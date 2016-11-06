//
// Created by dalaoshe on 16-10-16.
//

#ifndef RECORD_H
#define RECORD_H

#include <cstdio>
struct RID{
    int pid;
    int sid;
};
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

    BufType getData(int offset) const {
        return this->data + offset;
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
};

#endif //RECORD_H
