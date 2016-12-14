//
// Created by ykd on 16-11-28.
//

#ifndef DATABASE_DATABASESYSTEM_H
#define DATABASE_DATABASESYSTEM_H


#include "SM_Manager.h"
#include "../parse/sql/SQLStatement.h"
#include "../parse/SQLParserResult.h"
#include "../parse/SQLParser.h"
#include "../parse/sqlhelper.h"
#include <iostream>
#include <cstring>
#include <map>
using namespace std;
using namespace hsql;

class DatabaseSystem {
    SM_Manager* system_manager;
    IndexManager* indexManager;
    RecordManager* recordManager;
    FileManager* fm;
    BufPageManager* bpm;
public:

    DatabaseSystem() {
        this->fm = new FileManager();
        this->bpm = new BufPageManager(fm);
        this->indexManager = new IndexManager(fm,bpm);
        this->recordManager = new RecordManager(fm,bpm);

        system_manager = new SM_Manager(indexManager,recordManager,fm,bpm);
    }

    ~DatabaseSystem() {

    }

    string readSQL(string sqlStmtList) {
        //解析
        hsql::SQLParserResult* result = hsql::SQLParser::parseSQLString(sqlStmtList);

        // check whether the parsing was successful
        if (result->isValid) {
            printf("Parsed successfully!\n");
//            printf("Number of statements: %lu\n", result->size());
            for (hsql::SQLStatement* stmt : result->statements) {
                // process the statements...
                string result = processSQL(stmt);
                printf("%s",result.c_str());
                return result;
            }
        } else {
            return ("Invalid SQL!\n");
        }
    }

