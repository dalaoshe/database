#ifndef RECORD_MANAGER_H
#define RECORD_MANAGER_H

#include "../bufmanager/BufPageManager.h"
#include "../fileio/FileManager.h"
#include "../utils/pagedef.h"
#include "PageManager.h"
#include "Record.h"
#include <iostream>
#include "../utils/rc.h"
#include "../utils/base.h"
using namespace std;
//以记录的粒度管理记录
class RM_FileHandle {
    //文件头关闭时需要写回
    BufType fileHeader;
    //每一个handle对应一个fm和对应的bpm
    FileManager* fm;
    BufPageManager* bpm;
    PageManager* pm;
    int slot_int_size;
    int fileID;
    int headIndex;
    int _findFreePage() {
        int pageID = 2;
        return pageID;
    }
public:
    RM_FileHandle  () {
        pm = new PageManager();
    };                                  // Constructor
    ~RM_FileHandle () {
        this->close();
    };// Destructor

    /*
     * @函数名getRec
     * @参数rid:记录id，<pid,rid>
     * @参数rec:待赋值的记录实例
     * 功能:将对应位置的数据copy到rec中
     * 返回:成功操作返回RC(0)
     */
    RC getRec(const RID &rid, Record &rec) {
        int index;
        BufType page = bpm->getPage(fileID,rid.pid,index);
        pm->resetPage(page,slot_int_size);
        return pm->getRecordCopy(rid,rec);
    };
    /*
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
        pm->resetPage(page,slot_int_size);
        if(pm->insertRecord(data,rid)) {
            bpm->markDirty(index);
            return RC();
        }
        return RC(-1);
    };
    /*
     * @函数名deleteRec
     * @参数rid:待删除的记录id
     * 功能:将相应的槽位的位图标记为0，以完成删除，并标记对应页为脏页
     * 返回:成功操作返回RC(0)
     */
    RC deleteRec(const RID &rid) {
        int index;
        BufType page = bpm->getPage(fileID,rid.pid,index);
        pm->resetPage(page,slot_int_size);
        if(pm->deleteRecord(rid.sid)) {
            bpm->markDirty(index);
            return RC();
        }
        return RC(-1);
    };
    /*
     * @函数名updateRec
     * @参数rec:需要更新的记录
     * 功能:将rec的rid指示的槽位的数据更新为rec的数据，以完成更新，并标记对应页为脏页
     * 返回:成功操作返回RC(0)
     */
    RC updateRec(const Record &rec){
        int index;
        BufType page = bpm->getPage(fileID,rec.getRID().pid,index);
        pm->resetPage(page,slot_int_size);
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

    /*
     * @函数名close
     * 功能:关闭缓存和文件管理器
     * 返回:成功操作返回RC(0)
     */
    RC close() {
        bpm->close();
        delete fm;
        return RC();
    }

    /*
     * @函数名init
     * 功能: 初始化，获取对应的文件头页，并标记其为脏页
     * 返回:成功操作返回RC(0)
     */
    RC init() {
        this->fileHeader = this->bpm->getPage(fileID,0,this->headIndex);
        this->slot_int_size = fileHeader[1];
        printf("fileId: %d, slot_int_size: %d\n",fileID,slot_int_size);
        bpm->markDirty(this->headIndex);
        return RC();
    }
    /*
    * @函数名getPageNum
    * @参数page_num:待赋值的页总数
    * 功能: 从文件头页读取数据页的总数
    * 返回:成功操作返回RC(0)
    */
    RC getPageNum(int &page_num) {
        page_num = fileHeader[0];
        /*
        pm->resetPage(fileHeader);
        RID rid;
        rid.pid = 0;
        rid.sid = 0;

        page_num = (pm->getRecordCopy(rid)).getHeaderPageNum();
        */
        return RC();
    }
    /*
    * @函数名getSlotNum
    * @参数pid:待查询的页id
    * @参数slot_num:待赋值的槽总数
    * 功能:获取pid页的槽位总数
    * 返回:成功操作返回RC(0)
    */
    RC getSlotNum(int pid, int &slot_num) {
        BufType page = bpm->getPage(fileID,pid,this->headIndex);
        pm->resetPage(page,slot_int_size);
        pm->getSlotNum(slot_num);
        return RC();
    }
};

class RecordManager{
    PageManager *pm;
    //负责文件头的读取
    FileManager *fm;
    BufPageManager *bpm;

public:
    RecordManager(FileManager *fm, BufPageManager* bpm) {
        this->fm = fm;
        this->bpm = bpm;
        pm = new PageManager();
    }
    /*
    * @函数名createFile
    * @参数name:建立文件名
    * @参数record_int_size:该文件每个槽位的int长度，规定槽位长度为4字节对齐
    * 功能:新建一个文件，并初始化文件头页对应的信息写入文件
    * 返回:成功操作返回RC(0)
    */
    RC createFile(const char* name ,int record_int_size) {
        if(this->fm->createFile(name)) {
            int fileID;
            fm->openFile(name,fileID);
            int index,findex;
            BufType page_header = bpm->getPage(fileID,0,index);
            BufType page_first = bpm->getPage(fileID,1,findex);
            //code to edit page_header
            //0 page_num
            //1 slot_size
            page_header[0] = 1;
            page_header[1] = record_int_size;
            //....
            bpm->markDirty(index);
            bpm->markDirty(findex);
            bpm->writeBack(index);
            bpm->writeBack(findex);
            printf("create! slot_int_size: %d\n",record_int_size);
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