//
// Created by dalaoshe on 16-10-16. 每一个页的记录管理器
//

#ifndef PAGE_MANAGER_H
#define PAGE_MANAGER_H
//record_length 64*4 byte

#define SLOT_LENGTH  64

#include "PageBitmap.h"
#include "Record.h"
#include "../utils/rc.h"
class PageManager {
    //4 * 2048byte
    int slot_num;
    int slot_int_size;
    BufType page; //缓存在bfm中的页的首地址
    PageBitmap *bitmap; //该页的位图管理器
public:
    PageManager(BufType page) {
        this->page = page;
        bitmap = new PageBitmap(page);
    }
    PageManager() {
        this->page = NULL;
        bitmap = new PageBitmap(page);
    }
    void resetPage(BufType page , int slot_int_size) {
        this->page = page;
        this->slot_int_size = slot_int_size;
        this->slot_num = (PAGE_SIZE - PAGE_HEADER_SIZE) / (slot_int_size << 2);
        bitmap->setBitmap(page);
        bitmap->setSlotSize(slot_int_size);
    }
    //更新sid槽位的记录为以buf为首地址的记录
    bool updateRecord(int sid, BufType buf) {
        BufType begin = page + (PAGE_HEADER_SIZE >> 2);
        BufType record = begin + sid * slot_int_size;
        for(int i = 0 ; i < slot_int_size ; ++i) {
            record[i] = buf[i];
        }
        return true;
    }
    //将记录插入sid槽位
    bool insertRecord(int sid, BufType buf) {
        BufType begin = page + (PAGE_HEADER_SIZE >> 2);
        BufType record = begin + sid * slot_int_size;
        for(int i = 0 ; i < slot_int_size ; ++i) {
            record[i] = buf[i];
        }
        this->bitmap->setSlot(sid);
        return true;
    }
    //插入一条记录，存在空闲并成功返回true，否则返回false
    bool insertRecord(BufType buf , RID& rid) {
        int sid = bitmap->findFreeSid();
        rid.sid = sid;
        if(sid == -1) return false;
        return this->insertRecord(sid, buf);
    }

    //删除一条记录。标记位图为0
    bool deleteRecord(int sid) {
        bitmap->deleteSlot(sid);
        return true;
    }

    RC getRecordCopy(RID rid , Record& rc) {
        if(rid.sid < 0 || rid.sid > this->slot_num) {
            printf("search sid over page_slot_num\n");
            return RC(-1);
        }
        BufType begin = page + (PAGE_HEADER_SIZE >> 2);
        BufType data = begin + rid.sid * slot_int_size;
        BufType copy = copyRecord(data);
        rc.setData(copy);
        rc.setRID(rid);
        return RC();
    }

    BufType copyRecord(BufType data) {
        BufType copy = new unsigned int[SLOT_LENGTH];
        for(int i = 0 ; i < slot_int_size; ++i) {
            copy[i] = data[i];
        }
        return copy;
    }

    void getSlotNum(int &slot_num) {
        slot_num = this->slot_num;
    }



};

#endif //PAGE_MANAGER_H