    /**
     * 执行sql语句
     * @param stmt
     * @return
     */
    string processSQL(SQLStatement *stmt) {
        switch (stmt->type()){
            case kStmtCreateDB:{
                CreateDBStatement* createDBStatement = (CreateDBStatement*)stmt;
                string db_name(createDBStatement->DBname);
                system_manager->createDB(db_name.c_str());
                return "Create databse "+db_name+" succeed!\n";
            }
            case kStmtDropDB:{
                DropDBStatement* dropDBStatement = (DropDBStatement*)stmt;
                system_manager->dropDB(dropDBStatement->DBname);
                return "Drop databse "+string(dropDBStatement->DBname)+" succeed!\n";
            }
            case kStmtUseDB:{
                UseDBStatement* useDBStatement = (UseDBStatement*)stmt;
                system_manager->OpenDB(useDBStatement->DBname);
                return "Use databse "+string(useDBStatement->DBname)+" succeed!\n";
            }
            case kStmtShowDB:{
                system_manager->ShowDatabases();
                return "Showing databses succeed!\n";
            }
            case kStmtCreateIndex:{
                CreateIndexStatement* createIndexStatement = (CreateIndexStatement*)stmt;
                system_manager->CreateIndex(createIndexStatement->table,createIndexStatement->column);
                return "Create Index succeed!\n";
            }
            case kStmtDropIndex:{
                DropIndexStatement* dropIndexStatement = (DropIndexStatement*)stmt;
                system_manager->DropIndex(dropIndexStatement->table,dropIndexStatement->column);
                return "";
            }
            case kStmtShowTable:{
                system_manager->ShowTables();
                return "";
            }
            case kStmtDesc:{
                DescStatement* descStatement = (DescStatement*)stmt;
                system_manager->ShowSchema(descStatement->table_name);
                return "";
            }
            case kStmtCreate:{
                CreateStatement* createStatement = (CreateStatement*)stmt;
                printCreateStatementInfo(createStatement,0);
                int attrCount = createStatement->columns->size();
                for(int i=0;i<attrCount;++i){
                    printf("attr_name: %s \t  ",(*(createStatement->columns))[i]->name);
                    printf("attr_type: %d \t  ",(*(createStatement->columns))[i]->type);
                    printf("attr_size: %d \t  ",(*(createStatement->columns))[i]->size);
                    printf("attr_not_null: %d\t",(*(createStatement->columns))[i]->not_null);
                    if(strcmp((*(createStatement->columns))[i]->name,createStatement->primary_key) == 0) {
                        printf("attr_col_type: %s\t\n","PRIMARY");
                    }
                    else{
                        printf("attr_col_type: %s\t\n","NORMAL");
                    }
                }
                RM_FileAttr* attr = new RM_FileAttr[1];
                for(int i=0;i<attrCount;++i){
                    attr->key_name.push_back(string((*(createStatement->columns))[i]->name));
                    attr->key_type.push_back((*(createStatement->columns))[i]->type);
                    attr->value_length.push_back((*(createStatement->columns))[i]->size);
                    int k = (*(createStatement->columns))[i]->not_null;
                    attr->not_null.push_back(k);

                    if(strcmp((*(createStatement->columns))[i]->name,createStatement->primary_key) == 0) {
                        attr->col_type.push_back(ColType::PRIMARY);
//                        printf("attr_col_type: %s\t\n","PRIMARY");
                    }
                    else{
                        attr->col_type.push_back(ColType::NORMAL);
                        //printf("attr_col_type: %s\t\n","NORMAL");
                    }
                }
                system_manager->CreateTable(createStatement->tableName,attrCount,attr);
                printf("create table ok\n");
                if(createStatement->primary_key != NULL) {
                    system_manager->CreateIndex(createStatement->tableName, createStatement->primary_key,
                                                ColType::PRIMARY);
                }
                return "";
            }
            case kStmtDrop:{
                DropStatement* dropStatement = (DropStatement*)stmt;
                system_manager->DropTable(dropStatement->name);
                return "";
            }
            case kStmtInsert:{
                //打印语句信息
                printInsertStatementInfo((InsertStatement*)stmt, 0);
                printf("insert options\n");

                InsertStatement* insertStmt = (InsertStatement*)stmt;
                //获取要插入的表名
                string filename = insertStmt->tableName;
                RM_FileHandle fileHandle;
                //获取rm handle
                recordManager->openFile(filename.c_str(),fileHandle);
                BufType fileHeader = fileHandle.getFileHeader();
                //获取表头信息
                RM_FileAttr* fileAttr = new RM_FileAttr();
                fileAttr->getFileAttrFromPageHeader(fileHeader);
                //获取要插入的数据块data
                BufType data = new unsigned int[fileHandle.getFileHeader()[TABLE_RECORD_INT_SIZE_INT_OFFSET]];

                std::vector<std::vector<Expr*>*>* values = insertStmt->values;
                int entry_size = values->size();
                for(int s = 0 ; s < entry_size; ++s) {
                    string info = fileAttr->buildValidInsertData(insertStmt, data, (*values)[s]);
                    if (info != "") {
                        printf("%s", info.c_str());
                        delete fileAttr;
                        return "";
                    }

                    //获取所有的索引项列名
                    vector <string> list = fileAttr->getIndexKeyNameList();


                    //检查是否有主键约束
                    if (fileAttr->getPrimaryKeyName() != "") {
                        //获取主键约束的列名
                        string primary_col_name = fileAttr->getPrimaryKeyName();
                        string indexName = fileAttr->getIndexName(insertStmt->tableName, primary_col_name);
                        IX_IndexHandle indexHandle;
                        this->indexManager->OpenIndex(indexName.c_str(), indexHandle);
                        //获取待插入的主键值
                        int offset = fileAttr->getColValueOffset(primary_col_name.c_str());

                        char *key = ((char *) (data)) + offset;
                        int type, tag;
                        Pointer p;
                        //检查是否存在
                        if (indexHandle.searchEntry(key, p, type, tag).equal(RC()) &&
                            tag == IndexType::valid) {//如果存在,报错。
                            printf("primary key: %s, dumplicate\n", fileAttr->getPrimaryKeyName().c_str());
                        } else {//插入数据，并插入索引
                            RID rid;
                            fileHandle.insertRec(data, rid);
                            printf("rid pid %d sid %d\n", rid.pid, rid.sid);
                            //插入主键索引
                            indexHandle.InsertEntry(key, rid);
                            indexHandle.close();
                            //插入其余索引
                            Record record;
                            record.setData(data);
                            record.setRID(rid);
                            int index_entry_numbers = list.size();
                            for (int i = 0; i < index_entry_numbers; ++i) {

                                //获取索引的列名
                                string index_col_name = list[i];
                                //创建handle
                                string indexName = fileAttr->getIndexName(insertStmt->tableName, index_col_name);
                                IX_IndexHandle indexHandle;
                                this->indexManager->OpenIndex(indexName.c_str(), indexHandle);
                                //获取待插入的索引码值
                                int offset = fileAttr->getColValueOffset(index_col_name.c_str());

                                ColType colType = fileAttr->getColType(index_col_name);
                                if (colType == ColType::UNIQUE || colType == ColType::PRIMARY) continue;

                                char *key = record.getData(offset);
                                if (indexHandle.InsertEntry(key, record.getRID()).equal(RC())) {
                                    printf("insert index %s rid<%d,%d> ok\n", indexName.c_str(), record.getRID().pid,
                                           record.getRID().sid);
                                    indexHandle.close();
                                } else {
                                    printf("insert index %s rid<%d,%d> fail\n", indexName.c_str(), record.getRID().pid,
                                           record.getRID().sid);
                                }
                            }
                        }
                    } else {//没有主键和UNIQUE约束，直接插入数据项和索引项
                        RID rid;
                        //插入数据项
                        fileHandle.insertRec(data, rid);
                        Record record;
                        record.setData(data);
                        record.setRID(rid);
                        printf("rid pid %d sid %d\n", rid.pid, rid.sid);
                        //插入索引项
                        int index_entry_numbers = list.size();
                        for (int i = 0; i < index_entry_numbers; ++i) {

                            //获取索引的列名
                            string index_col_name = list[i];
                            //创建handle
                            string indexName = fileAttr->getIndexName(insertStmt->tableName, index_col_name);
                            IX_IndexHandle indexHandle;
                            this->indexManager->OpenIndex(indexName.c_str(), indexHandle);
                            //获取待插入的索引码值
                            int offset = fileAttr->getColValueOffset(index_col_name.c_str());

                            ColType colType = fileAttr->getColType(index_col_name);
                            if (colType == ColType::UNIQUE || colType == ColType::PRIMARY) continue;

                            char *key = record.getData(offset);
                            if (indexHandle.InsertEntry(key, record.getRID()).equal(RC())) {
                                printf("insert index %s rid<%d,%d> ok\n", indexName.c_str(), record.getRID().pid,
                                       record.getRID().sid);
                                indexHandle.close();
                            } else {
                                printf("insert index %s rid<%d,%d> fail\n", indexName.c_str(), record.getRID().pid,
                                       record.getRID().sid);
                            }
                        }
                    }
                }
                delete fileAttr;
                return "";
            }
            case kStmtSelect:{
                //打印语句信息
//                printSelectStatementInfo((SelectStatement*)stmt, 0);
                printf("select options\n");
                vector<Expr::OperatorType> operates;
                vector<string> ope_columns;
                vector<string> no_columns;
                SelectStatement* selectStatement = (SelectStatement*)stmt;
                //获取要选取的列名(表名.列名 形式需要添加)
//                vector<string> columns;
                for (Expr* expr : *selectStatement->selectList){
                    switch (expr->type) {
                        case kExprStar: {
                            printf("*");
                            no_columns.push_back(string("*"));
                            break;
                        }
                        case kExprColumnRef: {
                            printf("%s %s\n", expr->table, expr->name);
                            no_columns.push_back(string(expr->name));
                            break;
                        }
                        case kExprOperator: {
                            switch (expr->op_type) {
                                case Expr::SUM: {
                                    operates.push_back(Expr::SUM);
                                    ope_columns.push_back(string(expr->expr->name));
                                    break;
                                }
                                case Expr::AVG: {
                                    operates.push_back(Expr::AVG);
                                    ope_columns.push_back(string(expr->expr->name));
                                    break;
                                }
                                case Expr::MAX: {
                                    operates.push_back(Expr::MAX);
                                    ope_columns.push_back(string(expr->expr->name));
                                    break;
                                }
                                case Expr::MIN: {
                                    operates.push_back(Expr::MIN);
                                    ope_columns.push_back(string(expr->expr->name));
                                    break;
                                }
                                default: {
                                    printf("operate sum/avg/max/min error \n");
                                    return "";
                                }
                            }
                            break;
                        }
                            // case kExprTableColumnRef: inprint(expr->table, expr->name, numIndent); break;
                        default: {
                            fprintf(stderr, "Unrecognized expression type %d\n", expr->type);
                            return "error";
                        }
                    }
                }
//                获取要选取的表名
                vector<string> filenames;
                if(selectStatement->fromTable->list == NULL)
                    filenames.push_back(selectStatement->fromTable->getName());
                else{
                    unsigned long size = (*selectStatement->fromTable->list).size();
                    for(int i=0;i<size;++i){
                        filenames.push_back((*selectStatement->fromTable->list)[i]->getName());
                    }
                }
//                string filename = selectStatement->fromTable->getName();
                RM_FileHandle fileHandle;
                //TODO 多表!!!!钱目前只查询打开了一个表
                printf("filename: %s   size: %lu\n",filenames[0].c_str(),filenames.size());
                //获取rm handle
                recordManager->openFile(filenames[0].c_str(),fileHandle);
                BufType fileHeader = fileHandle.getFileHeader();
                //获取表头信息
                RM_FileAttr* fileAttr = new RM_FileAttr();
                fileAttr->getFileAttrFromPageHeader(fileHeader);

                map<RID,int>rid_list;
                this->searchRIDListByWhereClause(selectStatement->whereClause,rid_list,fileHandle,0,selectStatement->fromTable->getName());
//                printf("rid size %lu\n",rid_list.size());
//                //获取记录
//                Record record;
//                RID rid; rid.pid=1; rid.sid=6;
//                fileHandle.getRec(rid,record);

                //非聚集查询与聚集查询分开输出

                //非聚集查询
                int no_column_size = no_columns.size();
                if(no_column_size!=0){
                    if(no_columns[0]=="*"){
                        no_columns.clear();
                        for(int i=0;i<fileAttr->attr_count;++i){
                            printf("%s       \t",fileAttr->key_name[i].c_str());
                            no_columns.push_back(fileAttr->key_name[i]);
                        }
                        no_column_size = no_columns.size();
//                        printf("size: %d\n",no_column_size);
                    } else {
                        for(int i=0;i < no_columns.size();++i){
                            printf("%s       \t",no_columns[i].c_str());
                        }
                    }
                    printf("\n");
                    map<RID, int>::iterator it;
                    //循环遍历左边表达式选取的项在右边表达式是否存在
                    for (it = rid_list.begin(); it != rid_list.end(); ++it) {
                        //判断在右边是否存在
                        RID rid = it->first;
//                        printf("rid<%d,%d> \t",rid.pid,rid.sid);
                        Record record;
                        fileHandle.getRec(rid,record);
                        //不存在则下一个
//                        fileAttr->printRecordInfo(record.getData(),no_columns);
                        int offset = 0;
                        char *data;
                        int attr_type = 0;
                        for(int i=0;i<no_column_size;++i){
                            attr_type = fileAttr->getColValueType(no_columns[i]);
                            offset = fileAttr->getColValueOffset(no_columns[i]);
                            data = record.getData(offset);
                            switch (attr_type) {
                                case INT: {//int
                                    int val = (*((int *) data));
                                    printf("%d  \t", val);
                                    break;
                                }
                                case FLOAT: {//float
                                    float val = (*((float *) data));
                                    printf("%f  \t", val);
                                    break;
                                }
                                case STRING: {//string
                                    printf("%s   \t", data);
                                    break;
                                }
                                default: {
                                    printf("error%s\n");
                                    return "type\n";
                                }
                            }
                        }
                        printf("\n");
                    }
                }

                //聚集查询
                for(int i=0;i < ope_columns.size();++i){
                    switch (operates[i]){
                        case Expr::SUM: {
                            double sum = 0;
                            for (map<RID, int>::iterator it = rid_list.begin(); it != rid_list.end(); ++it) {
//                                printf("type: %d\n",fileAttr->getColValueType(ope_columns[i]));
                                if (fileAttr->getColValueType(ope_columns[i]) != AttrType::INT &&
                                    fileAttr->getColValueType(ope_columns[i]) != AttrType::FLOAT) {
                                    printf("column type error\n");
                                    return "";
                                }
                                RID rid = it->first;
//                                printf("rid<%d,%d> \t", rid.pid, rid.sid);
                                Record record;
                                fileHandle.getRec(rid, record);
                                int offset = fileAttr->getColValueOffset(ope_columns[i]);
                                char *data = record.getData(offset);
                                if (fileAttr->getColValueType(ope_columns[i]) == AttrType::INT) {
                                    sum += *((int *) data);
                                } else if (fileAttr->getColValueType(ope_columns[i]) == AttrType::FLOAT) {
                                    sum += *((float *) data);
                                }
                            }
                            printf("SUM(%s): %lf", ope_columns[i].c_str(), sum);
                            break;
                        }
                        case Expr::AVG: {
                            double avg_sum = 0;
                            int count = 0;
                            for (map<RID, int>::iterator it = rid_list.begin(); it != rid_list.end(); ++it) {
                                if (fileAttr->getColValueType(ope_columns[i]) != AttrType::INT &&
                                    fileAttr->getColValueType(ope_columns[i]) != AttrType::FLOAT) {
                                    printf("column type error\n");
                                    return "";
                                }
                                RID rid = it->first;
                                printf("rid<%d,%d> \t", rid.pid, rid.sid);
                                Record record;
                                fileHandle.getRec(rid, record);
                                int offset = fileAttr->getColValueOffset(ope_columns[i]);
                                char *data = record.getData(offset);
                                if (fileAttr->getColValueType(ope_columns[i]) == AttrType::INT) {
                                    avg_sum += *((int *) data);
                                } else if (fileAttr->getColValueType(ope_columns[i]) == AttrType::FLOAT) {
                                    avg_sum += *((float *) data);
                                }
                                ++count;
                            }
                            printf("AVG(%s): %lf", ope_columns[i].c_str(), avg_sum / count);
                            break;
                        }
                        case Expr::MAX: {
                            double max = 0;
                            for (map<RID, int>::iterator it = rid_list.begin(); it != rid_list.end(); ++it) {
                                if (fileAttr->getColValueType(ope_columns[i]) != AttrType::INT &&
                                    fileAttr->getColValueType(ope_columns[i]) != AttrType::FLOAT) {
                                    printf("column type error\n");
                                    return "";
                                }
                                RID rid = it->first;
                                printf("rid<%d,%d> \t", rid.pid, rid.sid);
                                Record record;
                                fileHandle.getRec(rid, record);
                                int offset = fileAttr->getColValueOffset(ope_columns[i]);
                                char *data = record.getData(offset);
                                if (fileAttr->getColValueType(ope_columns[i]) == AttrType::INT) {
                                    if (max < *((int *) data))
                                        max = *((int *) data);
                                } else if (fileAttr->getColValueType(ope_columns[i]) == AttrType::FLOAT) {
                                    if (max < *((float *) data))
                                        max = *((float *) data);
                                }
                            }
                            printf("MAX(%s): %lf", ope_columns[i].c_str(), max);
                            break;
                        }
                        case Expr::MIN: {
                            double min = 0;
                            for (map<RID, int>::iterator it = rid_list.begin(); it != rid_list.end(); ++it) {
                                if (fileAttr->getColValueType(ope_columns[i]) != AttrType::INT &&
                                    fileAttr->getColValueType(ope_columns[i]) != AttrType::FLOAT) {
                                    printf("column type error\n");
                                    return "";
                                }
                                RID rid = it->first;
                                printf("rid<%d,%d> \t", rid.pid, rid.sid);
                                Record record;
                                fileHandle.getRec(rid, record);
                                int offset = fileAttr->getColValueOffset(ope_columns[i]);
                                char *data = record.getData(offset);
                                if (fileAttr->getColValueType(ope_columns[i]) == AttrType::INT) {
                                    if (min > *((int *) data))
                                        min = *((int *) data);
                                } else if (fileAttr->getColValueType(ope_columns[i]) == AttrType::FLOAT) {
                                    if (min > *((float *) data))
                                        min = *((float *) data);
                                }
                            }
                            printf("MIN(%s): %lf", ope_columns[i].c_str(), min);
                            break;
                        }
                    }
                }


                delete fileAttr;

                return "";
            }
            case kStmtUpdate:{
                printf("update options\n");
                UpdateStatement* updateStatement = (UpdateStatement*)stmt;

                //获取要选取的表名
                string filename = updateStatement->table->name;
                RM_FileHandle fileHandle;

                //获取rm handle
                recordManager->openFile(filename.c_str(),fileHandle);
                BufType fileHeader = fileHandle.getFileHeader();
                //获取表头信息
                RM_FileAttr* fileAttr = new RM_FileAttr();
                fileAttr->getFileAttrFromPageHeader(fileHeader);
                //获取所有要更新的记录
                map<RID,int>rid_list;
                this->searchRIDListByWhereClause(updateStatement->where,rid_list,fileHandle,0,updateStatement->table->name);
                printf("update rid size %lu\n",rid_list.size());
                //更新记录
                map<RID, int>::iterator it;

                for (it = rid_list.begin(); it != rid_list.end(); ++it) {
                    RID rid = it->first;
                    Record record;
                    //获取要修改的数据项数据
                    fileHandle.getRec(rid,record);
                    //修改数据项
                    for(int i = 0 ; i < updateStatement->updates->size(); ++i) {

                        //要更新的列名
                        char* col_name = ((*updateStatement->updates)[i])->column;
                        //要更新的新值
                        Expr* value = ((*updateStatement->updates)[i])->value;
                        printf("update col name %s\n",col_name);
                        AttrType value_type = fileAttr->getColValueType(col_name);
                        int offset = fileAttr->getColValueOffset(col_name);
                        int value_size = fileAttr->getColValueSize(col_name);
                        ColType col_type = fileAttr->getColType(col_name);

                        char* data = record.getData(offset);
                        //缓存修改前的值，以删除索引
                        char* old_data = new char[value_size];
                        for(int j = 0 ; j < value_size; ++j) {
                            old_data[j] = data[j];
                        }
                        //获取新的值
                        switch(value_type) {
                            case AttrType::INT: {
                                *(int*)data = value->ival;
                                printf("new INT  %d %d\n",value->ival,*(int*)data);
                                break;
                            }
                            case AttrType::FLOAT: {
                                *(float*)data = value->fval;
                                printf("new FLOAT  %f %f\n",value->fval,*(float *)data);
                                break;
                            }
                            case AttrType::STRING: {
                                strcpy(data, value->name);
                                printf("update string %s %s\n",value->name,data);
                                break;
                            }
                            default: {
                                printf("type error %s %s\n",value->name,data);
                            }
                        }

                        //如果修改的是索引项则删除旧索引建立新的索引
                        if(col_type == ColType::INDEX || col_type == ColType::PRIMARY || col_type == ColType::UNIQUE) {
                            //创建handle
                            string indexName = fileAttr->getIndexName(updateStatement->table->name, col_name);
                            IX_IndexHandle indexHandle;
                            this->indexManager->OpenIndex(indexName.c_str(), indexHandle);
                            char *key = old_data;
                            int type,tag;
                            Pointer p;
                            //如果是PRIMARY和UNIQUE，需要确保新值不存在
                            if((col_type == ColType::UNIQUE || col_type == ColType::PRIMARY) &&
                                indexHandle.searchEntry(data,p,type,tag).equal(RC()) && tag == IndexType::valid) {//如果存在,报错。
                                printf("primary key: %s, dumplicate, update fail\n",fileAttr->getPrimaryKeyName().c_str());
                                return "";
                            }
                            //否则删除索引并插入新的索引
                            if(indexHandle.DeleteEntry(key, rid).equal(RC())) {
                                printf("delete index %s rid<%d,%d> ok\n",indexName.c_str(),rid.pid,rid.sid);
                                //插入新的索引项
                                if(indexHandle.InsertEntry(data,rid).equal(RC())) {
                                    printf("insert index %s %s rid<%d,%d> ok\n",indexName.c_str(),data,rid.pid,rid.sid);
                                } else {
                                    printf("insert index %s rid<%d,%d> fail\n",indexName.c_str(),rid.pid,rid.sid);
                                    return "";
                                }
                            }
                            else {
                                printf("delete index %s rid<%d,%d> fail\n",indexName.c_str(),rid.pid,rid.sid);
                                return "";
                            }
                            indexHandle.close();
                        }
                    }
                    //所有列的修改完成后修改数据项
                    fileHandle.updateRec(record);
                }
                delete fileAttr;
                printf("update \n  ");
                return "";
            }
            case kStmtDelete:{
                printf("delete options\n");
                DeleteStatement* deleteStatement = (DeleteStatement*)stmt;
                //获取要选取的表名
                string filename = deleteStatement->tableName;
                RM_FileHandle fileHandle;

                //获取rm handle
                recordManager->openFile(filename.c_str(),fileHandle);
                BufType fileHeader = fileHandle.getFileHeader();
                //获取表头信息
                RM_FileAttr* fileAttr = new RM_FileAttr();
                fileAttr->getFileAttrFromPageHeader(fileHeader);
                //获取所有的索引项列名
                vector<string> list = fileAttr->getIndexKeyNameList();

                map<RID,int>rid_list;
                this->searchRIDListByWhereClause(deleteStatement->expr,rid_list,fileHandle,0,deleteStatement->tableName);
                printf("delete rid size %lu\n",rid_list.size());
                //删除记录
                map<RID, int>::iterator it;
                for (it = rid_list.begin(); it != rid_list.end(); ++it) {
                    RID rid = it->first;
                    Record record;
                    //获取要删除的数据项数据
                    fileHandle.getRec(rid,record);
                    //删除数据项记录
                    if(fileHandle.deleteRec(rid).equal(RC())) {
                        printf("delete data rid<%d,%d> \n", rid.pid, rid.sid);
                        //删除对应的索引项
                        unsigned long index_entry_numbers = list.size();
                        for (int i = 0; i < index_entry_numbers; ++i) {
                            //获取索引的列名
                            string index_col_name = list[i];
                            //创建handle
                            string indexName = fileAttr->getIndexName(deleteStatement->tableName, index_col_name);
                            IX_IndexHandle indexHandle;
                            this->indexManager->OpenIndex(indexName.c_str(), indexHandle);
                            //获取待删除的索引码值
                            int offset = fileAttr->getColValueOffset(index_col_name.c_str());
                            char *key = record.getData(offset);
                            if(indexHandle.DeleteEntry(key, rid).equal(RC())) {
                                printf("delete index %s rid<%d,%d> ok\n",indexName.c_str(),rid.pid,rid.sid);
                                indexHandle.close();
                            }
                            else {
                                printf("delete index %s rid<%d,%d> fail\n",indexName.c_str(),rid.pid,rid.sid);
                            }
                        }
                    }
                    else {
                        printf("delete data rid<%d,%d> fail \n", rid.pid, rid.sid);
                    }
                }
                delete fileAttr;
                printf("delete \n  ");
                return "";
            }
            default:{
                return "WTH!? "+ stmt->type();
            }
        }
    }



