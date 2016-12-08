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
        pm->resetPage(page,record_int_size);

        //获取可插入页
        if( pm->isPageFull() ) {//空闲页已经满
            //查看最后一页
            page = bpm->getPage(fileID,last_pageID,index);
            pm->resetPage(page,record_int_size);
            if (pm->isPageFull()) {//最后一页已经满
                //新开一页
                last_pageID ++;
                page = bpm->getPage(fileID,last_pageID,index);
                pm->resetPage(page,record_int_size);
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
        pm->resetPage(page,this->record_int_size);
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
        pm->resetPage(page,record_int_size);
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
        pm->resetPage(page,this->record_int_size);
        if(pm->deleteRecord(rid.sid)) {
            bpm->markDirty(index);
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
        pm->resetPage(page,record_int_size);
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
        bpm->close();
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
        pm->resetPage(page,this->record_int_size);
        pm->getSlotNum(slot_used_number);
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
    RC createFile(const char* name ,int record_int_size, RM_FileAttr* attr) {
        if(this->fm->createFile(name)) {
            //建立文件成功
            int fileID;
            fm->openFile(name,fileID);
            int index;
            //获取头页
            BufType page_header = bpm->getPage(fileID,0,index);
            printf("index:%d\n",index);
            //TODO: code to edit root_page
            //将该表的信息写入头页
            attr->setFileAttrToPageHeader(page_header,record_int_size);
            //标记为脏页
            bpm->markDirty(index);
            //写回
            bpm->writeBack(index);
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
class RM_FileScan {
    AttrType attrType;
    CompOp op;
    int attrLength;
    int attrOffset;
    ClientHint hit;
    void* value;
    int pid;
    int sid;
    int page_num;
    RM_FileHandle *fileHandle;
public:
    RM_FileScan  (){};                                // Constructor
    ~RM_FileScan (){};                                // Destructor
    RC openScan     (RM_FileHandle *fileHandle,  // Initialize file scan
                     AttrType      attrType,
                     int           attrLength,
                     int           attrOffset,
                     CompOp        compOp,
                     void          *value,
                     ClientHint    pinHint = NO_HINT);
    RC getNextRec   (Record &rec);                  // Get next matching record
    RC closeScan    ();                                // Terminate file scan
    bool checkRecord(Record &rec) const ;
};

#endif