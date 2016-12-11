//
// Created by dalaoshe on 16-11-7.
//

#ifndef FILESYSTEM_INDEX_UTIL_H
#define FILESYSTEM_INDEX_UTIL_H
#include "../utils/base.h"
namespace IndexType {
    enum {
        cluster = 1,
        bucket = 2,
        id = 3,
        index = 4,
        valid = 5,
        invalid = 6,
    };
};
struct Key{
    char* key;
    Key(char* key) {
        this->key = key;
    }
    void writeback(char* page, int len) {
        for(int i = 0 ; i < len ; ++i) {
            *(page+i) = *(key+i);
        }
    }
    bool equal(Key target, int len) {
        char* t = target.key;
        for(int i = 0 ; i < len ; ++i) {
            char a = *(key+i);
            char b = *(t+i);
            if(a != b) return false;
        }
        return true;
    }

    bool less(Key target, int len,int key_type) {
        char* t = target.key;
        switch(key_type){
            case INT:{
                return *(int*)key < *(int*) t;
            }
            case FLOAT:{
                return *(float *)key < *(float *) t;
            }
            case STRING:{
                for(int i = 0 ; i < len ; ++i) {
                    char a = *(key+i);
                    char b = *(t+i);
                    if((int)a >= (int)b) return false;
                }
                return true;
            }
        }
        return true;
    }
    bool greater(Key target, int len,int key_type) {
        char* t = target.key;
        switch(key_type){
            case INT:{
//                len = (len>>2);
//                for(int i = 0 ; i < len  ; ++i) {
//                    int a = *(int*)(key+i*4);
//                    int b = *(int*)(t+i*4);
//                    if(a <= b) return false;
//                }
                printf("key type: INT, target: %d, key: %d\n",*(int*) t,*(int*)key);
                return *(int*)key > *(int*) t;
               // return true;
            }
            case FLOAT:{
//                len = (len>>3);
//                for(int i = 0 ; i < len  ; ++i) {
//                    float a = *(float*)(key+i*8);
//                    float b = *(float*)(t+i*8);
//                    if(a <= b) return false;
//                }
                printf("key type: FLOAT\n");
                return *(float *)key > *(float *) t;
                //return true;
            }
            case STRING:{
                for(int i = 0 ; i < len ; ++i) {
                    char a = *(key+i);
                    char b = *(t+i);
                    if((int)a <= (int)b) return false;
                }
                return true;
            }
        }
        return true;
    }
};
/*
 * 指向一条索引记录的起始地址
 */
struct Pointer{
    //页id
    int pid;
    //在该页的偏移(若是rid记录则为sid)
    int offset;
    //pointer为索引行的索引指针地址
    Pointer(char* pointer) {
        unsigned int* p = (unsigned int *)pointer;
        this->pid = *(p);
        this->offset = *(p+1);
    }
    Pointer(int pid, int offset) {
        this->pid = pid;
        this->offset = offset;
    }
    void writeback(char* page) {
        int *p = (int *)page;
        *(p) = pid;
        *(p+1) = offset;
    }
    Pointer(){}
};
#endif //FILESYSTEM_INDEX_UTIL_H
