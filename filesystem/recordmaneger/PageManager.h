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

//对内存中page数据块进行读取修改操作
class PageManager {
    int slot_int_size;//一个槽中的数据长度
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
    void resetPage(BufType page) {
        this->page = page;
        this->slot_int_size = page[PAGE_SLOT_INT_SIZE_INT_OFFSET];
        bitmap->setBitmap(page);
    }
    /**
     * 分配出新页时初始化数据页信息（设置页头信息和清零位图）
     * @param page
     * @param pid
     * @param record_int_size
     */
    void allocateFreePage(BufType page, int pid, int record_int_size){
        this->page = page;
        this->slot_int_size = record_int_size;
        //初始化数据页，设置所有位图为0
        char* buf = (char*) page;
        buf = buf + PAGE_SIZE - RECORD_BITMAP_SIZE;
        for(int i = 0 ; i < RECORD_BITMAP_SIZE ; ++i) {
            char slot = 0;
            buf[i] = slot;
        }
        printf("clean bitmap ok\n");

        this->bitmap->setBitmap(this->page);
        //初始化页头信息
        this->bitmap->setSlotSize(record_int_size);
        this->bitmap->page_is_full = 0;
        this->bitmap->slot_used_number = 0;
        //写入内存中
        this->bitmap->writebackHeaderInfo();
    }

    /**
     * 更新sid槽位的记录为以buf为首地址的记录
     * @param sid
     * @param buf
     * @return
     */
    bool updateRecord(int sid, BufType buf) {
        BufType begin = page + PAGE_HEADER_INT_SIZE;
        BufType record = begin + sid * slot_int_size;
        for(int i = 0 ; i < this->slot_int_size ; ++i) {
            record[i] = buf[i];
        }
        return true;
    }
    /**
     * 将数据buf插入sid槽位，并标记位图为1
     * @param sid
     * @param buf
     * @return
     */
    bool insertRecordBySid(int sid, BufType buf) {
        if(this->bitmap->setSlot(sid)) {
            //定位到slot首地址
            BufType record = (this->page + PAGE_HEADER_INT_SIZE) + sid * this->slot_int_size;
            for(int i = 0 ; i < this->slot_int_size ; ++i) {
                record[i] = buf[i];
            }
            return true;
        }
        return false;
    }
    /**
     * 插入一条记录，存在空闲并成功返回true，否则返回false
     * @param buf
     * @param rid
     * @return
     */
    bool insertRecord(BufType buf , RID& rid) {
        int sid = bitmap->findFreeSid();
        rid.sid = sid;
        if(sid == -1) return false;
        if( this->insertRecordBySid(sid, buf) ) {
            this->bitmap->slot_used_number ++;
            if(this->bitmap->slot_used_number >= this->bitmap->slot_max_number)
                this->bitmap->page_is_full = 1;
            this->bitmap->writebackHeaderInfo();
        }
    }

    /**
     * 删除一条记录。标记位图为0
     * @param sid
     * @return
     */
    bool deleteRecord(int sid) {
        if(this->bitmap->deleteSlot(sid)) {
            this->bitmap->slot_used_number --;
            this->bitmap->writebackHeaderInfo();
            return true;
        }
        return false;

    }
    /**
     * 获取rid定位的数据记录的copy
     * @param rid
     * @param rc
     * @return
     */
    RC getRecordCopy(RID rid , Record& rc) {
        if(rid.sid < 0 || rid.sid >= this->bitmap->slot_max_number ) {
            printf("search sid over page_slot_num\n");
            return RC(-1);
        }
        if(!this->bitmap->isSlotUsed(rid.sid)) {
            printf("sid not used\n");
            return RC(-1);
        }

        BufType begin = page + (PAGE_HEADER_INT_SIZE);
        BufType data = begin + rid.sid * slot_int_size;
        BufType copy = copyRecord(data);
        rc.setData(copy);
        rc.setRID(rid);
        return RC(0);
    }
    /**
     * copy data为首地址的slot_int_size个4字节数据
     * @param data
     * @return copy
     */
    BufType copyRecord(BufType data) {
        BufType copy = new unsigned int[this->slot_int_size];
        for(int i = 0 ; i < this->slot_int_size; ++i) {
            copy[i] = data[i];
        }
        printf("copy record: slot_int_size %d\n",slot_int_size);
        return copy;
    }
    /**
     * 获取已经使用的槽位数量
     * @return slot_used_number
     */
    int getSlotNum() {
        return this->bitmap->slot_used_number;
    }

    /**
     * 获取已经使用的槽位数量
     * @return slot_free_number
     */
    int getFreeSlotNumber() {
        return this->bitmap->slot_max_number - this->bitmap->slot_used_number;
    }

    bool isPageFull() {
        return this->bitmap->page_is_full;
    }

    int getMaxSlotNumber() {
        return this->bitmap->slot_max_number;
    }

};

#endif //PAGE_MANAGER_H
