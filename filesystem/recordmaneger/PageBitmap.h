//
// Created by dalaoshe on 16-10-16. 每一个页的位图管理器
//

#ifndef PAGE_BITMAP_H
#define PAGE_BITMAP_H

#include "../utils/pagedef.h"
struct PageBitmap{
    //address page bitmap
    //页头中存储的变量
    //目前状态 该页槽位总数
    int slot_num;
    //该页槽位总数 / 32
    //int slot_int_num;
    //该页槽大小slot_size = slot_int_size * 4 byte
    //int slot_int_size;

    //pageID 4 Bytes
    //slot_num 4 Bytes
    //free_cnt 4 Bytes
    //free_data 4 Bytes
    // 页头

    unsigned int *page_header;
    //页
    unsigned int *pageData;
    //位图
    unsigned int *bitmap;



    PageBitmap(unsigned int* bitmap) {
        this->page_header = bitmap;
        this->bitmap = bitmap+PAGE_SIZE-1;
        this->pageData = bitmap+PAGE_HEADER_SIZE;
    }

    void setBitmap(unsigned int* bitmap) {
        this->page_header = bitmap;
        this->bitmap = bitmap+PAGE_SIZE-1;
        this->pageData = bitmap+PAGE_HEADER_SIZE;
    }

 /*   void setSlotSize(int slot_int_size) {
        this->slot_int_size = slot_int_size;
        this->slot_num = (PAGE_SIZE - PAGE_HEADER_SIZE) / (slot_int_size << 2);
        //this->slot_int_num = (this->slot_num >> 5);
        //if((this->slot_num - (this->slot_int_num << 5) > 0)) slot_int_num ++;
    }*/

    //设置数据页的页头,传递时需要给出页头中需要的参数
    void setPageHeader(unsigned int* page_header,int length){
        if(length>32)printf("the page %d header overflows!",*(this->page_header));
        for(int i=0;i<length;++i){
            *(this->page_header+i) = *(page_header+i);
        }
    }

    void setPageHeader(int pid, int slot_num,int free_cnt,int free_data_offset){
        *(this->page_header) = pid;
        *(this->page_header+1) = slot_num;
        *(this->page_header+2) = free_cnt;
        *(this->page_header+3) = free_data_offset;
    }
    //设置数据页页头中的槽总数
    void setSlotSize(unsigned int slot_size){
        *(this->page_header+1) = slot_size;
        slot_num = slot_size;
    }

    //标记该槽位为未使用
    bool deleteSlot(int sid) {
        if(sid > slot_num || sid < 0){
            printf("delete slot; sid overflows!");
            return false;
        }
        //bitmap_index = sid / 32 定位槽位号所在的位图index
        int bitmap_index = sid >> 5;
        //pos 定位 在一个32位的bi数组中的位置
        int pos = sid - (bitmap_index << 5);

        unsigned int p = 1 << pos;
        p = ~p;
        unsigned int slot = *(bitmap-bitmap_index);
        slot = p & slot;
        *(bitmap-bitmap_index) = slot;
        return true;
    }
    //TODO 调用该函数之前许需要判断是否位发生冲突
    // 获取该页第一个未被使用的槽位，获得其sid。sid  <= slot_num + 1
    int findFreeSid() {
        int sid = 0;
        //遍历每一个4字节的位图
        //printf("slot_int_num: %d\n",slot_int_num);
        printf("slot_num: %d; page_header_size: %d\n",slot_num,*(page_header+1));
        int slot_int_num = slot_num>>5;
        for(int j = 0 ; j <slot_int_num+1 ; ++j) {
            unsigned int slot = *(bitmap-j);
            unsigned int t = 1;
            //遍历4字节的所有位
            for (int i = 0; i <= 31; ++i) {
                unsigned int temp = slot >> i;
                unsigned int result = temp & t;
                if (result == 0) {
                    if((sid+i) > slot_num+1) {
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
        unsigned int slot = *(bitmap-bitmap_index);
        slot = p | slot;
        *(bitmap-bitmap_index) = slot;
        return true;
    }
    //返回目前使用的槽数
    int getSlotNum(){
        if(slot_num==*(page_header+1))
            return *(page_header+1);
        printf("slot_num error");
    }

    //返回空闲字节数目
    int getFreeCnt(){
        return *(page_header+2);
    }

    //返回第一个空闲空间字节偏量
    int getFreeDataOffset(){
        return *(page_header+3);
    }

};
#endif //PAGE_BITMAP_H