    /**
     *
     * @param filename 文件名
     * @return
     */
    string readSQLfile(string filename ){
        ifstream fin(filename.c_str());
        string sql_stmt;
        if(fin){
            string temp;
            while (getline(fin,temp)){
                sql_stmt += " "+temp;
                if(temp=="")
                    continue;
                if(temp[temp.length()-1]==';') {
                    cout<<sql_stmt<<endl;
                    string result = readSQL(sql_stmt);
                    printf("\n");
                }
//                printf("%s",result.c_str());
            }
        }
        fin.close();
        return  "";
    }

    RC searchRIDListByWhereClause(Expr* whereclause, map<RID,int> & rid_list , RM_FileHandle &fileHandle , int numIndent, char* tableName) {
        //whereclause type is kExprOperator
        if (whereclause == NULL) {
            printf("null where get all record\n");
            RM_FileScan *fileScan = new RM_FileScan();
            fileScan->openScan(&fileHandle, AttrType::FLOAT, 0, 0, CompOp::EQ_OP, NULL);
            fileScan->getAllRecordOfFile(rid_list);
            delete fileScan;
            return RC(-1);
        }
        map<RID,int> left;
        map<RID,int> right;
        CompOp op = EQ_OP;
        switch (whereclause->op_type) {
            case Expr::LESS_EQ: {// <=
                op = LE_OP;
            }
            case Expr::GREATER_EQ: {// >=
                op = GE_OP;
            }
            case Expr::NOT_EQUALS: {// <>
                op = NE_OP;
            }
            case Expr::SIMPLE_OP: {
                //= < >
                //递归基，符号两边为列名和属性值，进行查找
                char *col_name = whereclause->expr->name;
                RM_FileAttr *fileAttr = new RM_FileAttr();
                fileAttr->getFileAttrFromPageHeader(fileHandle.getFileHeader());
                //数据行的偏移量
                int offset = fileAttr->getColValueOffset(col_name);
                //数据列对应数据长度
                int value_size = fileAttr->getColValueSize(col_name);
                //数据类型
                AttrType value_type = fileAttr->getColValueType(col_name);
                //列类型
                ColType col_type = fileAttr->getColType(col_name);

                char op_char = whereclause->op_char;
                if (op_char == '<') {
                    op = LT_OP;
                } else if (op_char == '>') {
                    op = GT_OP;
                } else if (op_char == '=') {
                    op = EQ_OP;
                }
                //比较数据
                char *col_values = new char[value_size];
                //whereclause->expr2 为属性值
                switch (whereclause->expr2->type) {
                    case kExprLiteralFloat:
                        *((float *) col_values) = whereclause->expr2->fval;
                        break;
                    case kExprLiteralInt:
                        *((int *) col_values) = whereclause->expr2->ival;
                        break;
                    case kExprLiteralString:
                        strcpy(col_values, whereclause->expr2->name);
                        break;
                    default:
                        return RC(-1);
                }
                //如果查找列是索引列，并且是等号查找，则按索引查找
                if((col_type == ColType::INDEX || col_type == ColType::UNIQUE || col_type == ColType::PRIMARY) && op == CompOp::EQ_OP) {
                    printf("index search\n");
                    IX_IndexScan* indexScan = new IX_IndexScan();
                    string indexName = fileAttr->getIndexName(tableName,col_name);
                    IX_IndexHandle indexHandle;
                    printf("index filename %s\n",indexName.c_str());
                    this->indexManager->OpenIndex(indexName.c_str(),indexHandle);
                    indexScan->OpenScan(&indexHandle,op,col_values);
                    indexScan->getAllRecord(rid_list);
                    delete indexScan;
                }
                else {
                    RM_FileScan *fileScan = new RM_FileScan();
                    fileScan->openScan(&fileHandle, value_type, value_size, offset, op, col_values);
                    printf("base search\n");
                    printf("op %c\n", whereclause->op_char);
                    fileScan->getAllRecord(rid_list);
                    printf("base search ok %c\n", whereclause->op_char);
                    delete fileScan;
                }
                delete fileAttr;
                break;
            }
             //符号两边为表达式，继续递归根据符号取交、并、补
            case Expr::AND: {
                RC l_rc = searchRIDListByWhereClause(whereclause->expr, left, fileHandle, numIndent + 1,tableName);
                RC r_rc = searchRIDListByWhereClause(whereclause->expr2, right, fileHandle, numIndent + 1,tableName);
                map<RID, int>::iterator it;
                //循环遍历左边表达式选取的项在右边表达式是否存在
                for (it = left.begin(); it != left.end(); ++it) {
                    //判断在右边是否存在
                    map<RID, int>::iterator r_it = right.find(it->first);
                    //不存在则下一个
                    if (r_it == right.end()) continue;
                    rid_list.insert(pair<RID, int>(it->first, 1));
                }
                printf("AND");
                return RC();
            }
            case Expr::OR: {
                RC l_rc = searchRIDListByWhereClause(whereclause->expr, left, fileHandle, numIndent + 1,tableName);
                RC r_rc = searchRIDListByWhereClause(whereclause->expr2, right, fileHandle, numIndent + 1,tableName);
                map<RID, int>::iterator it;
                //将右边表达式选取的记录插入
                for (it = right.begin(); it != right.end(); ++it) {
                    rid_list.insert(pair<RID, int>(it->first, 1));
                }

                //循环遍历左边的记录是否存在右边，若存在则剔除
                for (it = left.begin(); it != left.end(); ++it) {
                    //判断在右边是否存在
                    map<RID, int>::iterator r_it = right.find(it->first);
                    //若右边存在则剔除
                    if (r_it != right.end()) continue;
                    rid_list.insert(pair<RID, int>(it->first, 1));
                }
                printf("OR");
                return RC();
            }
            case Expr::NOT: {
                printf("NOT");
                break;
            }
            default: {
                printf("%d\n", whereclause->op_type);
                break;
            }
        }
    }
};


#endif //DATABASE_DATABASESYSTEM_H
