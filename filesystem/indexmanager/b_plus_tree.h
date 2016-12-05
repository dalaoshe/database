//
// Created by dalaoshe on 16-11-6.
//

#ifndef FILESYSTEM_B_PLUS_TREE_H
#define FILESYSTEM_B_PLUS_TREE_H

#include "../utils/pagedef.h"
#include "IndexPageManager.h"
#include "../recordmaneger/Record.h"
#include "index_util.h"
/*
 *  n+1个索引码和n+1个索引指针
 *  其中0索引码为空值
 *  pi指针指向的索引码均大于索引码ki-1,小于索引码ki
 */

struct Node
{

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

    Node(){};
    Node(BufType page,int key_offset, int key_byte_size, int index_byte_size, int page_header_size, int key_type,int max_num,
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
    bool isLeaf() { return this->isleaf; }

    Key getKey(int i) {
        char *p = (char*)page;
        p = p + page_header_size + i * index_byte_size + key_offset;
        return Key(p);
    }

    int getTag(int i) {
        char *p = (char*)page;
        p = p + page_header_size + i * index_byte_size;
        return *(int *)p;
    }

    Pointer getPointer(int i) {
        char *p = (char*)page;
        p = p + page_header_size + (i-1) * index_byte_size + key_offset + key_byte_size;
        return Pointer(p);
    }

    int getPointerType(int i) {
        char *p = (char*)page;
        p = p + page_header_size + (i-1) * index_byte_size + key_offset + key_byte_size + 8;
        return *(int *)p;
    }
    /*
     * 获取第一个索引码大于key的在该节点的码值位置
     */
    int search(Key key)
    {
        printf("index num : %d\n",index_num);
        if(this->index_num == 0) {
            return 1;
        }
        if(key.less(this->getKey(1),key_byte_size,key_type))
            return 1;
        else if(key.greater(this->getKey(this->index_num),key_byte_size,key_type))
            return this->index_num+1;
        else {
            for (int i = 2; i <= index_num; ++i) {
                Key k1 = this->getKey(i - 1);
                Key k2 = this->getKey(i);
                if ((k1.less(key,key_byte_size,key_type) || k1.equal(key,key_byte_size))
                    && key.less(k2,key_byte_size,key_type)) {
                    return i;
                }
            }
        }
    }
    /*
     * 将缓存中的页面信息读入节点
     */
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
    /*
     * 重设page
     */
    void reset(BufType page,Pointer pointer) {
        this->init(page,pointer);
    }
    /*
     * 将关键码为key的，指针为pointer的项插入该节点
     * 插入操作直接修改缓存，执行后需要标记其为脏页
     */
    void insertKey(Key key, Pointer pointer, int type, int tag) {
        int i = this->search(key);
        int j = this->index_num;
        for(int k = j ; k >= i ; --k) {
            printf("k:%d; i:%d; j:%d\n",k,i,j);

            copyIndex(k,k+1);
        }

        char *p = (char*)page;
        p = p + page_header_size + i * index_byte_size;
        //插入状态位
        *(int *)p = tag;
        //插入索引码
        key.writeback(p+key_offset,key_byte_size);
        p += key_offset + key_byte_size;
        //插入索引指针
        pointer.writeback(p);
        p += 8;
        //插入索引类型
        *(int *)p = type;
        this->index_num += 1;
    }
    /*
     * copy data in index i to index j
     */
    void copyIndex(int i, int j) {
        char *p = (char*)page;
        char *target = p + page_header_size + j * index_byte_size;
        char *source = p + page_header_size + i * index_byte_size;
        for(int k = 0 ; k < index_byte_size ; ++k) {
            *(target+k) = *(source+k);
        }
    }

    bool overflow() {
        return this->max_num < index_num;
    }
    bool downflow() {
        return this->min_num > index_num;
    }
    /*
     * 将页信息写回页头
     */
    void writeback() {
        *(bool*)page = this->isleaf ;
        *(((int *)page)+1) = this->next_page_id ;
        *(((int *)page)+2) = this->index_num ;
        *(((int *)page)+3) = this->page_type ;
    }
    /*
     * 获取分裂轴点
     */
    int getSplit() {
        return (index_num / 2) + 1;
    }
    /*
     * 设置第i个指针
     */
    void setPointer(int i, Pointer pointer) {
        char *p = (char*)page;
        p = p + page_header_size + (i-1)*index_byte_size + key_offset + key_byte_size;
        pointer.writeback(p);
    }
    /*
     * 设置第i个索引的指针类型
     */
    void setPointerType(int i, int type) {
        char *p = (char*)page;
        p = p + page_header_size + (i-1)*index_byte_size + key_offset + key_byte_size + 8;
        *(int *)p = type;
    }
    void setPointerTag(int i, int tag) {
        char *p = (char*)page;
        p = p + page_header_size + (i)*index_byte_size;
        *(int *)p = tag;
    }
    /*
     * 判断索引码k是否存在该节点
     */
    bool exist(Key k) {
        if(this->index_num == 0)return false;
        int i = this->search(k);
        Key key = this->getKey(i-1);
        return k.equal(key,key_byte_size);
    }


};


#endif //FILESYSTEM_B_PLUS_TREE_H
