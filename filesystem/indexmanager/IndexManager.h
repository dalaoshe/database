//
// Created by dalaoshe on 16-11-6.
//

#ifndef FILESYSTEM_INDEXMANAGER_H
#define FILESYSTEM_INDEXMANAGER_H
#include "../utils/rc.h"
#include "../utils/base.h"
#include "../fileio/FileManager.h"
#include "../bufmanager/BufPageManager.h"
#include "IndexPageManager.h"
#include "BucketPageManager.h"
#include "b_plus_tree.h"
#include <vector>
#define INDEX_PAGE_HEADER_SIZE 32

class IX_IndexHandle {
    //每一个handle对应一个fm和对应的bpm
    FileManager* fm;
    BufPageManager* bpm;

    int fileID;
    //文件头页在缓存中的下标
    int headIndex;
    //文件头页
    BufType header;
    /*
     * 文件头页存储的信息
     */
    //索引根页id
    int rootPageId;
    //该文件目前由多少页
    int page_num;
    //该文件每页记录的最多索引项数量
    int max_num;
    //该文件每页记录的最少索引项数量
    int min_num;
    //索引码的长度
    int key_byte_size;
    //每个索引项的byte长度
    int index_byte_size;
    //索引码在索引行的偏移
    int key_offset;
    //索引码数据类型
    int key_type;
    //每个索引页的页头长度byte
    int page_header_size;
public:

    IX_IndexHandle  (){};                             // Constructor
    ~IX_IndexHandle (){};                             // Destructor

