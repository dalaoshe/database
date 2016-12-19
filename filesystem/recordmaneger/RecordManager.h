#ifndef RECORD_MANAGER_H
#define RECORD_MANAGER_H

#include "PageManager.h"
#include "Record.h"
#include "FileAttr.h"
#include "../bufmanager/BufPageManager.h"
#include "../fileio/FileManager.h"
#include "../utils/pagedef.h"
#include "../utils/rc.h"
#include "../utils/base.h"
#include <cstring>
#include <string>
#include <iostream>
#include <vector>

using namespace std;
/**
 * 解析数据表的字段
 */
//0 pageID
//1 record_int_size
//2 attr_size 字段数
//.....
//自32起，每32bytes为一个字段的定义
//key_name 20byte(//列名最长19byte + '\0'),
//key_type 4byte,
//null 4byte,
//length 4byte,


//以记录的粒度管理记录
class RM_FileHandle {
    //文件头关闭时需要写回
    BufType fileHeader;
    //每一个handle对应一个fm和对应的bpm
    FileManager* fm;
    BufPageManager* bpm;
    PageManager* pm;

    int record_int_size;
    int max_slot_number;
    int last_pageID;
    int free_pageID;
    int attr_count;

    int fileID;
    int headIndex;
    /**
     * 获取可以插入数据行的数据页的pid
     * @return
     */
    int _findFreePage() {
        int index;
        BufType page = bpm->getPage(fileID,free_pageID,index);
        pm->resetPage(page);

        //获取可插入页
        if( pm->isPageFull() ) {//空闲页已经满
            //查看最后一页
            page = bpm->getPage(fileID,last_pageID,index);
            pm->resetPage(page);
            if (pm->isPageFull()) {//最后一页已经满
                //新开一页
                last_pageID ++;
                page = bpm->getPage(fileID,last_pageID,index);
                pm->resetPage(page);
                pm->allocateFreePage(page,last_pageID,record_int_size);
                //将新开的页标记为脏页
                bpm->markDirty(index);
            }
            //重新定位空闲页
            free_pageID = last_pageID;
            //修改了头页
            bpm->markDirty(headIndex);
        }

        fileHeader[TABLE_FREE_PAGE_INT_OFFSET] = free_pageID;
        fileHeader[TABLE_LAST_PAGEID_INT_OFFSET] = last_pageID;

        return free_pageID;
    }
public:
    RM_FileHandle  () {
        pm = new PageManager();
    };                                  // Constructor
    ~RM_FileHandle () {
        this->close();
    };// Destructor

    /**
     * @函数名getRec
     * @参数rid:记录id，<pid,rid>
     * @参数rec:待赋值的记录实例
     * 功能:将对应位置的数据copy到rec中
     * 返回:成功操作返回RC(0)
     */
    RC getRec(RID rid, Record &rec) {
        int index;
        BufType page = bpm->getPage(fileID,rid.pid,index);
        pm->resetPage(page);
        return pm->getRecordCopy(rid,rec);
    };
    /**
     * @函数名insertRec
     * @参数data:待插入数据的首地址
     * @参数rid:待赋值的记录id
     * 功能:将数据插到该文件的第一个空闲页的空闲槽，并记录rid，并标记对应页为脏页
     * 返回:成功操作返回RC(0)
     */
    RC insertRec(BufType data, RID &rid){
        int index;
        int pid = this->_findFreePage();
        rid.pid = pid;
        BufType page = bpm->getPage(fileID,pid,index);
        pm->resetPage(page);
        if(pm->insertRecord(data,rid)) {

            bpm->markDirty(index);
            return RC();
        }
        return RC(-1);
    };
    /**
     * @函数名deleteRec
     * @参数rid:待删除的记录id
     * 功能:将相应的槽位的位图标记为0，以完成删除，并标记对应页为脏页
     * 返回:成功操作返回RC(0)
     */
    RC deleteRec(const RID &rid) {
        int index;
        BufType page = bpm->getPage(fileID,rid.pid,index);
        pm->resetPage(page);
        if(pm->deleteRecord(rid.sid)) {
            bpm->markDirty(index);
            //由于该行删除，该数据页空闲,若空闲行大于最小值则认为该页空闲
            if(pm->getFreeSlotNumber() > RECORD_MIN_FREE_NUMBER) {
                this->free_pageID = rid.pid;
                fileHeader[TABLE_FREE_PAGE_INT_OFFSET] = free_pageID;
                bpm->markDirty(headIndex);
            }
            return RC();
        }
        return RC(-1);
    };
    /**
     * @函数名updateRec
     * @参数rec:需要更新的记录
     * 功能:将rec的rid指示的槽位的数据更新为rec的数据，以完成更新，并标记对应页为脏页
     * 返回:成功操作返回RC(0)
     */
    RC updateRec(const Record &rec){
        int index;
        BufType page = bpm->getPage(fileID,rec.getRID().pid,index);
        pm->resetPage(page);
        BufType data = rec.getData();
        RID rid = rec.getRID();
        if(pm->updateRecord(rid.sid,data)) {
            bpm->markDirty(index);
            return RC();
        }
        return RC(-1);
    };

