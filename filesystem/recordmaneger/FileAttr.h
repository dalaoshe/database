//
// Created by ykd on 16-11-29.
//

#ifndef DATABASE_FILEATTR_H
#define DATABASE_FILEATTR_H

#include "../utils/base.h"
#include <vector>

using namespace std;
class RM_FileAttr{
public:
    vector<string> key_name;
    vector<AttrType> key_type;
    vector<int> value_length;
    vector<int> not_null;

    /**
     * 构造函数
     */
    RM_FileAttr(){
    }
    /**
     * 功能：获取定长数据长度
     * @return
     */
    int getFsize(){
        int size = 0;
        int count = value_length.size();
        for(int i=0;i<count;++i)
            //TODO 判断是否为定长数据
            size += value_length[i];
        return size;
    }
};
#endif //DATABASE_FILEATTR_H
