//
// Created by dalaoshe on 16-11-6.
//

#ifndef FILESYSTEM_BUCKETPAGEMANAGER_H
#define FILESYSTEM_BUCKETPAGEMANAGER_H

#include "../utils/pagedef.h"
#include "index_util.h"
/*
 * 指针桶页管理器
 */
class BucketPageManager {

    //索引页首地址
    BufType page;
    /*
     * 文件头页规定信息
     */
    //该页记录的最多索引项数量
    int max_num;
    //该页记录的最少索引项数量
    int min_num;
    //索引码的长度
    int key_byte_size;
    //索引的byte长度
    int index_byte_size;
    //索引码的偏移量
    int key_offset;
    //索引码的数据类型
    int key_type;
    //该页的页头长度byte
    int page_header_size;

    //该页在索引文件中指针
    Pointer pointer;
    /*
     * 页头信息
     */
    //是否是叶级页
    bool isleaf;
    //页链，下页页号，如果是指针桶页则指向下一个指针桶
    int next_page_id;
    //该页记录的索引项数量
    int index_num;
    //该页的类型
    int page_type;


    BucketPageManager(BufType page,int key_offset, int key_byte_size, int index_byte_size, int page_header_size, int key_type,int max_num,
                      int min_num, Pointer pointer) {
        this->init(page, pointer);

        this->max_num = max_num;
        this->min_num = min_num;
        this->index_byte_size = index_byte_size;
        this->key_byte_size = key_byte_size;
        this->key_offset = key_offset;
        this->key_type = key_type;
        this->page_header_size = page_header_size;
    }

    void init(BufType page,Pointer pointer) {
        this->pointer = pointer;
        this->page = page;
        /*
         * 第一个字节给出是否是页级叶
         * 第5个字节给出页级页的下页指针
         * 第9个字节存最大的索引记录偏移
         *
         */
        this->isleaf = *(bool*)page;
        this->next_page_id = *(((int *)page)+1);
        this->index_num = *(((int *)page)+2);
        this->page_type = *(((int *)page)+3);
    }

    void reset(BufType page, Pointer pointer) {
        this->init(page,pointer);
    }

    void initBucketPageInfo() {
        *(bool*)page = this->isleaf = false;
        *(((unsigned int *)page)+1) = this->next_page_offset = -1;
        *(((unsigned int *)page)+2) = this->last_offset = page_header_size;
        *(((unsigned int *)page)+3) = this->index_num = 0;
    }

    void insert(Key key,Pointer pointer) {
        char *p = (char*)page;
        p = p + page_header_size + index_num * index_byte_size;
        key.writeback(p+key_offset,key_byte_size);
        p += key_offset + key_byte_size;
        pointer.writeback(p);
        p += 8;
        *(int *)p = IndexType::id;
        this->index_num += 1;
    }

    bool canInsert() {
        return this->index_num < this->max_num;
    }
    bool hasNextBucket() {
        return this->next_page_id != -1;
    }

    int getNextPid() {
        return this->next_page_id;
    }
    void setNextPid(int pid) {
        return this->next_page_id = pid;
    }
    void writeback() {
        *(bool*)page = this->isleaf ;
        *(((unsigned int *)page)+1) = this->next_page_offset ;
        *(((unsigned int *)page)+2) = this->last_offset ;
        *(((unsigned int *)page)+3) = this->index_num ;
    }
};
#endif //FILESYSTEM_BUCKETPAGEMANAGER_H