    void setBufManager(BufPageManager* bpm) {
        this->bpm = bpm;
    }
    void setFileID(int fileID) {
        this->fileID = fileID;
    }
    void setFileManager(FileManager* fm) {
        this->fm = fm;
    }
    int getFileID(){
        return this->fileID;
    }

    /**
     * @函数名close
     * 功能:关闭缓存和文件管理器
     * 返回:成功操作返回RC(0)
     */
    RC close() {
        bpm->markDirty(headIndex);
        bpm->close();
        fm->closeFile(fileID);
        delete bpm;
        delete fm;
        return RC();
    }

    /**
     * @函数名init
     * 功能: 初始化，获取对应的文件头页的信息，并标记其为脏页
     * 返回:成功操作返回RC(0)
     */
    RC init() {
        this->fileHeader = this->bpm->getPage(fileID,0,this->headIndex);

        this->record_int_size = fileHeader[TABLE_RECORD_INT_SIZE_INT_OFFSET];
        this->last_pageID = fileHeader[TABLE_LAST_PAGEID_INT_OFFSET];
        this->free_pageID = fileHeader[TABLE_FREE_PAGE_INT_OFFSET];
        this->attr_count = fileHeader[TABLE_ATTR_COUNT_INT_OFFSET];
        //pm默认打开第一页
        int index;
        BufType page = this->bpm->getPage(fileID,1,index);
        pm->resetPage(page);

        printf("fileId: %d record_int_size %d\n",fileID,this->record_int_size);
        bpm->markDirty(this->headIndex);
        return RC();
    }
    /**
    * @函数名getPageNum
    * @参数page_num:待赋值的页总数
    * 功能: 从文件头页读取已经使用的数据页的总数
    * 返回:成功操作返回RC(0)
    */
    RC getPageNum(int &page_num) {

        page_num = this->last_pageID + 1;
        /*
        pm->resetPage(fileHeader);
        RID rid;
        rid.pid = 0;
        rid.sid = 0;

        page_num = (pm->getRecordCopy(rid)).getHeaderPageNum();
        */
        return RC();
    }
    /**
    * @函数名getSlotUsedNumner
    * @参数pid:待查询的页id
    * @参数slot_num:待赋值的槽总数
    * 功能:获取pid页的使用的槽位总数
    * 返回:成功操作返回RC(0)
    */
    RC getSlotUsedNumber(int pid, int &slot_used_number) {
        int index;
        BufType page = bpm->getPage(fileID,pid,index);
        pm->resetPage(page);
        slot_used_number = pm->getSlotNum();
        return RC();
    }
    /**
     * 打印数据表的信息
     * @return
     */
    RC ShowSchema(){
        int index;
        BufType page_header = bpm->getPage(fileID,0,index);
        RM_FileAttr* attr = new RM_FileAttr();
        attr->getFileAttrFromPageHeader(page_header);
        attr->showFileAttrInfo();
        delete attr;
    }
    /**
     * 获取该文件的首页
     * @return
     */
    BufType getFileHeader() {
        return this->fileHeader;
    }

    int getLastPageID() {
        return  this->last_pageID;
    }
    int getMaxSlotNumber() {
        return this->pm->getMaxSlotNumber();
    }
};