    RC InsertEntry     (void *key, const RID &rid) {
        //待插入索引码该插入的叶级节点
        Node node;
        //待插入的索引码指针对
        Key k = Key((char*)key);
        Pointer pointer(rid.pid,rid.sid);
        //叶级节点页在缓存管理器中的下标
        int index;
        //根级页到叶级页的路径（包括叶级页）
        vector<Pointer> path;
        if(this->searchEntryLeaf(k,node,index,path) == RC(0)) {
            //索引码存在直接插入指针桶
            if(node.exist(k)) {
                int i = node.search(k);
                IndexType index_type = node.getPointerType(i+1);
                /*
                 * 根据指针为指针桶还是行定位器进行不同的插入操作
                 */
                if(index_type == IndexType::bucket) {
                    Pointer bucket_pointer = node.getPointer(i+1);
                    int bucket_index;
                    int bucket_pid = bucket_pointer.pid;
                    BufType bucket_page = this->bpm->getPage(fileID,bucket_pointer.pid,bucket_index);
                    BucketPageManager bucket = BucketPageManager(bucket_page,key_offset,key_byte_size,index_byte_size,
                                                                 page_header_size,type,max_num,min_num,bucket_pointer);
                    //定位到最后一个指针桶页
                    while(bucket.hasNextBucket()) {
                        bucket_pid = bucket.getNextPid();
                        bucket_page = this->bpm->getPage(fileID,bucket_pointer.pid,bucket_index);
                        bucket.reset(bucket_page,Pointer(bucket_pid,page_header_size));
                    }
                    if(bucket.canInsert()) {
                        bucket.insertKey(key,pointer);
                        bucket.writeback();
                        this->bpm->markDirty(bucket_index);
                    }
                    else {
                        //将原指针桶与新指针桶关联并写回缓存
                        bucket.setNextPid(page_num);
                        bucket.writeback();
                        this->bpm->markDirty(bucket_index);
                        //创建新的指针桶
                        bucket_page = this->bpm->allocPage(fileID, page_num, bucket_index);
                        //初始化该指针桶页信息
                        bucket = BucketPageManager(bucket_page,key_offset,key_byte_size,index_byte_size,
                                                   page_header_size,type,max_num,min_num,Pointer(page_num,page_header_size));
                        bucket.initBucketPageInfo();
                        //插入索引码
                        bucket.insert(key,pointer);
                        bucket.writeback();
                        this->bpm->markDirty(bucket_index);
                        page_num += 1;
                    }
                }
                else if(index_type == IndexType::id){
                    int bucket_index;
                    Pointer bucket_pointer(page_num,page_header_size);
                    BufType bucket_page = this->bpm->allocPage(fileID, page_num, bucket_index);
                    page_num += 1;
                    BucketPageManager bucket = BucketPageManager(bucket_page,key_offset,key_byte_size,index_byte_size,
                                                                 page_header_size,type,max_num,min_num,bucket_pointer);
                    bucket.initBucketPageInfo();

                    Pointer old_pointer = node.getPointer(i+1);

                    bucket.insert(k,old_pointer);
                    bucket.insert(k,pointer);

                    node.setPointer(i+1,bucket_pointer);
                    node.setPointerType(i+1,IndexType::bucket);
                    node.writeback();
                    this->bpm->markDirty(index);
                    bucket.writeback();
                    this->bpm->markDirty(bucket_index);
                }
            }
            else {
                node.insertKey(k,pointer,IndexType::id);
                solveOverflow(node,index,path);
                return RC(0);
            }
        }
    };
    /*
     * 解决节点上溢
     */
    RC solveOverflow(Node node, int index, vector<Pointer>& path) {
        //递归基，不再上溢直接写回缓存标记脏页
        if (!node.overflow()) {
            node.writeback();
            this->bpm->markDirty(index);
            return RC(0);
        }
        //分裂的轴点
        int split = node.getSplit();
        //获取新的索引节点页并初始化该页的信息
        int new_index;
        BufType new_page = this->bpm->allocPage(fileID, page_num, new_index);
        page_num += 1;
        Node new_node = Node(new_page, key_offset, key_byte_size, index_byte_size, page_header_size, type);
        new_node.isleaf = node.isleaf;
        new_node.index_num = 0;
        //new_node.parent_pointer = node.parent_pointer;
        new_node.pointer = Pointer(page_num, page_header_size);

        //将split之后的所有关键码插入新节点
        for (int i = split+1; i <= node.index_num; ++i) {
            Key key = node.getKey(i);
            Pointer p = node.getPointer(i + 1);
            new_node.insertKey(key, p, IndexType::id);
        }

        //叶子节点需要将split也插入
        if(new_node.isLeaf()) {
            Key key = node.getKey(split);
            Pointer p = node.getPointer(split + 1);
            new_node.insertKey(key, p, IndexType::id);
        }
        else {
            //中间节点将首指针指向split的右孩子
            Pointer p = node.getPointer(split+1);
            new_node.setPointer(1,p);
        }
        //将原节点的码数减少至split-1,以完成删除
        node.index_num = split - 1;


        //要向上插入的关键码（split，新节点pointer）
        Key key = node.getKey(split);
        Pointer pointer = new_node.pointer;
        Node p;
        int pIndex;
        if (path.size() == 0) {
            //如果原节点没有父亲则新建
            BufType pPage = this->bpm->allocPage(fileID, page_num, pIndex);
            p = Node(pPage, key_offset, key_byte_size, index_byte_size, page_header_size, type);
            p.pointer = Pointer(page_num, page_header_size);
            p.isleaf = false;
            p.index_num = 0;
            //p.parent_pointer = Pointer(-1, -1);
            page_num += 1;
            //新生成的父节点的最左孩子为分裂前的节点
            p.setPointer(1,node.pointer);
            //关联父子节点
            //node.parent_pointer = new_node.parent_pointer = p.pointer;
        } else {
            BufType pPage = this->bpm->getPage(fileID,path[path.size()-1].pid,pIndex);
            path.pop_back();
            p = Node(pPage, key_offset, key_byte_size, index_byte_size, page_header_size, type);
        }

        //将分裂的字节点数据写回缓存
        node.writeback();
        new_node.writeback();
        //将缓存标记为脏页以使更新回磁盘
        this->bpm->markDirty(index);
        this->bpm->markDirty(new_index);
        //父节点插入关键码，并向上检查
        p.insertKey(key,pointer,IndexType::id);
        solveOverflow(p,pIndex,path);
    }


