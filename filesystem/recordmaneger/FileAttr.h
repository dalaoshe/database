//
// Created by ykd on 16-11-29.
//

#ifndef DATABASE_FILEATTR_H
#define DATABASE_FILEATTR_H

#include <string.h>
#include "../utils/base.h"
#include <vector>
#include <map>
#include "../utils/pagedef.h"
#include "../utils/rc.h"
#include "../parse/sql/InsertStatement.h"
#include "../parse/sql/UpdateStatement.h"
#include "../parse/sql/DeleteStatement.h"
#include "../parse/sql/SelectStatement.h"
#include "Record.h"
using namespace hsql;
using namespace std;
//管理一个文件（表头）信息
class RM_FileAttr{
public:
    vector<string> key_name;
    //列的数据类型
    vector<AttrType> key_type;
    vector<int> value_length;
    vector<int> not_null;
    //列的类型 索引列、unique、primary
    vector<ColType> col_type;
    vector<Expr*> check_exprs;
    unsigned int* page_header;
    int page_ID;
    int record_int_size;
    int attr_count;
    int last_page_id;
    int free_pageId;

    /**
     * 构造函数
     */
    RM_FileAttr(){
    }
    ~RM_FileAttr(){

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
    /**
     *
     */
    int initFileAttrToPageHeader(unsigned int* page_header) {
        this->page_header = page_header;
        this->attr_count = this->key_name.size();
        //计算每条记录的长度（INT长度）
        this->record_int_size = 0;
        //所有数据列的长度和
        for(int i = 0 ; i < this->attr_count ; ++i) {
            this->record_int_size += this->value_length[i];
        }
        //数据行状态位长度
        this->record_int_size += RECORD_FIX_DATA;
        //转成int长度
        this->record_int_size = (this->record_int_size >> 2) + 1;
        //保证每条记录的长度不小于最小长度
        if(this->record_int_size < RECORD_MIN_INT_SIZE) this->record_int_size = RECORD_MIN_INT_SIZE;
        //0 本页pageID
        //1 record_int_size
        //2 attr_size 字段数
        //3 最近空闲页(无记录)pageID
        //4 当前最后一页的pid(初始为1)
        //.....
        //自32起，每32bytes为一个字段的定义
        //key_name 20,key_type 4,null 4,length 4

        //0 头页ID 0
        page_header[0] = 0;
        //1 该表每条记录的最大INT长度
        page_header[TABLE_RECORD_INT_SIZE_INT_OFFSET] = this->record_int_size;
        //2 attr_count 字段数（列数）
        page_header[TABLE_ATTR_COUNT_INT_OFFSET] = this->attr_count;
        //3 建表时第一个空闲页ID为1
        page_header[TABLE_FREE_PAGE_INT_OFFSET] = 1;
        //4 建表时最后一页的pid为1
        page_header[TABLE_LAST_PAGEID_INT_OFFSET] = 1;

        //定位到第一个列属性信息的记录位置
        page_header += ATTR_INT_OFFSET;

        for(int i=0; i < attr_count; ++i) {
            const char* name = this->key_name[i].c_str();
            //列名最长19字节 + '\0'(20字节)
            for(int j=0; j < this->key_name[i].length() ; ++j) {
                *((char*)(page_header)+j) = *(name+j);
            }
            *((char*)(page_header)+this->key_name[i].length()) = '\0';

            //5 列数据类型
            page_header[ATTR_VALUE_TYPE_INT_OFFSET] = this->key_type[i];
            //6 列数据长度
            page_header[ATTR_VALUE_LENGTH_INT_OFFSET] = this->value_length[i];
            //7 列是否为空
            page_header[ATTR_NOT_NULL_INT_OFFSET] = this->not_null[i];
            //8 列为列的类型
            page_header[ATTR_TYPE_INT_OFFSET] = this->col_type[i];
            //定位到下一个列属性信息的起始位置
            page_header += ATTR_INT_SIZE;
        }

    }

    int initFileAttrCheckToPageHeader(unsigned int* page_header) {
        //定位到CHECK域
        BufType check = page_header + TABLE_CHECK_INT_OFFSET;
        //初始化每一列的CHECK项信息
        for(int i = 0; i < this->attr_count; ++i) {

            Expr* check_expr = check_exprs[i];

            //找到这列的check记录
            BufType check_record = check + i * ATTR_CHECK_INT_SIZE;
            //TODO 获取可选项数量

            int check_entry_number = 0;
            //初始化CHECK项数目，默认为0
            if(check_expr == NULL) {
                check_entry_number = 0;
            }

            check_record[ATTR_CHECK_NUMBER_INT_OFFSET] = check_entry_number;
            //定位到第一个CHECK项
            check_record = check_record + ATTR_CHECK_RECORD_HEADER_INT_OFFSET;
            //获取这列的属性类型
            AttrType value_type = this->key_type[i];
            //获取这列的数据长度
            int value_len = this->value_length[i];
            //记录每一项的可能值
            for(int j = 0 ; j < check_entry_number; ++j) {
                //TODO 获取该项的限制方法，默认为EQUAL
                CompOp op = CompOp::EQ_OP;
                //TODO 获取该项的限制值
                char* target_v;
                //定位到这一项
                BufType check_entry = ((BufType)(((char*)check_record) + value_len * j)) + ATTR_CHECK_ENTRY_VALUES_INT_OFFSET * j;
                //设置符号
                check_entry[ATTR_CHECK_ENTRY_OP_INT_OFFSET] = op;
                //设置限制值
                char* check_v = (char*)(check_record + ATTR_CHECK_ENTRY_VALUES_INT_OFFSET);

                switch (value_type) {
                    case AttrType::FLOAT: {
                        *((float *) check_v) = *((float *) target_v);
                        break;
                    }
                    case AttrType::INT: {
                        *((int *) check_v) = *((int *) target_v);
                        break;
                    }
                    case AttrType::STRING: {
                        strcpy(check_v,target_v);
                        break;
                    }
                    default:
                        return 1;
                }
            }
        }
    }

    int getFileAttrFromPageHeader(unsigned int* page_header) {
        this->page_header = page_header;
        //清空原来的信息
        this->key_name.clear();
        this->key_type.clear();
        this->value_length.clear();
        this->not_null.clear();
        //获取表信息
        this->page_ID = page_header[0];
        this->record_int_size = page_header[TABLE_RECORD_INT_SIZE_INT_OFFSET];
        this->attr_count = page_header[TABLE_ATTR_COUNT_INT_OFFSET];
        this->free_pageId = page_header[TABLE_FREE_PAGE_INT_OFFSET];
        this->last_page_id = page_header[TABLE_LAST_PAGEID_INT_OFFSET];

        page_header += ATTR_INT_OFFSET;
        //输出每一个列的属性信息
        for(int i=0; i < this->attr_count; ++i) {

            //列名最长19byte + '\0'
            string attr_name = (char*)(page_header);
            AttrType attr_type = (AttrType)(page_header[ATTR_VALUE_TYPE_INT_OFFSET]);
            int attr_length = page_header[ATTR_VALUE_LENGTH_INT_OFFSET];
            int attr_not_null = page_header[ATTR_NOT_NULL_INT_OFFSET];
            ColType coltype = (ColType)page_header[ATTR_TYPE_INT_OFFSET];

            this->key_name.push_back(attr_name);
            this->key_type.push_back(attr_type);
            this->value_length.push_back(attr_length);
            this->not_null.push_back(attr_not_null);
            this->col_type.push_back(coltype);

            page_header += ATTR_INT_SIZE;
        }
    }

    void showFileAttrInfo() {
        printf("page_ID: %d\n",page_ID);
        printf("record_int_size: %d\n",record_int_size);
        printf("attr_count: %d\n",attr_count);
        printf("free_pageID: %d\n",free_pageId);
        printf("last_pageID: %d\n",last_page_id);
        for(int i=0; i < this->attr_count; ++i) {


            printf("attr_name: %s \t",this->key_name[i].c_str());
            printf("attr_type: %s\t ",this->getColValTypeName(this->key_type[i]).c_str()) ;
            printf("attr_length: %d\t ",this->value_length[i]) ;
            printf("attr_not_null: %d\t ",this->not_null[i]) ;
            printf("col_type: %s\t\n ",this->getColTypeName(this->col_type[i]).c_str());

        }
    }
    /**
     * 根据插入语句 stmt 构造数据行 data
     * @param stmt
     * @param data
     * @return 报错信息，""表示无错误
     */
    string buildValidInsertData(InsertStatement* stmt, BufType data, std::vector<Expr*> *values) {
        //初始化置所有null位图为0
        char* nullmap = ((char*)data) + RECORD_NULL_BITMAP;
        memset(nullmap,0,RECORD_BITMAP_SIZE);
        Record record;
        record.setData(data);
        //check项约束
        BufType check = data + TABLE_CHECK_INT_OFFSET;
        if (stmt->columns != NULL) { //insert into table(c1,c2,c3...) values(v1,v2,v3...)
            //总共要插入的列数
            int num = (*stmt->columns).size();
            //插入每一个数据列
            for(int i = 0 ; i < num ; ++i) {
                //获取要插入的列名
                char* target_col_name = (*stmt->columns)[i];
                //获取要插入的数据的表达式
                Expr* expr = (*values)[i];
                //判断是否命中
                bool exist = false;
                //该列数据的写入首地址
                char* begin = ((char*)data) + RECORD_FIX_DATA;
                //插入列index，标记null
                int col_index = this->getColIndex(target_col_name);
                //获取该列属性信息
                BufType attr = this->page_header + ATTR_INT_OFFSET;
                int attr_type, not_null, attr_len;
                for(int j = 0 ; j < attr_count ; ++j) {//查询是否存在对应的列
                    char* attr_name = (char*)attr;
                    attr_type = attr[ATTR_VALUE_TYPE_INT_OFFSET];
                    not_null = attr[ATTR_NOT_NULL_INT_OFFSET];
                    attr_len = attr[ATTR_VALUE_LENGTH_INT_OFFSET];
                    if(!strcmp(target_col_name,attr_name)) {//命中
                        exist = true;
                        break;
                    }
                    begin += attr_len;
                    attr += ATTR_INT_SIZE;
                }
                //找到该列
                if(exist) {
                    //判断属性是否合法，若合法则插入相应属性值
                    switch (expr->type) {
                        case kExprLiteralFloat:
                            if(attr_type == AttrType::FLOAT) {
                                *((float*)begin) = expr->fval;
                                record.setNotNULL(col_index);
                            }
                            else {
                                return string("insert type error, ") + string(target_col_name) + " need " + this->getColValTypeName((AttrType)attr_type) + " type\n";
                            }
                            break;
                        case kExprLiteralInt:
                            if(attr_type == AttrType::INT) {
                                *((int *)begin) = expr->ival;
                                record.setNotNULL(col_index);
                            }
                            else {
                                return string("insert type error, ") + string(target_col_name) + " need " + this->getColValTypeName((AttrType)attr_type) + " type\n";
                            }
                            break;
                        case kExprLiteralString:
                            if(attr_type == AttrType::STRING) {
                                strcpy(begin,expr->name);
                                record.setNotNULL(col_index);
                            }
                            else {
                                return string("insert type error, ") + string(target_col_name) + " need " + this->getColValTypeName((AttrType)attr_type) + " type\n";
                            }
                            break;
                        default:
                            return "type\n";
                    }
                }
                else {
                    printf("no such columns\n");
                    return "";
                }

            }
        }
        else {//没有列名，一一对应插入
            int num = (*values).size();
            int attr_type, not_null, attr_len;
            //获取写入数据的写入首地址
            char* begin = ((char*)data) + RECORD_FIX_DATA;
            //获取列属性信息首地址
            BufType attr = this->page_header + ATTR_INT_OFFSET;
            //插入每一个数据列
            for(int i = 0 ; i < num ; ++i) {
                //获取要插入的数据的表达式
                Expr* expr = (*values)[i];
                char* attr_name = (char*)attr;
                attr_type = attr[ATTR_VALUE_TYPE_INT_OFFSET];
                not_null = attr[ATTR_NOT_NULL_INT_OFFSET];
                attr_len = attr[ATTR_VALUE_LENGTH_INT_OFFSET];
                int col_index = this->getColIndex(attr_name);
                BufType check_record = check + col_index * ATTR_CHECK_INT_SIZE;
                //printf("insert coluns: %s\n",attr_name);

                switch (expr->type) {
                    case kExprLiteralFloat:
                        if (attr_type == AttrType::FLOAT) {
                            if(this->checkValues(check_record,(char*)(&(expr->fval)),(AttrType)attr_type,attr_len)) {
                                *((float *) begin) = expr->fval;
                                record.setNotNULL(col_index);
                                break;
                            }
                            //printf("insert float: %f\n",*((float *) begin));
                        } else {
                            return string("insert type error, ") + string(attr_name) + " need " + this->getColValTypeName((AttrType)attr_type) + " type\n";
                        }
                    case kExprLiteralInt:
                        if (attr_type == AttrType::INT) {
                            if(this->checkValues(check_record,(char*)(&(expr->ival)),(AttrType)attr_type,attr_len)) {
                                *((int *) begin) = expr->ival;
                                record.setNotNULL(col_index);
                                break;
                            }
                           // printf("insert int: %d\n",*((int *) begin));
                        }
                        else {
                            return string("insert type error, ") + string(attr_name) + " need " + this->getColValTypeName((AttrType)attr_type) + " type\n";
                        }
                    case kExprLiteralString:
                        if (attr_type == AttrType::STRING) {
                            if(this->checkValues(check_record,expr->name,(AttrType)attr_type,attr_len)) {
                                strcpy(begin, expr->name);
                                record.setNotNULL(col_index);
                                break;
                            }
                  //          printf("insert string: %s\n",begin);
                        }
                        else {
                            return string("insert type error, ") + string(attr_name) + " need " + this->getColValTypeName((AttrType)attr_type) + " type\n";
                        }
                    default:
                        return "type error\n";
                }
                //下一列
                begin += attr_len;
                attr += ATTR_INT_SIZE;
            }
        }

        //检查所有列的not null约束
        for(int i = 0 ; i < this->attr_count; ++i) {
            string col_name = this->key_name[i];
            int n_null = this->not_null[i];
            bool is_null = record.isNULL(i);
            if(is_null && n_null) {//不允许为null的列的值为null
                string error = col_name + " cannot be null..\n";
                return error;
            }
        }
        //成功
        return "";
    }
    bool checkValues(BufType check_record, char* values, AttrType attrType, int value_len) {
        return true;
        //获取该列的所有check限制项数目
        int check_count = check_record[ATTR_CHECK_NUMBER_INT_OFFSET];
        //定位到第一项
        BufType record = check_record + ATTR_CHECK_RECORD_HEADER_INT_OFFSET;
        //只要满足一项即可
        bool valid = false;
        for(int i = 0; i < check_count; ++i) {
            CompOp op = (CompOp)record[ATTR_CHECK_ENTRY_OP_INT_OFFSET];
            char* target_v = (char*)(record + ATTR_CHECK_ENTRY_VALUES_INT_OFFSET);
            char* rec_v = values;


            if(attrType == AttrType::FLOAT) {
                switch (op) {
                    case EQ_OP: {
                        valid = (*(float*)rec_v) == (*(float*)target_v);
                    }
                    case LT_OP: {
                        valid = (*(float*)rec_v) < (*(float*)target_v);
                    }
                    case GT_OP: {
                        valid = (*(float*)rec_v) > (*(float*)target_v);
                    }
                    case LE_OP: {
                        valid = (*(float*)rec_v) <= (*(float*)target_v);
                    }
                    case GE_OP: {
                        valid = (*(float*)rec_v) >= (*(float*)target_v);
                    }
                    case NE_OP: {
                        valid = (*(float*)rec_v) < (*(float*)target_v) || (*(float*)rec_v) > (*(float*)target_v);;
                    }
                    case NO_OP: {
                        valid = target_v == NULL;
                    }
                }
            }
            else if(attrType == AttrType::INT) {
                switch (op) {
                    case EQ_OP: {
                        valid = (*(int*)rec_v) == (*(int*)target_v);
                    }
                    case LT_OP: {
                        valid = (*(int*)rec_v) < (*(int*)target_v);
                    }
                    case GT_OP: {
                        valid = (*(int*)rec_v) > (*(int*)target_v);
                    }
                    case LE_OP: {
                        valid = (*(int*)rec_v) <= (*(int*)target_v);
                    }
                    case GE_OP: {
                        valid = (*(int*)rec_v) >= (*(int*)target_v);
                    }
                    case NE_OP: {
                        valid = (*(int*)rec_v) < (*(int*)target_v) || (*(int*)rec_v) > (*(int*)target_v);;
                    }
                    case NO_OP: {
                        valid = target_v == NULL;
                    }
                }
            }
            else if(attrType == AttrType::STRING) {
                switch (op) {
                    case EQ_OP: {

                        valid = strcmp(rec_v,target_v) == 0;
                    }
                    case LT_OP: {
                        valid = strcmp(rec_v,target_v) < 0;
                    }
                    case GT_OP: {
                        valid = strcmp(rec_v,target_v) > 0;
                    }
                    case LE_OP: {
                        valid = strcmp(rec_v,target_v) <= 0;
                    }
                    case GE_OP: {
                        valid = strcmp(rec_v,target_v) >= 0;
                    }
                    case NE_OP: {
                        valid = strcmp(rec_v,target_v) != 0;
                    }
                    case NO_OP: {
                        valid = target_v == NULL;
                    }
                    case LIKE_OP: {
                        int len = strlen(target_v);
                        //printf("pattern %s len %d\n",target_v,len);
                        string pattern = string(target_v).substr(1,len-2);
                        string rec = string(rec_v);
                        //cout<<"rec "<<rec<<" "<<pattern<<endl;
                        if(rec.find(pattern) == string::npos) {
                            valid = false;
                        }
                        else {
                            valid = true;
                        }
                    }
                }
            }
            if(valid)break;
            //不符合，到下一项
            record = ((BufType)(((char*)record) + value_len)) + ATTR_CHECK_ENTRY_VALUES_INT_OFFSET;
        }
        return valid;
    }
    //打印一个槽记录信息
    string printRecordInfo(BufType data, vector<string>& columns) {
        Record record;
        record.setData(data);
        char* begin = (char*)data;
        //定位到定长数据首地址
        begin += RECORD_FIX_DATA;
        //定位到列属性信息首地址
        BufType attr = this->page_header + ATTR_INT_OFFSET;
        int attr_len,not_null;
        AttrType attr_type;
//        printf("all columns number %d \n",this->attr_count);
        int column_size = columns.size();
        for(int i = 0 ; i < this->attr_count ; ++i) {
            //获取该列的所有属性信息
            char *attr_name = (char *) attr;
            attr_len = attr[ATTR_VALUE_LENGTH_INT_OFFSET];
            if (columns[0] != "*") {
                bool need = false;
                for (int j = 0; j < column_size; ++j) {
                    if (string(attr_name) == columns[j]) {
                        need = true;
                        break;
                    }
                }
                if (!need) {
                    begin += attr_len;
                    attr += ATTR_INT_SIZE;
                    continue;
                }
            }
            attr_type = (AttrType) attr[ATTR_VALUE_TYPE_INT_OFFSET];
            not_null = attr[ATTR_NOT_NULL_INT_OFFSET];
//            printf("columns name: %s\t",attr_name);
            int col_index = this->getColIndex(attr_name);
            printf("%d\n",col_index);
            if(record.isNULL(col_index)) {
                printf("null  \t");
            }
            else {
                switch (attr_type) {
                    case INT: {//int
                        int val = (*((int *) begin));
                        printf("%d  \t", val);
                        break;
                    }
                    case FLOAT: {//float
                        float val = (*((float *) begin));
                        printf("%f  \t", val);
                        break;
                    }
                    case STRING: {//string
                        printf("%s   \t", begin);
                        break;
                    }
                    default: {
                        printf("error%s\n");
                        return "type\n";
                    }
                }
            }
            //下一列
            begin += attr_len;
            attr += ATTR_INT_SIZE;
        }
        printf("\n");
        return "";
    }

    /**
     * 获取col_name 的数据列 数据类型
     * @param col_name
     * @return
     */
    AttrType getColValueType(string col_name) {
        for(int i = 0 ; i < this->attr_count ; ++i) {
            if(col_name == this->key_name[i]) return this->key_type[i];
        }
    }

    /**
     * 获取col_name 的数据列 数据长度
     * @param col_name
     * @return
     */
    int getColValueSize(string col_name) {
        for(int i = 0 ; i < this->attr_count ; ++i) {
            if(col_name == this->key_name[i]) return this->value_length[i];
        }
    }
    /**
     * 获取col_name 的数据列 在数据行第几列
     * @param col_name
     * @return
     */
    int getColIndex(string col_name) {
        for(int i = 0 ; i < this->attr_count ; ++i) {
            if(col_name == this->key_name[i]) return i;
        }
    }
    /**
     * 获取col_name 的数据列的数据在数据槽的偏移
     * @param col_name
     * @return
     */
    int getColValueOffset(string col_name) {
        int offset = RECORD_FIX_DATA;
        for(int i = 0 ; i < this->attr_count ; ++i) {
            if(col_name == this->key_name[i]) return offset;
            offset += this->value_length[i];
        }
    }
    /**
     * 获取col_name 的数据列 列类型
     * @param col_name
     * @return
     */
    ColType getColType(string col_name) {
        for(int i = 0 ; i < this->attr_count ; ++i) {
            if(col_name == this->key_name[i]) return this->col_type[i];
        }
    }
    /**
     * 修改头页对应列的列类型，保存到内存中
     * @param col_name
     * @param type
     */
    void setColType(string col_name, ColType type) {
        BufType page_header = this->page_header;
        page_header += ATTR_INT_OFFSET;
        for(int i = 0 ; i < this->attr_count ; ++i) {
            if(col_name == this->key_name[i]) {
                page_header[ATTR_TYPE_INT_OFFSET] = type;
                return;
            }
            //定位到下一个列属性信息的起始位置
            page_header += ATTR_INT_SIZE;
        }
    }

    string getIndexName(string table_name, string col_name) {
        string indexName = table_name + "." + col_name;
        return indexName;
    }

    string getColTypeName(ColType type) {
        switch(type) {
            case ColType::INDEX:{
                return "INDEX";
            }
            case ColType::NORMAL: {
                return "NORMAL";
            }
            case ColType::PRIMARY: {
                return "PRIMARY";
            }
            case ColType::UNIQUE: {
                return "UNIQUE";
            }
            default: {
                return "NORMAL";
            }
        }
    }
    string getColValTypeName(AttrType type) {
        switch(type) {
            case AttrType::INT:{
                return "INT";
            }
            case AttrType::FLOAT: {
                return "FLOAT";
            }
            case AttrType::STRING: {
                return "VARCHAR";
            }
            default: {
                return "INT";
            }
        }
    }
    /**
     * 获取Primary列的列名
     * @return
     */
    string getPrimaryKeyName() {
        for(int i = 0 ; i < this->attr_count ; ++i) {
            if(this->col_type[i] == ColType::PRIMARY) {
                return this->key_name[i];
            }
        }
        return "";
    }
    /**
     * 
     * @return
     */
    vector<string> getIndexKeyNameList() {
        vector<string> list;
        for(int i = 0 ; i < this->attr_count ; ++i) {
            if(this->col_type[i] == ColType::PRIMARY || this->col_type[i] == ColType::INDEX || this->col_type[i] == ColType::UNIQUE) {
                list.push_back(this->key_name[i]);
            }
        }
        return list;
    }
};


#endif //DATABASE_FILEATTR_H