class RecordManager{
    //负责文件头的读取
    FileManager *fm;
    BufPageManager *bpm;

public:
    RecordManager(FileManager *fm, BufPageManager* bpm) {
        this->fm = fm;
        this->bpm = bpm;
    }
    /*
    * @函数名createFile
    * @参数name:建立文件名
    * @参数record_int_size:该文件每个槽位的int长度，规定槽位长度为4字节对齐
    * 功能:新建一个文件，并初始化文件头页对应的信息写入文件
    * 返回:成功操作返回RC(0)
    */
    /**
     *
     * @param name 表名
     * @param attr 表参数（各个列对应的属性信息）
     * @return
     */
    RC createFile(const char* name , RM_FileAttr* attr) {
        if(this->fm->createFile(name)) {
            //建立文件成功
            int fileID;
            fm->openFile(name,fileID);
            int index;
            //获取头页
            BufType page_header = bpm->getPage(fileID,0,index);
            //将该表的信息写入头页
            attr->initFileAttrToPageHeader(page_header);
            //标记为脏页
            bpm->markDirty(index);
            //写回数据头页
            bpm->writeBack(index);

            //获取数据行长度
            int record_int_size = page_header[TABLE_RECORD_INT_SIZE_INT_OFFSET];
            printf("init header! record_int_size: %d\n",record_int_size);
            //初始化第一个数据页信息（pid=1）
            BufType first_data_page = bpm->getPage(fileID,1,index);
            PageManager* pm = new PageManager();
            pm->allocateFreePage(first_data_page,1,record_int_size);
            bpm->markDirty(index);
            bpm->writeBack(index);
            printf("allocate first page! record_int_size: %d\n",record_int_size);
            delete pm;
            printf("create! record_int_size: %d\n",record_int_size);
            return RC();
        }
        return RC(-1);
    }
    /*
    * @函数名destroyFile
    * @参数name:待删除的文件名
    * 功能:删除一个文件
    * 返回:成功操作返回RC(0)
    */
    RC destroyFile(const char* name) {
        if(fm->destroyFile(name)) {
            return RC();
        }
        return RC(-1);
    }
    /*
    * @函数名openFile
    * @参数name:待打开的文件名
    * @参数fileHandle:待初始化的文件记录管理操作句柄
    * 功能:打开一个文件，并为其初始化相应的filemanager/bufmanager,以及对应的RM_FileHandle
    * 返回:成功操作返回RC(0)
    */
    RC openFile(const char* name, RM_FileHandle& fileHandle) {
        FileManager *fm = new FileManager();
        int fileID;
        if(fm->openFile(name,fileID)) {
            BufPageManager *bpm = new BufPageManager(fm);
            fileHandle.setBufManager(bpm);
            fileHandle.setFileID(fileID);
            fileHandle.setFileManager(fm);
            fileHandle.init();
            return RC();
        }
        printf("error\n");
        return RC(-1);
    }
    /*
    * @函数名closeFile
    * @参数fileHandle:待关闭的文件句柄
    * 功能:关闭对应的RM_FileHandle
    * 返回:成功操作返回RC(0)
    */
    RC closeFile(RM_FileHandle& fileHandle) {
        fileHandle.close();
        return RC();
    }
};

/*
 * 按属性查找器，尚未测试
 */
#include <map>
class RM_FileScan {
    AttrType attrType;
    CompOp op;
    int attrLength;
    int attrOffset;
    char* value;
    int pid;
    int sid;
    int page_num;
    RM_FileHandle *fileHandle;
    int col_index;
public:
    RM_FileScan  (){};                                // Constructor
    ~RM_FileScan (){};                                // Destructor
    RC openScan     (RM_FileHandle *fileHandle,  // Initialize file scan
                     AttrType      attrType,
                     int           attrLength,
                     int           attrOffset,
                     CompOp          compOp,
                     char          *value,
                     int col_index
                    ) {
        this->fileHandle = fileHandle;
        this->attrType = attrType;
        this->attrLength = attrLength;
        this->attrOffset = attrOffset;
        this->op    = compOp;
        this->value = value;
        this->pid = 1;
        this->sid = 0;
        this->col_index = col_index;
    }
    RC getNextRec   (Record &rec);                  // Get next matching record
    RC closeScan    ();                                // Terminate file scan