    RC DeleteEntry     (void *pData, const RID &rid) {

    };  // Delete index entry

    /*
     *  将文件头页信息写回缓存并标记脏页
     */
    RC ForcePages      () {
        BufType header = this->bpm->getPage(fileID,0,headIndex);
        /*
         * 将页头信息写入
         */
        //根页号初始化1
        *(((int *)header)) = rootPageId;
        //文件当前页数包括头页
        *(((int *)header)+1) = page_num;
        //每页最大索引数目
        *(((int *)header)+2) = max_num;
        //每页最小索引数目
        *(((int *)header)+3) = min_num;
        //单个索引码长度
        *(((int *)header)+4) = key_byte_size;
        //单个索引项长度
        *(((int *)header)+5) = index_byte_size;
        //索引码的在索引项中的偏移
        *(((int *)header)+6) = key_offset;
        //索引码的数据类型
        *(((int *)header)+7) = key_type;
        //每页页头长度
        *(((int *)header)+8) = page_header_size;
        this->bpm->markDirty(headIndex);
    };

    /*
     * key索引码 node,索引码所在的叶级节点 path，根到叶级节点的路径
     */
    RC searchEntryLeaf(void *key, Node &node, int &pageIndexInbpm , vector<Pointer>& path) {
        Key k = Key((char*)key);
        Pointer pointer = Pointer(rootPageId,page_header_size);
        BufType page = bpm->getPage(fileID,rootPageId,pageIndexInbpm);
        Node root = Node(page,key_offset,key_byte_size,index_byte_size,page_header_size,type,max_num,min_num,pointer);
        while(!root.isLeaf()) {
            int i = root.search(k);
            if(i == -1)return RC(-1);
            path.push_back(pointer);
            pointer = root.getPointer(i);
            BufType page = bpm->getPage(fileID,pointer.pid,index);
            root = root.reset(page,pointer);
        }
        node = root;
        return RC(0);
    }


    /*
     * @函数名close
     * 功能:将页头信息写回缓存并关闭缓存和文件管理器
     * 返回:成功操作返回RC(0)
     */
    RC close() {
        this->ForcePages();
        bpm->close();
        delete fm;
        return RC();
    }

    /*
     * @函数名init
     * 功能: 初始化，获取对应的文件头页信息
     * 返回:成功操作返回RC(0)
     */
    RC init() {
        this->fileHeader = this->bpm->getPage(fileID,0,this->headIndex);
        /*
         *  解析页头信息
         */
        //根页号
        this->rootPageId = *(((int *)header));
        //文件当前页数包括头页
        this->page_num = *(((int *)header)+1);
        //每页最大索引数目
        this->max_num = *(((int *)header)+2);
        //每页最小索引数目
        this->min_num = *(((int *)header)+3);
        //单个索引码长度
        this->key_byte_size = *(((int *)header)+4);
        //单个索引项长度
        this->index_byte_size = *(((int *)header)+5);
        //索引码的在索引项中的偏移
        this->key_offset = *(((int *)header)+6);
        //索引码的数据类型
        this->key_type = *(((int *)header)+7);
        //每页页头长度
        this->page_header_size = *(((int *)header)+8);
        //printf("fileId: %d, slot_int_size: %d\n",fileID,slot_int_size);
        return RC(0);
    }

    void setBufManager(BufPageManager* bpm) {
        this->bpm = bpm;
    }
    void setFileID(int fileID) {
        this->fileID = fileID;
    }
    void setFileManager(FileManager* fm) {
        this->fm = fm;
    }
};

class IndexManager {
    FileManager* fm;
    BufPageManager* bpm;
public:
    IndexManager   (FileManager *fm, BufPageManager* bpm) {
        this->fm = fm;
        this->bpm = bpm;
    };              // Constructor

    ~IndexManager()  () {

    };                             // Destructor


