//
// Created by dalaoshe on 16-10-16. 每一个页的位图管理器
//

#ifndef PAGE_BITMAP_H
#define PAGE_BITMAP_H

#include "../utils/pagedef.h"
struct PageBitmap{
    //address page bitmap
    //页头中存储的变量


    //该页已经使用的槽数
    int slot_used_number;
    //该页最多能存放的槽数量
    int slot_max_number;
    //该页能存的槽位总数/32 （即需要几个int类型的位图来记录）
    int slot_int_num;

    //该页槽大小slot_size = slot_int_size * 4 byte
    int slot_int_size;
    //该页是否已满
    int page_is_full;
    //pageID 4 Bytes
    //slot_num 4 Bytes
    //free_cnt 4 Bytes
    //free_data 4 Bytes


    // 页头
    unsigned int *page_header;
    //第一个数据行（槽位）的首地址
    unsigned int *pageData;
    //位图(32位行偏移数组)
    unsigned int *bitmap;



    PageBitmap(unsigned int* bitmap) {
        if(bitmap != NULL) {
            this->page_header = bitmap;
            this->bitmap = bitmap + PAGE_INT_SIZE - 1;
            this->pageData = bitmap + PAGE_HEADER_INT_SIZE;

            this->slot_used_number = this->page_header[PAGE_SLOT_USED_NUMBER_INT_OFFSET];
            this->slot_int_size = this->page_header[PAGE_SLOT_INT_SIZE_INT_OFFSET];
            this->slot_max_number = this->page_header[PAGE_SLOT_MAX_NUMBER_INT_OFFSET];
            this->page_is_full = this->page_header[PAGE_SLOT_IS_FULL_INT_OFFSET];
            this->slot_int_num = this->page_header[PAGE_SLOT_INT_NUM_INT_OFFSET];
        }
    }
    /**
     * 获取给定数据页的页头信息
     * @param bitmap
     */
    void setBitmap(unsigned int* bitmap) {
        if(bitmap != NULL) {
            this->page_header = bitmap;
            this->bitmap = bitmap + PAGE_INT_SIZE - 1;
            this->pageData = bitmap + PAGE_HEADER_INT_SIZE;

            this->slot_used_number = this->page_header[PAGE_SLOT_USED_NUMBER_INT_OFFSET];
            this->slot_int_size = this->page_header[PAGE_SLOT_INT_SIZE_INT_OFFSET];
            this->slot_max_number = this->page_header[PAGE_SLOT_MAX_NUMBER_INT_OFFSET];
            this->page_is_full = this->page_header[PAGE_SLOT_IS_FULL_INT_OFFSET];
            this->slot_int_num = this->page_header[PAGE_SLOT_INT_NUM_INT_OFFSET];
        }
    }

    void setSlotSize(int slot_int_size) {
        this->slot_int_size = slot_int_size;
        //可以使用的最大槽数（页大小-页头-位图占用/每个槽的大小）
        this->slot_max_number = (PAGE_SIZE - PAGE_HEADER_INT_SIZE * 4 - RECORD_BITMAP_SIZE) / (slot_int_size << 2);
        //需要多少个int类型位图来标记每个槽的使用情况
        this->slot_int_num = (this->slot_max_number >> 5);
        if((this->slot_max_number - (this->slot_int_num << 5) > 0)) this->slot_int_num ++;
    }


    void writebackHeaderInfo() {
        this->page_header[PAGE_SLOT_USED_NUMBER_INT_OFFSET] = this->slot_used_number;
        this->page_header[PAGE_SLOT_INT_SIZE_INT_OFFSET] = this->slot_int_size;
        this->page_header[PAGE_SLOT_MAX_NUMBER_INT_OFFSET] = this->slot_max_number;
        this->page_header[PAGE_SLOT_IS_FULL_INT_OFFSET] = this->page_is_full;
        this->page_header[PAGE_SLOT_INT_NUM_INT_OFFSET] = this->slot_int_num;
    }

    /**
     * 标记该槽位为未使用
     * @param sid
     * @return
     */
    bool deleteSlot(int sid) {
        if(sid >= this->slot_max_number || sid < 0){
            printf("delete slot; sid overflows!");
            return false;
        }
        //bitmap_index = sid / 32 定位槽位号所在的位图index
        int bitmap_index = sid >> 5;
        //pos 定位 在一个32位的bi数组中的位置
        int pos = sid - (bitmap_index << 5);
        unsigned int p = 1 << pos;
        unsigned int slot = *(bitmap-bitmap_index);
        //判断原来是否是1
        unsigned int old = slot & p;
        if(old == 0) {
            printf("delete slot; sid not used!");
            return false;
        }

        p = ~p;
        slot = p & slot;
        *(bitmap-bitmap_index) = slot;
        return true;
    }

    /**
     *     获取该页第一个未被使用的槽位，获得其sid。sid  <= slot_num + 1
           sid < slot_max_number
     * @return sid
     */
    int findFreeSid() {
        int sid = 0;
        //遍历每一个4字节的位图
        //printf("slot_int_num: %d\n",slot_int_num);
        printf("slot_max_num: %d\n; slot_used_num: %d\n; page_header_size: %d\n",slot_max_number,slot_used_number,*(page_header+1));
        for(int j = 0 ; j < this->slot_int_num ; ++j) {
            unsigned int slot = *(bitmap-j);
            unsigned int t = 1;
            //遍历4字节的所有位
            for (int i = 0; i <= 31; ++i) {
                unsigned int temp = slot >> i;
                unsigned int result = temp & t;
                if (result == 0) {//该位可用
                    if((sid+i) > slot_max_number-1) {
                        return -1;
                    }
                    return sid + i;
                }
            }
            sid += 32;
        }
        return -1;
    }
    /**
     * 标记该槽位为已用
     * @param sid
     * @return
     */
    int setSlot(int sid) {
        if(sid >= this->slot_max_number || sid < 0){
            printf("set slot error; sid overflows!");
            return false;
        }
        //bitmap_index = sid / 32 定位槽位号所在的4字节位图index
        int bitmap_index = sid >> 5;
        //pos 定位所在4字节位图的第几位
        int pos = sid - (bitmap_index << 5);
        unsigned int p = 1 << pos;
        unsigned int slot = *(bitmap-bitmap_index);

        //判断原来是否是1
        unsigned int old = slot & p;
        if(old > 0) {
            printf("set slot; sid has used!");
            return false;
        }

        slot = p | slot;
        *(bitmap-bitmap_index) = slot;
        return true;
    }
    //返回目前使用的槽数
    int getSlotUsedNumber(){
        return this->slot_used_number;
    }

    //返回空闲字节数目
    int getFreeCnt(){
        return *(page_header+2);
    }

    //返回第一个空闲空间字节偏量
    int getFreeDataOffset(){
        return *(page_header+3);
    }

    bool isSlotUsed(int sid) {
        if(sid >= this->slot_max_number || sid < 0){
            printf("set slot error; sid overflows!");
            return true;
        }
        //bitmap_index = sid / 32 定位槽位号所在的4字节位图index
        int bitmap_index = sid >> 5;
        //pos 定位所在4字节位图的第几位
        int pos = sid - (bitmap_index << 5);
        unsigned int p = 1 << pos;
        unsigned int slot = *(bitmap-bitmap_index);

        //判断原来是否是1
        unsigned int old = slot & p;
        if(old > 0) {
            printf("is used!\n");
            return true;
        }
        return false;
    }

};
#endif //PAGE_BITMAP_H