    bool checkRecord(Record &rec) {
        char* target_v = this->value;
        char* rec_v = rec.getData(this->attrOffset);

        if(op == CompOp::ISNULL_OP) {
            return rec.isNULL(col_index);
        }

        if(attrType == AttrType::FLOAT) {
            switch (op) {
                case EQ_OP: {
                    return (*(float*)rec_v) == (*(float*)target_v);
                }
                case LT_OP: {
                    return (*(float*)rec_v) < (*(float*)target_v);
                }
                case GT_OP: {
                    return (*(float*)rec_v) > (*(float*)target_v);
                }
                case LE_OP: {
                    return (*(float*)rec_v) <= (*(float*)target_v);
                }
                case GE_OP: {
                    return (*(float*)rec_v) >= (*(float*)target_v);
                }
                case NE_OP: {
                    return (*(float*)rec_v) < (*(float*)target_v) || (*(float*)rec_v) > (*(float*)target_v);;
                }
                case NO_OP: {
                    return target_v == NULL;
                }
            }
        }
        else if(attrType == AttrType::INT) {
            switch (op) {
                case EQ_OP: {
                    return (*(int*)rec_v) == (*(int*)target_v);
                }
                case LT_OP: {
                    return (*(int*)rec_v) < (*(int*)target_v);
                }
                case GT_OP: {
                    return (*(int*)rec_v) > (*(int*)target_v);
                }
                case LE_OP: {
                    return (*(int*)rec_v) <= (*(int*)target_v);
                }
                case GE_OP: {
                    return (*(int*)rec_v) >= (*(int*)target_v);
                }
                case NE_OP: {
                    return (*(int*)rec_v) < (*(int*)target_v) || (*(int*)rec_v) > (*(int*)target_v);;
                }
                case NO_OP: {
                    return target_v == NULL;
                }
            }
        }
        else if(attrType == AttrType::STRING) {
            switch (op) {
                case EQ_OP: {

                    return strcmp(rec_v,target_v) == 0;
                }
                case LT_OP: {
                    return strcmp(rec_v,target_v) < 0;
                }
                case GT_OP: {
                    return strcmp(rec_v,target_v) > 0;
                }
                case LE_OP: {
                    return strcmp(rec_v,target_v) <= 0;
                }
                case GE_OP: {
                    return strcmp(rec_v,target_v) >= 0;
                }
                case NE_OP: {
                    return strcmp(rec_v,target_v) != 0;
                }
                case NO_OP: {
                    return target_v == NULL;
                }
                case LIKE_OP: {
                    int len = strlen(target_v);
                    //printf("pattern %s len %d\n",target_v,len);
                    string pattern = string(target_v).substr(1,len-2);
                    string rec = string(rec_v);
                    //cout<<"rec "<<rec<<" "<<pattern<<endl;
                    if(rec.find(pattern) == string::npos) return false;
                    return true;
                }
            }
        }
    }

    RC getAllRecord(map<RID,int> & rid_list) {
        int slot_max_number = fileHandle->getMaxSlotNumber();
        int last_page_id = fileHandle->getLastPageID();
        int pid = 1, sid = 0;
       // printf("slot_max: %d last_pid: %d \n",slot_max_number,last_page_id);
        for(pid = 1 ; pid <= last_page_id ; ++pid) {

            for(sid = 0 ; sid < slot_max_number; ++sid) {
                RID rid;
                rid.pid = pid; rid.sid = sid;
                Record record;
                if( this->fileHandle->getRec(rid,record).equal(RC(0)) ) {
                    //存在这条记录，判断是否符合要求
                   // printf("check rid<%d,%d>\n",rid.pid,rid.sid);
                    if(this->checkRecord(record)) {
                        //该记录符合要求
                        rid_list.insert(pair<RID, int>(rid, 1));
                    }
                }
            }
        }
        return RC();
    }
    /**
     * 获取文件中所有页的所有槽（包括没有使用的槽）
     * @param rid_list
     * @return
     */
    RC getAllRecordOfFile(map<RID,int> & rid_list) {
        int slot_max_number = fileHandle->getMaxSlotNumber();
        int last_page_id = fileHandle->getLastPageID();
        int pid = 1, sid = 0;
       // printf("slot_max: %d last_pid: %d \n",slot_max_number,last_page_id);
        for(pid = 1 ; pid <= last_page_id ; ++pid) {
            for(sid = 0 ; sid < slot_max_number; ++sid) {
                RID rid;
                rid.pid = pid; rid.sid = sid;
                Record record;
                if( this->fileHandle->getRec(rid,record).equal(RC(0)) ) {
                    rid_list.insert(pair<RID, int>(rid, 1));
                }
            }
        }
        return RC();
    }

    RC getAllIndexPairOfFile(map<RID,char*> & rid_list) {
        int slot_max_number = fileHandle->getMaxSlotNumber();
        int last_page_id = fileHandle->getLastPageID();
        int pid = 1, sid = 0;
        //printf("slot_max: %d last_pid: %d \n",slot_max_number,last_page_id);
        for(pid = 1 ; pid <= last_page_id ; ++pid) {
            for(sid = 0 ; sid < slot_max_number; ++sid) {
                RID rid;
                rid.pid = pid; rid.sid = sid;
                Record record;
                if( this->fileHandle->getRec(rid,record).equal(RC(0)) ) {
                    char* key = record.getData(this->attrOffset);
                    rid_list.insert(pair<RID, char*>(rid, key));
                }
            }
        }
        return RC();
    }
};

#endif