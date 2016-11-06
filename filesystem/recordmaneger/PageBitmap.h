//
// Created by dalaoshe on 16-10-16. 每一个页的位图管理器
//

#ifndef PAGE_BITMAP_H
#define PAGE_BITMAP_H

#include "../utils/pagedef.h"
struct PageBitmap{
    //address page bitmap
    //该页槽位总数
    int slot_num;
    //该页槽位总数 / 32
    int slot_int_num;
    //该页槽大小slot_size = slot_int_size * 4 byte
    int slot_int_size;

    //页头
    unsigned int *page_header;
    //页
    unsigned int *page;
    //位图
    unsigned int *bitmap;

    PageBitmap(unsigned int* bitmap) {
        this->page_header = bitmap;
        this->bitmap = bitmap;
        this->page = bitmap;
    }

    void setBitmap(unsigned int* bitmap) {
        this->page_header = bitmap;
        this->bitmap = bitmap;
        this->page = bitmap;
    }

    void setSlotSize(int slot_int_size) {
        this->slot_int_size = slot_int_size;
        this->slot_num = (PAGE_SIZE - PAGE_HEADER_SIZE) / (slot_int_size << 2);
        this->slot_int_num = (this->slot_num >> 5);
        if((this->slot_num - (this->slot_int_num << 5) > 0)) slot_int_num ++;
    }

    //标记该槽位为未使用
    bool deleteSlot(int sid) {
        if(sid > slot_num || sid < 0)return false;
        //bitmap_index = sid / 32 定位槽位号所在的位图index
        int bitmap_index = sid >> 5;
        //pos 定位
        int pos = sid - (bitmap_index << 5);

        unsigned int p = 1 << pos;
        p = ~p;
        unsigned int slot = *(bitmap+bitmap_index);
        slot = p & slot;
        *(bitmap+bitmap_index) = slot;
        return true;
    }
    //获取该页第一个未被使用的槽位，获得其sid。sid  < slot_num
    int findFreeSid() {
        int sid = 0;
        //遍历每每一个4字节的位图
        printf("slot_int_num: %d\n",slot_int_num);
        printf("slot_num: %d\n",slot_num);
        for(int j = 0 ; j < slot_int_num ; ++j) {
            unsigned int slot = *(bitmap+j);
            unsigned int t = 1;
            //遍历4字节的所有位
            for (int i = 0; i <= 31; ++i) {
                unsigned int temp = slot >> i;
                unsigned int result = temp & t;
                if (result == 0) {
                    if((sid+i) >= slot_num) {
                        return -1;
                    }
                    return sid + i;
                }
            }
            sid += 32;
        }
        return -1;
    }
    //标记该槽位为已用
    int setSlot(int sid) {
        if(sid > slot_num || sid < 0)return false;
        //bitmap_index = sid / 32 定位槽位号所在的4字节位图index
        int bitmap_index = sid >> 5;
        //pos 定位所在4字节位图的第几位
        int pos = sid - (bitmap_index << 5);
        unsigned int p = 1 << pos;
        unsigned int slot = *(bitmap+bitmap_index);
        slot = p | slot;
        *(bitmap+bitmap_index) = slot;
        return true;
    }

};
#endif //PAGE_BITMAP_H
