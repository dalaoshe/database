//
// Created by dalaoshe on 16-10-16.
//

#ifndef RECORD_H
#define RECORD_H

#include <cstdio>
#include <stdint.h>
#include "../utils/pagedef.h"
struct RID{
    int pid;
    int sid;
};
bool operator < (const RID l, const RID r) {
    return l.pid < r.pid || ((l.pid == r.pid) && l.sid < r.sid);
}
class Record{
    RID rid;
    //记录的copy的首地址
    BufType data;
public:
    RID getRID() const {
        return this->rid;
    }
    void setRID(RID rid) {
        this->rid = rid;
    }
    void setData(BufType data) {
        this->data = data;
    }
    BufType getData() const{
        return this->data;
    }
    Record() {
        data = NULL;
    }
    ~Record() {

    }

    char* getData(int offset) {
        return ((char*)(this->data)) + offset;
    }

    int getHeaderSlotSize() {
        return data[1];
    }

    int getHeaderPageNum() {
        return data[0];
    }

    Record(RID rid, BufType data) {
        this->rid = rid;
        this->data = data;
    }

    void print() {
        if(data == NULL) {
            printf("NULL RECORD!\n");
            return;
        }
        printf("pid: %d sid: %d data[0]: %d\n",rid.pid,rid.sid,data[0]);
    }
    //设置第i列为null标记(0)
    void setNULL(int i) {
        char* null_map = ((char*)data) + RECORD_NULL_BITMAP;
        //第几个byte
        int byte_pos = i >> 3;
        //该byte的第几位
        int index = i % 8;
        uint8_t a = null_map[byte_pos];
        uint8_t b = 1;
        b = b << index;
        b = ~b;
        a = b & a;
        null_map[byte_pos] = a;
    }
    //设置第i列为非null标记(1)
    void setNotNULL(int i) {
        char* null_map = ((char*)data) + RECORD_NULL_BITMAP;
        //第几个byte
        int byte_pos = i >> 3;
        //该byte的第几位
        int index = i % 8;
        uint8_t a = null_map[byte_pos];
        uint8_t b = 1;
        b = b << index;
        a = b | a;
        null_map[byte_pos] = a;
     //   cout<<"bit: "<<unsigned(a) <<" "<<unsigned(b)<<endl;
    }

    bool isNULL(int i) {
        char* null_map = ((char*)data) + RECORD_NULL_BITMAP;
        //第几个byte
        int byte_pos = i >> 3;
        //该byte的第几位
        int index = i % 8;
        uint8_t a = null_map[byte_pos];
        uint8_t b = 1;
        b = b << index;
        a = b & a;
     //   cout<<"bit: "<<unsigned(a) <<" "<<unsigned(b)<<endl;
        return a == 0;
    }
};

#endif //RECORD_H
