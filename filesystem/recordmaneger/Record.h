//
// Created by dalaoshe on 16-10-16.
//

#ifndef RECORD_H
#define RECORD_H

#include <cstdio>
#include ""
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
    //设置第i列为null标记
    void setNULL(int i) {
        char* null_map = ((char*)data)+RECORD_
        //第几个byte
        int byte_pos = i >> 3;
        //该byte的第几位
        int index = i % 8;
        uint_8 a = ;
        uint_8 b = 1;
        b = b << index;

        memset(a,0, sizeof(a));

    }
    //设置第i列为非null标记
    void setNotNULL(int i) {

    }
};

#endif //RECORD_H
