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

//以记录的粒度管理记录
class RM_FileHandle {
    //文件头关闭时需要写回
    BufType fileHeader;
    //每一个handle对应一个fm和对应的bpm
    FileManager* fm;
    BufPageManager* bpm;
    PageManager* pm;
    int record_size;
    int fileID;
    int headIndex;
    //TODO find free page
    int _findFreePage() {
        int pageID = 1;
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
        pm->resetPage(page,record_size);
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
        pm->resetPage(page,record_size);
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
        pm->resetPage(page,record_size);
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
        pm->resetPage(page,record_size);
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
        this->record_size = fileHeader[1];
        //printf("fileId: %d, slot_int_size: %d\n",fileID,slot_int_size);
        printf("fileId: %d\n",fileID);
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
        pm->resetPage(page,record_size);
        pm->getSlotNum(slot_num);
        return RC();
    }

    RC ShowSchema(){
        int index;
        BufType page_header = bpm->getPage(fileID,0,index);
        printf("page_ID: %d\n",page_header[0]);
        printf("record_size: %d\n",page_header[1]);
        int attr_offset = 32>>2;
        int attr_count = page_header[2];
        for(int i=0;i<attr_count;++i){
            int offset = attr_offset*i + ATTR_SIZE;
            printf("attr_name: %s\t",(char*)(page_header[offset]));
            printf("attr_type: %d\t ",page_header[offset+5]) ;
            printf("attr_length: %d\t ",page_header[offset+6]) ;
            printf("attr_not_null: %d\t\n ",page_header[offset+7]) ;
        }
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
    RC createFile(const char* name ,int record_int_size, RM_FileAttr* attr) {
        if(this->fm->createFile(name)) {
            int fileID;
            fm->openFile(name,fileID);
            int index;
//            int findex;
            BufType page_header = bpm->getPage(fileID,0,index);
//            BufType page_first = bpm->getPage(fileID,1,findex);
            //TODO: code to edit root_page
            //0 pageID
            //1 record_init_size
            //2 attr_size 字段数
            //.....
            //自32起，每32bytes为一个字段的定义
            //key_name 20,key_type 4,null 4,length 4
            printf("index:%d\n",index);
            page_header[0] = 0;
            page_header[1] = record_int_size;
            int attr_offset = 32>>2;
            int attr_count = attr->key_type.size();
            page_header[2] = attr_count;
            printf("1\n");
            for(int i=0;i<attr_count;++i){
                int offset = attr_offset*i + ATTR_SIZE;
                const char* name = attr->key_name[i].c_str();
                for(int i=0;i<attr->key_name[i].size();++i){
                    *((char*)(page_header[offset])+i) = *(name+i);
                }
                page_header[offset+5] = attr->key_type[i];
                page_header[offset+6] = attr->value_length[i];
                page_header[offset+7] = attr->not_null[i];
            }

//            page_header[2] = fix_col_num;
//            page_header[3] = var_col_num;
            //....
            printf("10\n");
            bpm->markDirty(index);
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