    RC CreateIndex  (const char *fileName,          // Create new index
                     int        indexNo,
                     AttrType   key_type,
                     int        key_byte_size) {
        int fileID,headIndex;
        if(fm->createFile(fileName)) {
            if(fm->openFile(fileName,fileID)) {
                BufType header = this->bpm->getPage(fileID, 0, headIndex);
                int max_num, min_num,
                    key_offset = 4,
                    index_byte_size = key_offset + key_byte_size + 8 + 4,
                    page_header_size = PAGE_HEADER_SIZE;
                //每页能存的最多索引数为页大小-页头大小-2个预留索引长度 / 索引长度
                max_num = (PAGE_SIZE - page_header_size - index_byte_size * 2) / index_byte_size;
                //最少为最多的一半
                min_num = max_num / 2;
                //初始化根页页号pid为1,页数为2
                this->setHeaderPage(header, 1, 2, max_num, min_num, key_byte_size, index_byte_size, key_offset,
                                    key_type, page_header_size);
                this->bpm->markDirty(headIndex);
                this->bpm->writeBack(headIndex);

                int index;
                BufType rootPage = this->bpm->getPage(fileID, 1, index);
                this->setIndexPage(rootPage, true, -1, 0, IndexType::index);
                this->bpm->markDirty(index);
                this->bpm->writeBack(index);
                return RC(0);
            }
            printf("create success but open fail\n");
        }
        printf("create error\n");
        return RC(-1);
    };

    RC setHeaderPage(BufType header, int root_pid, int page_num, int max_num, int min_num, int key_byte_size, int index_byte_size,
    int key_offset, int key_type, int page_header_size) {
        //根页号初始化1
        *(((int *)header)) = root_pid;
        //文件当前页数包括头页
        *(((int *)header)+1) = page_num;
        //每页最大索引数目
        *(((int *)header)+2) = max_num;
        //每页最小索引数目
        *(((int *)header)+3) = min_num;
        //单个索引码长度
        *(((int *)header)+4) = key_byte_size;
        //单个索引项长度
        *(((int *)header)+5) = index_byte_size;
        //索引码的在索引项中的偏移
        *(((int *)header)+6) = key_offset;
        //索引码的数据类型
        *(((int *)header)+7) = key_type;
        //每页页头长度
        *(((int *)header)+8) = page_header_size;
    }

    RC setIndexPage(BufType page, bool isleaf, int next_page_id, int index_num, int page_type) {
        *(((bool *)page)) = isleaf;
        //下一页的页号
        *(((int *)page)+1) = next_page_id;
        //该页记录的索引数目
        *(((int *)page)+2) = index_num;
        //该页的类型
        *(((int *)page)+3) = page_type;
    }



    RC DestroyIndex (const char *fileName,          // Destroy index
                     int        indexNo) {
        this->fm->destroyFile(fileName);
    };

    RC OpenIndex    (const char *fileName,          // Open index
                     int        indexNo,
                     IX_IndexHandle &indexHandle) {
        FileManager *fm = new FileManager();
        int fileID;
        if(fm->openFile(name,fileID)) {
            BufPageManager *bpm = new BufPageManager(fm);
            indexHandle.setBufManager(bpm);
            indexHandle.setFileID(fileID);
            indexHandle.setFileManager(fm);
            indexHandle.init();
            return RC(0);
        }
        printf("error\n");
        return RC(-1);
    };

    RC CloseIndex   (IX_IndexHandle &indexHandle) {
        indexHandle.close();
        return RC(0);
    };  // Close index
};

class IX_IndexScan {
public:
    IX_IndexScan  ();                                 // Constructor
    ~IX_IndexScan ();                                 // Destructor
    RC OpenScan      (const IX_IndexHandle &indexHandle, // Initialize index scan
                      CompOp      compOp,
                      void        *value,
                      ClientHint  pinHint = NO_HINT);
    RC GetNextEntry  (RID &rid);                         // Get next matching entry
    RC CloseScan     ();                                 // Terminate index scan
};
#endif //FILESYSTEM_INDEXMANAGER_H