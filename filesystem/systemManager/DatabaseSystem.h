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
#include <values.h>
/*
 * map按value排序
 */
typedef pair<string, int> PAIR;
bool cmp_by_value(const PAIR& lhs, const PAIR& rhs) {
    return lhs.second < rhs.second;
}

struct CmpByValue {
    bool operator()(const PAIR& lhs, const PAIR& rhs) {
        return lhs.second > rhs.second;
    }
};

using namespace std;
using namespace hsql;
union AttrValue{
    char* string_data;
    int int_data;
    float float_data;
};
struct columnDef{
    string tableName;
    string colName;
    columnDef(){
        tableName = "";
        colName = "";
    }
};
//struct N_Table_Params;
class DatabaseSystem {
    SM_Manager* system_manager;

    RecordManager* recordManager;
    FileManager* fm;
    BufPageManager* bpm;
    int tt;
public:
    IndexManager* indexManager;

    DatabaseSystem() {
        this->fm = new FileManager();
        this->bpm = new BufPageManager(fm);
        this->indexManager = new IndexManager(fm,bpm);
        this->recordManager = new RecordManager(fm,bpm);
        tt = 0;
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
              //  printf("%s",result.c_str());
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
                    if((*(createStatement->columns))[i]->check_expr!=NULL){
                        continue;
                    }
                    printf("attr_name: %s \t  ",(*(createStatement->columns))[i]->name);
                    printf("attr_type: %d \t  ",(*(createStatement->columns))[i]->type);
                    printf("attr_size: %d \t  ",(int)(*(createStatement->columns))[i]->size);
                    printf("attr_not_null: %d\t",(*(createStatement->columns))[i]->not_null);
                    if(createStatement->primary_key == NULL) continue;
                    if(strcmp((*(createStatement->columns))[i]->name,createStatement->primary_key) == 0) {
                        printf("attr_col_type: %s\t\n","PRIMARY");
                    }
                    else{
                        printf("attr_col_type: %s\t\n","NORMAL");
                    }
                }

                RM_FileAttr* attr = new RM_FileAttr[1];
                for(int i=0;i<attrCount;++i) {
                    if((*(createStatement->columns))[i]->check_expr!=NULL){
                        //获取列名
                        string colname = string((*(createStatement->columns))[i]->check_expr->expr->name);
                        int col_index = attr->getColIndex(colname);
                        attr->check_exprs[col_index] = (*(createStatement->columns))[i]->check_expr;
                        continue;
                    }
                    attr->key_name.push_back(string((*(createStatement->columns))[i]->name));
                    attr->key_type.push_back((*(createStatement->columns))[i]->type);
                    attr->value_length.push_back(((*(createStatement->columns))[i]->size) + RECORD_COL_PAD);
                    int k = (*(createStatement->columns))[i]->not_null;
                    attr->not_null.push_back(k);
                    attr->check_exprs.push_back(NULL);

                    if( createStatement->primary_key != NULL && strcmp((*(createStatement->columns))[i]->name,createStatement->primary_key) == 0) {
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
                //printInsertStatementInfo((InsertStatement*)stmt, 0);
                //printf("insert options\n");

                InsertStatement* insertStmt = (InsertStatement*)stmt;
                std::vector<std::vector<Expr*>*>* values = insertStmt->values;
                //该语句中所有要插入项的总数
                int entry_size = values->size();
                //获取要插入的表名
                string filename = insertStmt->tableName;
                RM_FileHandle* fileHandle = new RM_FileHandle();
                //打开RM_Handle
                recordManager->openFile(filename.c_str(),*fileHandle);
                BufType fileHeader = fileHandle->getFileHeader();
                //获取表头信息
                RM_FileAttr* fileAttr = new RM_FileAttr();
                fileAttr->getFileAttrFromPageHeader(fileHeader);
                //申请插入的数据块data缓冲区
                BufType data = new unsigned int[fileHandle->getFileHeader()[TABLE_RECORD_INT_SIZE_INT_OFFSET]];
                //打开主键约束Handle（如果存在主键约束）
                IX_IndexHandle* primaryHandle;
                if (fileAttr->getPrimaryKeyName() != "") {
                    //获取主键约束的列名
                    primaryHandle = new IX_IndexHandle;
                    string primary_col_name = fileAttr->getPrimaryKeyName();
                    string indexName = fileAttr->getIndexName(insertStmt->tableName, primary_col_name);
                    this->indexManager->OpenIndex(indexName.c_str(), *primaryHandle);
                }
                //获取所有的索引项列名
                vector <string> list = fileAttr->getIndexKeyNameList();
                //打开所有的索引约束Handle（不含PRIMARY和UNIQUE）
                vector <IX_IndexHandle*> indexHandleList;
                for(int i = 0 ; i < list.size() ; ++i) {
                    //获取索引的列名
                    string index_col_name = list[i];
                    //创建handle
                    string indexName = fileAttr->getIndexName(insertStmt->tableName, index_col_name);
                    //获取索引列类型，排除PRIMARY和UNIQUE
                    ColType colType = fileAttr->getColType(index_col_name);
                    if (colType == ColType::UNIQUE || colType == ColType::PRIMARY) {
                        indexHandleList.push_back(NULL);
                        continue;
                    }
                    //打开该索引的Handle
                    IX_IndexHandle* indexHandle = new IX_IndexHandle;
                    this->indexManager->OpenIndex(indexName.c_str(), *indexHandle);
                    indexHandleList.push_back(indexHandle);
                }
                tt += entry_size;
                cout <<"size: "<< tt <<endl;
                //return "";

                //插入每一项
                for(int s = 0 ; s < entry_size; ++s) {
                    //获取数据信息
                    string info = fileAttr->buildValidInsertData(insertStmt, data, (*values)[s]);


                    if (info != "") {
                        printf("%s", info.c_str());
                        delete fileAttr;
                        return "";
                    }

                    //检查是否有主键约束
                    if (fileAttr->getPrimaryKeyName() != "") {//有主键约束，验证存在，不存在则插入
                        //获取主键约束的列名
                        string primary_col_name = fileAttr->getPrimaryKeyName();
                        //获取待插入的主键值
                        int offset = fileAttr->getColValueOffset(primary_col_name.c_str());
                        char *key = ((char *) (data)) + offset;
                        int type, tag;
                        Pointer p;
                        //检查是否存在
                        if (primaryHandle->searchEntry(key, p, type, tag).equal(RC()) &&
                            tag == IndexType::valid) {//如果存在,报错。
                            printf("primary key: %s, dumplicate\n", fileAttr->getPrimaryKeyName().c_str());
                        } else {//插入数据，并插入索引
                            RID rid;
                            fileHandle->insertRec(data, rid);
                            printf("rid<%d,%d> id %d\n", rid.pid, rid.sid,*((int*)(key)));
                            //插入主键索引
                            if(primaryHandle->InsertEntry(key, rid).equal(RC())) {
                                //printf("insert primary %s rid<%d,%d> ok\n", primary_col_name.c_str(), rid.pid,
                                //       rid.sid);
                            } else {
                                printf("insert primary %s rid<%d,%d> fail\n", primary_col_name.c_str(), rid.pid,
                                       rid.sid);
                            }
                            //插入其余索引
                            Record record;
                            record.setData(data);
                            record.setRID(rid);
                            for (int i = 0; i < list.size(); ++i) {
                                //获取索引的列名
                                string index_col_name = list[i];
                                //检查类型，如果是UNIQUE和PRIMARY则不插入
                                ColType colType = fileAttr->getColType(index_col_name);
                                if (colType == ColType::UNIQUE || colType == ColType::PRIMARY) {
                                    continue;
                                }
                                //获取该索引的handle
                                IX_IndexHandle* indexHandle = indexHandleList[i];
                                //获取待插入的索引列的偏移
                                int index_col_offset = fileAttr->getColValueOffset(index_col_name.c_str());
                                //获取待插入的索引码值
                                char *index_key = record.getData(index_col_offset);
                                if (indexHandle->InsertEntry(index_key, record.getRID()).equal(RC())) {
                                    printf("insert index %s rid<%d,%d> ok\n", index_col_name.c_str(), record.getRID().pid,
                                           record.getRID().sid);
                                } else {
                                    printf("insert index %s rid<%d,%d> fail\n", index_col_name.c_str(), record.getRID().pid,
                                           record.getRID().sid);
                                }
                            }
                        }
                    } else {//没有主键和UNIQUE约束，直接插入数据项和索引项
                        RID rid;
                        //插入数据项
                        fileHandle->insertRec(data, rid);
                        Record record;
                        record.setData(data);
                        record.setRID(rid);
                        printf("rid<%d,%d>\n", rid.pid, rid.sid);
                        //插入索引项
                        for (int i = 0; i < list.size(); ++i) {
                            //获取索引的列名
                            string index_col_name = list[i];
                            //检查类型，如果是UNIQUE和PRIMARY则不插入
                            ColType colType = fileAttr->getColType(index_col_name);
                            if (colType == ColType::UNIQUE || colType == ColType::PRIMARY) {
                                continue;
                            }
                            //获取该索引的handle
                            IX_IndexHandle* indexHandle = indexHandleList[i];
                            //获取待插入的索引列的偏移
                            int index_col_offset = fileAttr->getColValueOffset(index_col_name.c_str());
                            //获取待插入的索引码值
                            char *index_key = record.getData(index_col_offset);
                            if (indexHandle->InsertEntry(index_key, record.getRID()).equal(RC())) {
                                printf("insert index %s rid<%d,%d> ok\n", index_col_name.c_str(), record.getRID().pid,
                                       record.getRID().sid);
                            } else {
                                printf("insert index %s rid<%d,%d> fail\n", index_col_name.c_str(), record.getRID().pid,
                                       record.getRID().sid);
                            }
                        }
                    }
                }

                if (fileAttr->getPrimaryKeyName() != "") {
                    //获取主键约束的列名
                    primaryHandle->close();
                    delete primaryHandle;
                }

                for (int i = 0; i < list.size(); ++i) {
                    //获取索引的列名
                    string index_col_name = list[i];
                    //检查类型，如果是UNIQUE和PRIMARY则不插入
                    ColType colType = fileAttr->getColType(index_col_name);
                    if (colType == ColType::UNIQUE || colType == ColType::PRIMARY) {
                        continue;
                    }
                    //获取该索引的handle
                    IX_IndexHandle* indexHandle = indexHandleList[i];
                    indexHandle->close();
                    delete indexHandle;
                }
                delete [] data;
                delete fileAttr;
                delete fileHandle;
                return "";
            }
            case kStmtSelect:{
                //打印语句信息
                //printSelectStatementInfo((SelectStatement*)stmt, 0);
                //printf("select options\n");

                vector<Expr::OperatorType> operates;
                vector<columnDef> ope_columns;
                vector<columnDef> no_columns;
                SelectStatement* selectStatement = (SelectStatement*)stmt;

                //获取要选取的列名(表名.列名 表名或者列名默认为""空串)
                for (Expr* expr : *selectStatement->selectList){
                    switch (expr->type) {
                        case kExprStar: {
                            printf("columns: *\n");
                            columnDef temp_col;
                            temp_col.colName = "*";
                            no_columns.push_back(temp_col);
                            break;
                        }
                        case kExprColumnRef: {
                            printf("%s %s\n", expr->table, expr->name);
                            columnDef temp_col;
                            if(expr->table!=NULL)
                                temp_col.tableName = expr->table;
                            temp_col.colName = expr->name;
                            no_columns.push_back(temp_col);
                            break;
                        }
                        case kExprOperator: {
                            switch (expr->op_type) {
                                case Expr::SUM: {
                                    operates.push_back(Expr::SUM);
                                    columnDef temp_col;
                                    if(expr->expr->table!=NULL)
                                        temp_col.tableName = expr->expr->table;
                                    temp_col.colName = expr->expr->name;
                                    ope_columns.push_back(temp_col);
                                    break;
                                }
                                case Expr::AVG: {
                                    operates.push_back(Expr::AVG);
                                    columnDef temp_col;
                                    if(expr->expr->table!=NULL)
                                        temp_col.tableName = expr->expr->table;
                                    temp_col.colName = expr->expr->name;
                                    ope_columns.push_back(temp_col);
                                    break;
                                }
                                case Expr::MAX: {
                                    operates.push_back(Expr::MAX);
                                    columnDef temp_col;
                                    if(expr->expr->table!=NULL)
                                        temp_col.tableName = expr->expr->table;
                                    temp_col.colName = expr->expr->name;
                                    ope_columns.push_back(temp_col);
                                    break;
                                }
                                case Expr::MIN: {
                                    operates.push_back(Expr::MIN);
                                    columnDef temp_col;
                                    if(expr->expr->table!=NULL)
                                        temp_col.tableName = expr->expr->table;
                                    temp_col.colName = expr->expr->name;
                                    ope_columns.push_back(temp_col);
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

                /**
                * TEST Join
                */
                if(((SelectStatement*)stmt)->fromTable->type == kTableCrossProduct) {
                    TableRef* table = ((SelectStatement*)stmt)->fromTable;
                    N_Table_Params* params = new N_Table_Params();
                    map<string,int> tableMap;

                    for (TableRef* tbl : *table->list) {
                  //      printf("table name: %s\n",tbl->name);
                        tableMap.insert(pair<string,int>(tbl->name,0));
//                        params->addTable(tbl->name);
                    }
                    //按在表达式中的约束排序，出现次数最多先查
                    params->firgureTableTime(selectStatement->whereClause,tableMap);
                    vector<PAIR> name_score_vec(tableMap.begin(), tableMap.end());
                    sort(name_score_vec.begin(), name_score_vec.end(), CmpByValue());

                    for(int t = 0 ; t < name_score_vec.size(); ++t) {
                  //      printf("table name: %s\n",name_score_vec[t].first.c_str());
                        params->addTable(name_score_vec[t].first);
                    }
                    params->init(this,this->recordManager);
                  //  printf("begin search\n");
                    params->getAssociationSearchResult(selectStatement->whereClause);
                   // printf("search ok\n\n\n\n\n\n\n\n");
                    params->printTest(no_columns);
                    return "";
                }

                //获取要选取的表名
                vector<string> filenames;
                if(selectStatement->fromTable->list == NULL)
                    filenames.push_back(selectStatement->fromTable->getName());
                else{
                    unsigned long size = (*selectStatement->fromTable->list).size();
                    for(int i=0;i<size;++i){
                        filenames.push_back((*selectStatement->fromTable->list)[i]->getName());
                    }
                }
                RM_FileHandle fileHandle;
                //获取rm handle
                recordManager->openFile(filenames[0].c_str(),fileHandle);
                BufType fileHeader = fileHandle.getFileHeader();
                //获取表头信息
                RM_FileAttr* fileAttr = new RM_FileAttr();
                fileAttr->getFileAttrFromPageHeader(fileHeader);
                map<RID,int>rid_list;
                this->searchRIDListByWhereClause(selectStatement->whereClause,rid_list,fileHandle,0,selectStatement->fromTable->getName());
//                printf("rid size %lu\n",rid_list.size());
                if(selectStatement->groupBy!=NULL){
                    string groupby = (*selectStatement->groupBy->columns)[0]->name;
                    printf("groupby: %s\n",groupby.c_str());
                    vector<map<RID,int>> group_rid_list;
                    vector<int>int_values;
                    vector<float>float_values;
                    vector<string>string_values;
                    //循环遍历左边表达式选取的项在右边表达式是否存在
                    for (map<RID, int>::iterator it = rid_list.begin(); it != rid_list.end(); ++it){
                        RID rid = it->first;
                        Record record;
                        fileHandle.getRec(rid, record);
                        int offset = fileAttr->getColValueOffset(groupby);
                        char *data = record.getData(offset);
                        switch(fileAttr->getColValueType(groupby)){
                            case INT:{
                                bool exist = false;
                                int value = *((int*)data);
                                int size = int_values.size();
                                for(int i=0;i<size;++i){
                                    if(value == int_values[i]){
                                        exist = true;
                                        group_rid_list[i].insert(make_pair(it->first,it->second));
                                        break;
                                    }
                                }
                                if(!exist){
                                    int_values.push_back(value);
                                    map<RID,int> list;
                                    list.insert(make_pair(it->first,it->second));
                                    group_rid_list.push_back(list);
                                }
                                break;
                            }
                            case FLOAT:{
                                bool exist = false;
                                float value = *((float *)data);
                                int size = float_values.size();
                                for(int i=0;i<size;++i){
                                    if(value == float_values[i]){
                                        exist = true;
                                        group_rid_list[i].insert(make_pair(it->first,it->second));
                                        break;
                                    }
                                }
                                if(!exist){
                                    float_values.push_back(value);
                                    map<RID,int> list;
                                    list.insert(make_pair(it->first,it->second));
                                    group_rid_list.push_back(list);
                                }
                                break;
                            }
                            case STRING:{
                                bool exist = false;
                                string value = string(data);
                                int size = string_values.size();
                                for(int i=0;i<size;++i){
                                    if(value == string_values[i]){
                                        exist = true;
                                        group_rid_list[i].insert(make_pair(it->first,it->second));
                                        break;
                                    }
                                }
                                if(!exist){
                                    string_values.push_back(value);
                                    map<RID,int> list;
                                    list.insert(make_pair(it->first,it->second));
                                    group_rid_list.push_back(list);
                                }
                                break;
                            }
                        }

                    }
                    printf("%s    \t",groupby.c_str());
                    for(int i=0;i<ope_columns.size();++i){
                        switch (operates[i]) {
                            case Expr::SUM: {
                                printf("SUM(%s)   \t",ope_columns[i].colName.c_str());
                                break; }
                            case Expr::AVG: {
                                printf("AVG(%s)   \t",ope_columns[i].colName.c_str());
                                break; }
                            case Expr::MAX: {
                                printf("MAX(%s)   \t",ope_columns[i].colName.c_str());
                                break; }
                            case Expr::MIN: {
                                printf("MIN(%s)   \t",ope_columns[i].colName.c_str());
                                break; }
                        }
                    }
                    printf("\n");

                    int group_size = 0;
                    switch (fileAttr->getColValueType(groupby)){
                        case INT:{
                            group_size = int_values.size();
//                            printf("group size: %d\n",group_size);
                            for(int i=0;i<group_size;++i){
                                printf("%d    \t",int_values[i]);
                                for(int k=0;k<ope_columns.size();++k){
                                    switch (operates[k]) {
                                        case Expr::SUM: {
                                            double sum = printSUM(group_rid_list[i], fileAttr, ope_columns[k].colName, fileHandle);
                                            printf("%lf    \t",sum);
                                            break; }
                                        case Expr::AVG: {
                                            double avg = printAVG(group_rid_list[i], fileAttr, ope_columns[k].colName, fileHandle);
                                            printf("%lf    \t",avg);
                                            break; }
                                        case Expr::MAX: {
                                            double max = printMAX(group_rid_list[i], fileAttr, ope_columns[k].colName, fileHandle);
                                            printf("%lf    \t",max);
                                            break; }
                                        case Expr::MIN: {
                                            double min = printMIN(group_rid_list[i], fileAttr, ope_columns[k].colName, fileHandle);
                                            printf("%lf    \t",min);
                                            break; }
                                    }
                                }
                                printf("\n");
                            }
                            break;
                        }
                        case FLOAT:{
                            group_size = float_values.size();
                            for(int i=0;i<group_size;++i){
                                printf("%f    \t",float_values[i]);
                                for(int k=0;k<ope_columns.size();++k){
                                    switch (operates[k]) {
                                        case Expr::SUM: {
                                            double sum = printSUM(group_rid_list[i], fileAttr, ope_columns[k].colName, fileHandle);
                                            printf("%lf    \t",sum);
                                            break; }
                                        case Expr::AVG: {
                                            double avg = printAVG(group_rid_list[i], fileAttr, ope_columns[k].colName, fileHandle);
                                            printf("%lf    \t",avg);
                                            break; }
                                        case Expr::MAX: {
                                            double max = printMAX(group_rid_list[i], fileAttr, ope_columns[k].colName, fileHandle);
                                            printf("%lf    \t",max);
                                            break; }
                                        case Expr::MIN: {
                                            double min = printMIN(group_rid_list[i], fileAttr, ope_columns[k].colName, fileHandle);
                                            printf("%lf    \t",min);
                                            break; }
                                    }
                                }
                                printf("\n");
                            }
                            break;
                        }
                        case STRING:{
                            group_size = string_values.size();
                            for(int i=0;i<group_size;++i){
                                printf("%s    \t",string_values[i].c_str());
                                for(int k=0;k<ope_columns.size();++k){
                                    switch (operates[k]) {
                                        case Expr::SUM: {
                                            double sum = printSUM(group_rid_list[i], fileAttr, ope_columns[k].colName, fileHandle);
                                            printf("%lf    \t",sum);
                                            break; }
                                        case Expr::AVG: {
                                            double avg = printAVG(group_rid_list[i], fileAttr, ope_columns[k].colName, fileHandle);
                                            printf("%lf    \t",avg);
                                            break; }
                                        case Expr::MAX: {
                                            double max = printMAX(group_rid_list[i], fileAttr, ope_columns[k].colName, fileHandle);
                                            printf("%lf    \t",max);
                                            break; }
                                        case Expr::MIN: {
                                            double min = printMIN(group_rid_list[i], fileAttr, ope_columns[k].colName, fileHandle);
                                            printf("%lf    \t",min);
                                            break; }
                                    }
                                }
                                printf("\n");
                            }
                            break;
                        }
                    }

                }
                //非聚集查询与聚集查询分开输出
                //非分组聚集查询
                else {
                    int no_column_size = no_columns.size();
                    if (no_column_size != 0) {
                        if (no_columns[0].colName == "*") {
                            no_columns.clear();
                            for (int i = 0; i < fileAttr->attr_count; ++i) {
                                printf("%s       \t", fileAttr->key_name[i].c_str());
                                columnDef temp_col;
                                temp_col.colName = fileAttr->key_name[i];
                                no_columns.push_back(temp_col);
                            }
                            no_column_size = no_columns.size();
//                        printf("size: %d\n",no_column_size);
                        } else {
                            for (int i = 0; i < no_columns.size(); ++i) {
                                printf("%-10s|\t", no_columns[i].colName.c_str());
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
                            fileHandle.getRec(rid, record);
                            //不存在则下一个
//                        fileAttr->printRecordInfo(record.getData(),no_columns);
                            int offset = 0;
                            char *data;
                            int attr_type = 0;
                            for (int i = 0; i < no_column_size; ++i) {
                                attr_type = fileAttr->getColValueType(no_columns[i].colName);
                                offset = fileAttr->getColValueOffset(no_columns[i].colName);
                                data = record.getData(offset);
                                int col_index = fileAttr->getColIndex(no_columns[i].colName);
                                // printf("%d\n",col_index);
                                if (record.isNULL(col_index)) {
                                    printf("null  \t");
                                } else {
                                    switch (attr_type) {
                                        case INT: {//int
                                            int val = (*((int *) data));
                                            printf("%-10d|\t", val);
                                            break; }
                                        case FLOAT: {//float
                                            float val = (*((float *) data));
                                            printf("%-10f|\t", val);
                                            break; }
                                        case STRING: {//string
                                            printf("%-30s|\t", data);
                                            break; }
                                        default: {
                                            printf("error\n");
                                            return "type\n"; }
                                    }
                                }
                            }
                            printf("\n");
                        }
                    }
                    //聚集查询
                    for (int i = 0; i < ope_columns.size(); ++i) {
                        switch (operates[i]) {
                            case Expr::SUM: {
                                double sum = printSUM(rid_list, fileAttr, ope_columns[i].colName, fileHandle);
                                printf("SUN(%s): %lf", ope_columns[i].colName.c_str(), sum);
                                break;
                            }
                            case Expr::AVG: {
                                double avg = printAVG(rid_list, fileAttr, ope_columns[i].colName, fileHandle);
                                printf("AVG(%s): %lf", ope_columns[i].colName.c_str(), avg);
                                break;
                            }
                            case Expr::MAX: {
                                double max = printMAX(rid_list, fileAttr, ope_columns[i].colName, fileHandle);\
                                printf("MAX(%s): %lf", ope_columns[i].colName.c_str(), max);
                                break;
                            }
                            case Expr::MIN: {
                                double min = printMIN(rid_list, fileAttr, ope_columns[i].colName, fileHandle);
                                printf("MIN(%s): %lf", ope_columns[i].colName.c_str(), min);
                                break;
                            }
                        }
                    }
                }
                delete fileAttr;
                return "";
            }
            case kStmtUpdate:{
               // printf("update options\n");
                UpdateStatement* updateStatement = (UpdateStatement*)stmt;
                //获取要选取的表名
                string filename = updateStatement->table->name;
                //打开RM_Handle
                RM_FileHandle fileHandle;
                recordManager->openFile(filename.c_str(),fileHandle);
                //获取表头信息
                BufType fileHeader = fileHandle.getFileHeader();
                RM_FileAttr* fileAttr = new RM_FileAttr();
                fileAttr->getFileAttrFromPageHeader(fileHeader);

                //获取所有的索引项列名
                vector <string> list = fileAttr->getIndexKeyNameList();
                //打开所有的索引约束Handle（含PRIMARY和UNIQUE）
                map <string,IX_IndexHandle*> indexHandleList;
                for(int i = 0 ; i < list.size() ; ++i) {
                    //获取索引的列名
                    string index_col_name = list[i];
                    //创建handle
                    string indexName = fileAttr->getIndexName(updateStatement->table->name, index_col_name);
                    //打开该索引的Handle
                    IX_IndexHandle* indexHandle = new IX_IndexHandle;
                    this->indexManager->OpenIndex(indexName.c_str(), *indexHandle);
                    indexHandleList.insert(pair<string,IX_IndexHandle*>(index_col_name,indexHandle));
                }
                map <string, IX_IndexHandle*>::iterator index_handle_it;

                //获取所有要更新的记录
                map<RID,int>rid_list;
                this->searchRIDListByWhereClause(updateStatement->where,rid_list,fileHandle,0,updateStatement->table->name);
                map<RID, int>::iterator it;
               // printf("update rid size %lu\n",rid_list.size());

                //更新记录
                for (it = rid_list.begin(); it != rid_list.end(); ++it) {
                    RID rid = it->first;
                    Record record;
                    //获取要修改的数据项数据
                    fileHandle.getRec(rid,record);
                    //修改每一个数据项
                    for(int i = 0 ; i < updateStatement->updates->size(); ++i) {
                        //要更新的列名
                        char* col_name = ((*updateStatement->updates)[i])->column;
                        //要更新的新值
                        Expr* value = ((*updateStatement->updates)[i])->value;
                       // printf("update col name %s\n",col_name);
                        AttrType value_type = fileAttr->getColValueType(col_name);
                        int offset = fileAttr->getColValueOffset(col_name);
                        int value_size = fileAttr->getColValueSize(col_name);
                        ColType col_type = fileAttr->getColType(col_name);
                        int col_index = fileAttr->getColIndex(col_name);
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
                               // printf("new INT  %d %d\n",(int)value->ival,*(int*)data);
                                break;
                            }
                            case AttrType::FLOAT: {
                                *(float*)data = value->fval;
                              //  printf("new FLOAT  %f %f\n",value->fval,*(float *)data);
                                break;
                            }
                            case AttrType::STRING: {
                                strcpy(data, value->name);
                              //  printf("update string %s %s\n",value->name,data);
                                break;
                            }
                            default: {
                                printf("type error %s %s\n",value->name,data);
                            }
                        }

                        BufType check = fileAttr->page_header + TABLE_CHECK_INT_OFFSET;
                        BufType check_record = check + col_index * ATTR_CHECK_INT_SIZE;
                        if(!fileAttr->checkValues(check_record,data,value_type,value_size)) {
                            printf("not satisfy %s\n",col_name);
                            return "";
                        }

                        //如果修改的是索引项则删除旧索引建立新的索引
                        if(col_type == ColType::INDEX || col_type == ColType::PRIMARY || col_type == ColType::UNIQUE) {
                            //获取handle
                            IX_IndexHandle* indexHandle = indexHandleList.at(col_name);
                            char *key = old_data;
                            int type,tag;
                            Pointer p;
                            //如果是PRIMARY和UNIQUE，需要确保新值不存在
                            if((col_type == ColType::UNIQUE || col_type == ColType::PRIMARY) &&
                                indexHandle->searchEntry(data,p,type,tag).equal(RC()) && tag == IndexType::valid) {//如果存在,报错。
                                printf("primary key: %s, dumplicate, update fail\n",fileAttr->getPrimaryKeyName().c_str());
                                return "";
                            }
                            //否则删除索引并插入新的索引
                            if(indexHandle->DeleteEntry(key, rid).equal(RC())) {
                                printf("delete index %s rid<%d,%d> ok\n",col_name,rid.pid,rid.sid);
                                //插入新的索引项
                                if(indexHandle->InsertEntry(data,rid).equal(RC())) {
                                    printf("insert index %s %s rid<%d,%d> ok\n",col_name,data,rid.pid,rid.sid);
                                } else {
                                    printf("insert index %s rid<%d,%d> fail\n",col_name,rid.pid,rid.sid);
                                    return "";
                                }
                            }
                            else {
                                printf("delete index %s rid<%d,%d> fail\n",col_name,rid.pid,rid.sid);
                                return "";
                            }
                        }
                        record.setNotNULL(col_index);
                    }
                    //所有列的修改完成后修改数据项
                    fileHandle.updateRec(record);
                }

                for (index_handle_it = indexHandleList.begin(); index_handle_it != indexHandleList.end(); ++index_handle_it) {
                    IX_IndexHandle* indexHandle = index_handle_it->second;
                    indexHandle->close();
                    delete indexHandle;
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
                //打开所有要删除的索引项的Handle
                vector <IX_IndexHandle*> indexHandleList;
                for(int i = 0 ; i < list.size() ; ++i) {
                    //获取索引的列名
                    string index_col_name = list[i];
                    //创建handle
                    string indexName = fileAttr->getIndexName(deleteStatement->tableName, index_col_name);
                    //打开该索引的Handle
                    IX_IndexHandle* indexHandle = new IX_IndexHandle;
                    this->indexManager->OpenIndex(indexName.c_str(), *indexHandle);
                    indexHandleList.push_back(indexHandle);
                }

                //获取所有要删除的记录的RID
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
                        for (int i = 0; i < list.size(); ++i) {
                            //获取索引的列名
                            string index_col_name = list[i];
                            //获取该索引的handle
                            IX_IndexHandle* indexHandle = indexHandleList[i];
                            //获取要删除的索引列的偏移
                            int index_col_offset = fileAttr->getColValueOffset(index_col_name.c_str());
                            //获取要删除的索引码值
                            char *index_key = record.getData(index_col_offset);
                            if (indexHandle->DeleteEntry(index_key, record.getRID()).equal(RC())) {
                                printf("delete index %s rid<%d,%d> ok\n", index_col_name.c_str(), record.getRID().pid,
                                       record.getRID().sid);
                            } else {
                                printf("delete index %s rid<%d,%d> fail\n", index_col_name.c_str(), record.getRID().pid,
                                       record.getRID().sid);
                            }
                        }
                    }
                    else {
                        printf("delete data rid<%d,%d> fail \n", rid.pid, rid.sid);
                    }
                }

                for (int i = 0; i < list.size(); ++i) {
                    IX_IndexHandle* indexHandle = indexHandleList[i];
                    indexHandle->close();
                    delete indexHandle;
                }

                delete fileAttr;
                printf("delete ok\n  ");
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
    string readSQLfile(string filename){
        cout<<filename<<endl;
//        ifstream fin(filename.c_str());
        FILE* fin =fopen(filename.c_str(),"r");
        string sql_stmt = "";
        if(fin){
            char temp;
            while(!feof(fin)){
                temp=fgetc(fin);
                if(temp=='\n'&&sql_stmt[sql_stmt.length()-1]==';') {
                  //  cout<<"after: "<<sql_stmt<<endl;
                    string result = readSQL(sql_stmt);
                    sql_stmt = "";
                    printf("\n");
                }
                else if(temp!='\r'){
                    sql_stmt+=temp;
                }
//                cout<<"before: "<<sql_stmt<<endl;
//                else {
//                        cout<<"else: "<<temp<<" "<<temp<<endl;
//                };
//                printf("%s",result.c_str());
            }
        }
        else {
            printf("file doesn't exist\n");
            system("ls");
        }
        return  "";
    }
    RC searchRIDListByWhereClause(Expr* whereclause, map<RID,int> & rid_list , RM_FileHandle &fileHandle , int numIndent, char* tableName) {
        //whereclause type is kExprOperator
        if (whereclause == NULL) {
            printf("null where get all record\n");
            RM_FileScan *fileScan = new RM_FileScan();
            fileScan->openScan(&fileHandle, AttrType::FLOAT, 0, 0, CompOp::EQ_OP, NULL, 0);
            fileScan->getAllRecordOfFile(rid_list);
            delete fileScan;
            return RC(-1);
        }
        map<RID,int> left;
        map<RID,int> right;
        CompOp op = EQ_OP;
        switch (whereclause->op_type) {
            case Expr::LESS_EQ: {// <=
                if(whereclause->op_type == Expr::LESS_EQ) op = LE_OP;
            }
            case Expr::GREATER_EQ: {// >=
                if(whereclause->op_type == Expr::GREATER_EQ)
                op = GE_OP;
            }
            case Expr::NOT_EQUALS: {// <>
                if(whereclause->op_type == Expr::NOT_EQUALS)
                op = NE_OP;
            }
            case Expr::LIKE: {
                if(whereclause->op_type == Expr::LIKE)
                op = LIKE_OP;
            }
            case Expr::ISNULL: {
                if(whereclause->op_type == Expr::ISNULL) {
               //     printf("select null\n");
                    op = ISNULL_OP;
                }
            }
            case Expr::SIMPLE_OP: {
                //= < >
                //递归基，符号两边为列名和属性值，进行查找
                columnDef left_col,right_col;
                if(whereclause->expr->table!=NULL)
                    left_col.tableName = whereclause->expr->table;
                left_col.colName = whereclause->expr->name;
                RM_FileAttr *fileAttr = new RM_FileAttr();
                fileAttr->getFileAttrFromPageHeader(fileHandle.getFileHeader());
                //数据行的偏移量
                int offset = fileAttr->getColValueOffset(left_col.colName.c_str());
                //数据列对应数据长度
                int value_size = fileAttr->getColValueSize(left_col.colName.c_str());
                //数据类型
                AttrType value_type = fileAttr->getColValueType(left_col.colName.c_str());
                //列类型
                ColType col_type = fileAttr->getColType(left_col.colName.c_str());
                //数据列位置
                int col_index = fileAttr->getColIndex(left_col.colName.c_str());
               // printf("col_index %d\n",col_index);
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
                //whereclause->expr2 为目标属性值
                if(!(op == CompOp::ISNULL_OP)) {
                    switch (whereclause->expr2->type) {
                        case kExprLiteralFloat:
                            *((float *) col_values) = whereclause->expr2->fval;
                            break;
                        case kExprLiteralInt:
                            *((int *) col_values) = whereclause->expr2->ival;
                            break;
                        case kExprLiteralString:
//                            printf("taget: %s\n", whereclause->expr2->name);
                            strcpy(col_values, whereclause->expr2->name);
                            break;
                        case kExprOperator:
                            if(value_type==AttrType::INT) {
                                *((int *) col_values) = (int)getConstValue(whereclause->expr2);
                                printf("expr2_value: %d \n",*((int *) col_values));
                            }
                            else if(value_type==AttrType::FLOAT) {
                                *((float *) col_values) = getConstValue(whereclause->expr2);
                            }
                            break;
                        case kExprColumnRef:
                            if(whereclause->expr2->table!=NULL)
                                right_col.tableName = whereclause->expr2->table;
                            right_col.colName = whereclause->expr2->name;
                        default:
                            return RC(-1);
                    }
                }
                //如果查找列是索引列，并且是等号查找，并且不是模糊查找，则按索引查找
                if((col_type == ColType::INDEX || col_type == ColType::UNIQUE || col_type == ColType::PRIMARY) && op == CompOp::EQ_OP) {
                    printf("index search\n");
                    IX_IndexScan* indexScan = new IX_IndexScan();
                    string indexName = fileAttr->getIndexName(tableName,left_col.colName.c_str());
                    IX_IndexHandle indexHandle;
                    printf("index filename %s\n",indexName.c_str());
                    this->indexManager->OpenIndex(indexName.c_str(),indexHandle);
                    indexScan->OpenScan(&indexHandle,op,col_values);
                    indexScan->getAllRecord(rid_list);
                    printf("index search over, find:  %d\n",rid_list.size());
                    delete indexScan;
                }
                else {
                    RM_FileScan *fileScan = new RM_FileScan();
                    fileScan->openScan(&fileHandle, value_type, value_size, offset, op, col_values, col_index);
                  //  printf("base search\n");
                   // printf("op %c\n", whereclause->op_char);
                    fileScan->getAllRecord(rid_list);
                   // printf("base search ok %c\n", whereclause->op_char);
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



    double printSUM(map<RID,int>& rid_list,RM_FileAttr* fileAttr,string colname,RM_FileHandle& fileHandle){
        double sum = 0;
        for (map<RID, int>::iterator it = rid_list.begin(); it != rid_list.end(); ++it) {
//                                printf("type: %d\n",fileAttr->getColValueType(ope_columns[i]));
            if (fileAttr->getColValueType(colname) != AttrType::INT &&
                fileAttr->getColValueType(colname) != AttrType::FLOAT) {
                printf("column type error\n");
                return -1;
            }
            RID rid = it->first;
//                                printf("rid<%d,%d> \t", rid.pid, rid.sid);
            Record record;
            fileHandle.getRec(rid, record);
            int offset = fileAttr->getColValueOffset(colname);
            char *data = record.getData(offset);
            if (fileAttr->getColValueType(colname) == AttrType::INT) {
                sum += *((int *) data);
            } else if (fileAttr->getColValueType(colname) == AttrType::FLOAT) {
                sum += *((float *) data);
            }
        }
        return sum;
    }

    double printAVG(map<RID,int>& rid_list,RM_FileAttr* fileAttr,string colname,RM_FileHandle& fileHandle){
        double avg_sum = 0;
        int count = 0;
        for (map<RID, int>::iterator it = rid_list.begin(); it != rid_list.end(); ++it) {
            if (fileAttr->getColValueType(colname) != AttrType::INT &&
                fileAttr->getColValueType(colname) != AttrType::FLOAT) {
                printf("column type error\n");
                return -1;
            }
            RID rid = it->first;
//            printf("rid<%d,%d> \t", rid.pid, rid.sid);
            Record record;
            fileHandle.getRec(rid, record);
            int offset = fileAttr->getColValueOffset(colname);
            char *data = record.getData(offset);
            if (fileAttr->getColValueType(colname) == AttrType::INT) {
                avg_sum += *((int *) data);
            } else if (fileAttr->getColValueType(colname) == AttrType::FLOAT) {
                avg_sum += *((float *) data);
            }
            ++count;
        }
        return avg_sum/count;
    }

    double printMAX(map<RID,int>& rid_list,RM_FileAttr* fileAttr,string colname,RM_FileHandle& fileHandle){
        double max = 0;
        for (map<RID, int>::iterator it = rid_list.begin(); it != rid_list.end(); ++it) {
            if (fileAttr->getColValueType(colname) != AttrType::INT &&
                fileAttr->getColValueType(colname) != AttrType::FLOAT) {
                printf("column type error\n");
                return -1;
            }
            RID rid = it->first;
//            printf("rid<%d,%d> \t", rid.pid, rid.sid);
            Record record;
            fileHandle.getRec(rid, record);
            int offset = fileAttr->getColValueOffset(colname);
            char *data = record.getData(offset);
            if (fileAttr->getColValueType(colname) == AttrType::INT) {
                if (max < *((int *) data))
                    max = *((int *) data);
            } else if (fileAttr->getColValueType(colname) == AttrType::FLOAT) {
                if (max < *((float *) data))
                    max = *((float *) data);
            }
        }
        return max;
    }

    double printMIN(map<RID,int>& rid_list,RM_FileAttr* fileAttr,string colname,RM_FileHandle& fileHandle){
        double min = MAXDOUBLE;
        for (map<RID, int>::iterator it = rid_list.begin(); it != rid_list.end(); ++it) {
            if (fileAttr->getColValueType(colname) != AttrType::INT &&
                fileAttr->getColValueType(colname) != AttrType::FLOAT) {
                printf("column type error\n");
                return -1;
            }
            RID rid = it->first;
//            printf("rid<%d,%d> \t", rid.pid, rid.sid);
            Record record;
            fileHandle.getRec(rid, record);
            int offset = fileAttr->getColValueOffset(colname);
            char *data = record.getData(offset);
            if (fileAttr->getColValueType(colname) == AttrType::INT) {
                if (min > *((int *) data))
                    min = *((int *) data);
            } else if (fileAttr->getColValueType(colname) == AttrType::FLOAT) {
                if (min > *((float *) data))
                    min = *((float *) data);
            }
        }
        return min;
    }

    float getConstValue(Expr* expr) {
        float left = 0, right = 0;
        if(expr->expr2==NULL){
            if (expr->expr->type == kExprLiteralInt)
                left = expr->expr->ival;
            else if (expr->expr->type == kExprLiteralFloat)
                left = expr->expr->fval;
            return left;
        }
        if(expr->expr==NULL){
            if (expr->expr2->type == kExprLiteralInt)
                right = expr->expr2->ival;
            else if (expr->expr2->type == kExprLiteralFloat)
                right = expr->expr2->fval;
            return right;
        }
        if (isConst(expr->expr) && isConst(expr->expr2)) {
            if (expr->expr->type == kExprLiteralInt)
                left = expr->expr->ival;
            else if (expr->expr->type == kExprLiteralFloat)
                left = expr->expr->fval;

            if (expr->expr2->type == kExprLiteralInt)
                right = expr->expr2->ival;
            else if (expr->expr2->type == kExprLiteralFloat)
                right = expr->expr2->fval;
            printf("%d\n",kExprLiteralInt);
            printf("%d\n",kExprOperator);
            printf("%d\n",expr->type);
            printf("%d\n",expr->expr->type);
            printf("%d\n",expr->expr2->type);
            printf("left: %f;right: %f\n",left,right);
            switch (expr->op_char) {
                case '+':
                    return left + right;
                case '-':
                    return left - right;
                case '*':
                    return left * right;
                case '/': {
                    if (right == 0)
                        printf("division 0 ;expression is invalid\n");
                    return 0;
                }
                default:
                    return 0;
            }
        }
        left = getConstValue(expr->expr);
        right = getConstValue(expr->expr2);
        printf("left1: %f;right1: %f\n",left,right);
        switch (expr->op_char) {
            case '+':
                return left + right;
            case '-':
                return left - right;
            case '*':
                return left * right;
            case '/': {
                if (right == 0)
                    printf("division 0 ;expression is invalid\n");
                return 0;
            }
            default:
                return 0;
        }
        return 0;
    }
    bool isConst(Expr* expr){
        if(expr->type!=kExprOperator&&(expr->type==kExprLiteralInt||expr->type==kExprFunctionRef))
            return true;
        return false;
    }

    struct N_Table_Params {
        vector<string> table_list;
        vector<RM_FileAttr*> fileAttrList;
        vector<RM_FileHandle*> fileHandleList;
        map<string,IX_IndexHandle*> indexHandleMap;
        struct TableRecord{
            RID rid;//这条记录的rid
            int next_table_max_index;//这条记录对应下个表的记录的最大索引下标+1
            TableRecord() {
                next_table_max_index = 0;
            };
        };
        typedef vector<TableRecord*> RecordList;
        vector<RecordList*> table_record_list;
        //已经查过的所有表的数量
        int table_checked_number;
        DatabaseSystem* db;
        N_Table_Params() {
            this->table_checked_number = 0;
        }

        void init(DatabaseSystem* db, RecordManager* rm) {
            this->db = db;
            for(int i = 0; i < this->getTableCount(); ++i) {
                RM_FileHandle* fileHandle = new RM_FileHandle();
                rm->openFile(this->table_list[i].c_str(), *fileHandle);
                BufType fileHeader = fileHandle->getFileHeader();
                RM_FileAttr* fileAttr = new RM_FileAttr();
                fileAttr->getFileAttrFromPageHeader(fileHeader);
                fileAttrList.push_back(fileAttr);
                fileHandleList.push_back(fileHandle);
            }
        }

        void addTable(string tablename) {
            this->table_list.push_back(tablename);
            RecordList* record_list = new RecordList;
            this->table_record_list.push_back(record_list);
        }

        RecordList* getRecordList(string tablename) {
            for(int i = 0 ; i < table_list.size(); ++i) {
                if(table_list[i] == tablename) return table_record_list[i];
            }
        }

        int getTableCount() {
            return this->table_list.size();
        }
        void setNextTableMaxIndex(string tablename, int i, int index) {
            RecordList* list = this->getRecordList(tablename);
            (*list)[i]->next_table_max_index = index;
        }

        RC searchRIDListByWhereClauseOfNTable(Expr* whereclause, map<RID,int>& rid_list,
                                              map<string,Record*>& targetMap, map<string,RM_FileAttr*>& targetFileAttrMap,
                                              RM_FileHandle &fileHandle , int numIndent, string tableName){
            //没有where语句则直接返回
            if (whereclause == NULL) {
                printf("null where get all record\n");
                RM_FileScan *fileScan = new RM_FileScan();
                fileScan->openScan(&fileHandle, AttrType::FLOAT, 0, 0, CompOp::EQ_OP, NULL, 0);
                fileScan->getAllRecordOfFile(rid_list);
                delete fileScan;
                return RC(10);
            }
            //分表达式左边与右边查询，然后去合并的集合
            map<RID,int> left;
            map<RID,int> right;

            CompOp op = EQ_OP;

            switch (whereclause->op_type) {
                case Expr::LESS_EQ: {// <=
                    if(whereclause->op_type == Expr::LESS_EQ) op = LE_OP;
                }
                case Expr::GREATER_EQ: {// >=
                    if(whereclause->op_type == Expr::GREATER_EQ) op = GE_OP;
                }
                case Expr::NOT_EQUALS: {// <>
                    if(whereclause->op_type == Expr::NOT_EQUALS) op = NE_OP;
                }
                case Expr::LIKE: {
                    if(whereclause->op_type == Expr::LIKE) op = LIKE_OP;
                }
                case Expr::ISNULL: {
                    if(whereclause->op_type == Expr::ISNULL) {
                        //     printf("select null\n");
                        op = ISNULL_OP;
                    }
                }
                case Expr::SIMPLE_OP: {
                    //= < >
                    //递归基，符号两边为列名和属性值，进行查找
                    columnDef left_col,right_col;
                    if(whereclause->expr->table!=NULL)
                        left_col.tableName = whereclause->expr->table;
                    left_col.colName = whereclause->expr->name;

                    //如果这个表达式不是一个联合查询表达式，并且表达式左侧不是待查表，则该表达式必定为true
                    if( (!whereclause->isTableAssosicateOP()) &&
                        (left_col.tableName != tableName)) {
                        //均返回待查表的所有记录
//                        printf("where is not assosication but %d, search and left not target table but %s, get all record\n",whereclause->expr2->type,left_col.tableName.c_str());
//                        RM_FileScan *fileScan = new RM_FileScan();
//                        fileScan->openScan(&fileHandle, AttrType::FLOAT, 0, 0, CompOp::EQ_OP, NULL, 0);
//                        fileScan->getAllRecordOfFile(rid_list);
//                        delete fileScan;
                        return RC(10);
                    }

                    //要获取的待查表的数据信息
                    RM_FileAttr *fileAttr = new RM_FileAttr();
                    int offset = 0, value_size = 0, col_index = 0;
                    AttrType value_type = AttrType::INT;
                    ColType col_type = ColType::NORMAL;

                    char *col_values;

                    if(left_col.tableName == tableName) {
                        //如果表达式左侧表名为待查表，则获取左侧表的数据信息

                        //表达式左侧表的表头handle
                        fileAttr->getFileAttrFromPageHeader(fileHandle.getFileHeader());
                        //数据行的偏移量
                        offset = fileAttr->getColValueOffset(left_col.colName);
                        //数据列对应数据长度
                        value_size = fileAttr->getColValueSize(left_col.colName);
                        //数据类型
                        value_type = fileAttr->getColValueType(left_col.colName);
                        //列类型
                        col_type = fileAttr->getColType(left_col.colName);
                        //数据列位置
                        col_index = fileAttr->getColIndex(left_col.colName);
                        //待比较数据
                        col_values = new char[value_size];
                    }

                    // printf("col_index %d\n",col_index);
                    char op_char = whereclause->op_char;
                    if (op_char == '<') {
                        op = LT_OP;
                    } else if (op_char == '>') {
                        op = GT_OP;
                    } else if (op_char == '=') {
                        op = EQ_OP;
                    }

                    //whereclause->expr2 为目标属性值表达式
                    if(!(op == CompOp::ISNULL_OP)) {
                        switch (whereclause->expr2->type) {
                            //根据类型进行处理
                            case kExprLiteralFloat:
                                *((float *) col_values) = whereclause->expr2->fval;
                                break;
                            case kExprLiteralInt:
                                *((int *) col_values) = whereclause->expr2->ival;
                                break;
                            case kExprLiteralString:
//                            printf("taget: %s\n", whereclause->expr2->name);
                                strcpy(col_values, whereclause->expr2->name);
                                break;
                            case kExprOperator:
                                if (value_type == AttrType::INT) {
                                    *((int *) col_values) = (int) this->db->getConstValue(whereclause->expr2);
                                    printf("expr2_value: %d \n", *((int *) col_values));
                                } else if (value_type == AttrType::FLOAT) {
                                    *((float *) col_values) = this->db->getConstValue(whereclause->expr2);
                                }
                                break;
                            case kExprColumnRef:{
                                //该表达式是个联合查询表达式

                                if (whereclause->expr2->table != NULL)
                                    right_col.tableName = whereclause->expr2->table;
                                right_col.colName = whereclause->expr2->name;

                                //表达式左右都不存在说明待匹配数据表还未查，此表达式结果为true
                                bool both_checked = (targetMap.count(left_col.tableName) > 0 &&
                                                     targetMap.count(right_col.tableName) > 0);
                                //表达式左右都存在，则此表达式结果必定为true
                                bool neither_checked = (targetMap.count(left_col.tableName) == 0 &&
                                                        targetMap.count(right_col.tableName) == 0);
                                //表达式一方是待查表另外一方不存在
                                bool other_not_checked =
                                        (right_col.tableName == tableName && targetMap.count(left_col.tableName) == 0)
                                        || (left_col.tableName == tableName && targetMap.count(right_col.tableName) == 0);
                                //表达式左右都不是待查表
                                bool neither_is_target_table =
                                        (right_col.tableName != tableName) && (left_col.tableName != tableName);
                                //若该表达式必定为true，则获取所有记录
                                bool get_all_record = other_not_checked || neither_is_target_table;


                                if (get_all_record) {
                                    //均返回待查表的所有记录
//                                    printf("get all record, because:\n");
//                                    cout << "other_not_checked: " << other_not_checked << endl;
//                                    cout << "neither_is_target_table: " << neither_is_target_table << endl;
//                                    RM_FileScan *fileScan = new RM_FileScan();
//                                    fileScan->openScan(&fileHandle, AttrType::FLOAT, 0, 0, CompOp::EQ_OP, NULL, 0);
//                                    fileScan->getAllRecordOfFile(rid_list);
//                                    delete fileScan;
                                    delete fileAttr;
                                    return RC(10);
                                }

                                //否则进行查找
                                if (right_col.tableName == tableName) {//表达式右侧为待查项，需要重新构造数据信息
                                 //   cout<<"target in right "<<right_col.colName<<endl;
                                    //获取表头信息
                                    fileAttr->getFileAttrFromPageHeader(fileHandle.getFileHeader());
                                    //数据行的偏移量
                                    offset = fileAttr->getColValueOffset(right_col.colName);
                                    //数据列对应数据长度
                                    value_size = fileAttr->getColValueSize(right_col.colName);
                                    //数据类型
                                    value_type = fileAttr->getColValueType(right_col.colName);
                                    //列类型
                                    col_type = fileAttr->getColType(right_col.colName);
                                    //数据列位置
                                    col_index = fileAttr->getColIndex(right_col.colName);

                                    //目标数据的记录
                                    Record *target_record = targetMap[left_col.tableName];
                                    //目标数据的表头信息
                                    RM_FileAttr *target_fileAttr = targetFileAttrMap[left_col.tableName];
                                    //获取待比较的目标数据
                                    int target_offset = target_fileAttr->getColValueOffset(left_col.colName);
                                    col_values = target_record->getData(target_offset);
                                } else if (left_col.tableName == tableName) {
                                    //目标数据的记录
                                    Record *target_record = targetMap[right_col.tableName];
                                    //目标数据的表头信息
                                    RM_FileAttr *target_fileAttr = targetFileAttrMap[right_col.tableName];
                                    //获取待比较的目标数据
                                    int target_offset = target_fileAttr->getColValueOffset(right_col.colName);
                                    cout<<"right offset: "<<target_offset<<endl;
                                    col_values = target_record->getData(target_offset);
                                } else {
                                    printf("ERROR!\n");
                                    return RC(-1);
                                }
                                cout<<"association search: "<<left_col.tableName<<"."<<left_col.colName<<"="<<right_col.tableName<<"."<<right_col.colName<<endl;
                                cout<<*((int*)(col_values))<<endl;
                                break;
                            }
                            default:
                                return RC(-1);
                        }
                    }
                    cout<<"search"<<" "<<col_type<<endl;
                    //如果查找列是索引列，并且是等号查找，并且不是模糊查找，则按索引查找
                    if(true && (col_type == ColType::INDEX || col_type == ColType::UNIQUE || col_type == ColType::PRIMARY) && op == CompOp::EQ_OP) {
                     //   printf("index search\n");
                     //   cout<<"association search: "<<left_col.tableName<<"."<<left_col.colName<<"="<<right_col.tableName<<"."<<right_col.colName<<endl;
                     //   cout<<*((int*)(col_values))<<endl;
                        IX_IndexScan* indexScan = new IX_IndexScan();
                        string col_name = left_col.colName;
                        if(left_col.tableName != tableName) col_name = right_col.colName;
                        string indexName = fileAttr->getIndexName(tableName,col_name);
                        if(this->indexHandleMap.count(indexName)==0) {
                            IX_IndexHandle *indexHandle = new IX_IndexHandle();
                            printf("index filename %s\n", indexName.c_str());
                            this->db->indexManager->OpenIndex(indexName.c_str(), *indexHandle);
                            this->indexHandleMap.insert(pair<string,IX_IndexHandle*>(indexName,indexHandle));
                        }

                        IX_IndexHandle *indexHandle = this->indexHandleMap[indexName];
                        indexScan->OpenScan(indexHandle,op,col_values);
                        cout<<"begin index search"<<endl;
                        indexScan->getAllRecord(rid_list);
                        cout<<"index search ok, find: "<<rid_list.size()<<endl;
                        delete indexScan;
                    }
                    else {
                        RM_FileScan *fileScan = new RM_FileScan();
                        fileScan->openScan(&fileHandle, value_type, value_size, offset, op, col_values, col_index);
                        printf("base search\n");
                        printf("op %c\n", whereclause->op_char);
                        fileScan->getAllRecord(rid_list);
                        // printf("base search ok %c\n", whereclause->op_char);
                        delete fileScan;
                    }
                    delete fileAttr;
                    break;
                }
                    //符号两边为表达式，继续递归根据符号取交、并、补
                case Expr::AND: {
                    RC l_rc = searchRIDListByWhereClauseOfNTable(whereclause->expr, left,
                                                                 targetMap,targetFileAttrMap,
                                                                 fileHandle, numIndent + 1,tableName);
                    RC r_rc = searchRIDListByWhereClauseOfNTable(whereclause->expr2, right,
                                                                 targetMap,targetFileAttrMap,
                                                                 fileHandle, numIndent + 1,tableName);
                    if(l_rc.equal(RC(10)) && r_rc.equal(RC(10))) {
                        if(numIndent == 0) {
                            printf("get all record\n");
                            RM_FileScan *fileScan = new RM_FileScan();
                            fileScan->openScan(&fileHandle, AttrType::FLOAT, 0, 0, CompOp::EQ_OP, NULL, 0);
                            fileScan->getAllRecordOfFile(rid_list);
                            delete fileScan;
                            return RC();
                        }
                        else
                            return RC(10);
                    }
                    else if(r_rc.equal(RC(10))) {
                        map<RID, int>::iterator it;
                        //右表达式为true
                        //返回左表达式的所有取值
                        for (it = left.begin(); it != left.end(); ++it) {
                            rid_list.insert(pair<RID, int>(it->first, 1));
                        }
                        break;
                    }
                    else if(l_rc.equal(RC(10))) {
                        map<RID, int>::iterator it;
                        //左表达式为true
                        //返回右表达式的所有取值
                        for (it = right.begin(); it != right.end(); ++it) {
                            rid_list.insert(pair<RID, int>(it->first, 1));
                        }
                        break;
                    }

                    map<RID, int>::iterator it;
                    //循环遍历左边表达式选取的项在右边表达式是否存在
                    for (it = left.begin(); it != left.end(); ++it) {
                        //判断在右边是否存在
                        map<RID, int>::iterator r_it = right.find(it->first);
                        //不存在则下一个
                        if (r_it == right.end()) continue;
                        rid_list.insert(pair<RID, int>(it->first, 1));
                    }
                    printf("AND\n");
                    return RC();
                }
                case Expr::OR: {
                    RC l_rc = searchRIDListByWhereClauseOfNTable(whereclause->expr, left,
                                                                 targetMap,targetFileAttrMap,
                                                                 fileHandle, numIndent + 1,tableName);
                    RC r_rc = searchRIDListByWhereClauseOfNTable(whereclause->expr2, right,
                                                                 targetMap,targetFileAttrMap,
                                                                 fileHandle, numIndent + 1,tableName);
                    if(l_rc.equal(RC(10)) || r_rc.equal(RC(10))) {
                        if(numIndent == 0) {
                            printf("get all record\n");
                            RM_FileScan *fileScan = new RM_FileScan();
                            fileScan->openScan(&fileHandle, AttrType::FLOAT, 0, 0, CompOp::EQ_OP, NULL, 0);
                            fileScan->getAllRecordOfFile(rid_list);
                            delete fileScan;
                            return RC();
                        }
                        else
                            return RC(10);
                    }
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
            return RC();
        }

        //table_index表的的record_index条记录为条件
        void search(int table_index, int record_index, Expr* where, TableRecord* lastTableRecord,
                    map<string,Record*> &targetMap, map<string,RM_FileAttr*>& targetFileAttrMap,
                    RM_FileHandle *check_fileHandle ) {
            if(table_index >= table_checked_number) {
                cout<<"check new table"<<endl;
                //前面的所有记录信息已经匹配，直接查找
                map<RID,int> rid_list;
                //要查询的表名
                string tableName = this->table_list[table_index];
                //进行查找
                cout<<"search table: "<<tableName<<endl;

                this->searchRIDListByWhereClauseOfNTable(where,rid_list,targetMap,targetFileAttrMap,*check_fileHandle,0,tableName);
                cout<<"search table: "<<tableName<<" ok, add to list"<<endl;

                RecordList* list = this->getRecordList(tableName);
                map<RID, int>::iterator it;
                for (it = rid_list.begin(); it != rid_list.end(); ++it) {
                    RID rid = it->first;
                    TableRecord* record = new TableRecord();
                    record->rid = rid;
                    (*list).push_back(record);
                }
                //如果查的不是第一张表，则要更新连接到该表的上表记录的索引
                if(lastTableRecord != NULL) {
                    lastTableRecord->next_table_max_index = (int) (*list).size();
                }
                return;
            }
            else {
                string tableName = this->table_list[table_index];
                cout<<"\ncheck last table: "<<tableName<<endl;
                RM_FileHandle* fileHandle = this->fileHandleList[table_index];
                RM_FileAttr* fileAttr = this->fileAttrList[table_index];
                RecordList* list = this->table_record_list[table_index];

                if(record_index >= (*list).size()) {
                    return;
                }

                TableRecord* tableRecord = (*list)[record_index];
                Record record;
                fileHandle->getRec(tableRecord->rid,record);
//             rid_list.insert(pair<RID, int>(it->first, 1));
                if(targetMap.count(tableName) == 0)
                    targetMap.insert(pair<string,Record*>(tableName,&record));
                else targetMap[tableName] = &record;

                if(targetFileAttrMap.count(tableName) == 0)
                    targetFileAttrMap.insert(pair<string,RM_FileAttr*>(tableName,fileAttr));

                if( table_index < table_checked_number-1 ) {
                    //如果之后还有已经查过的表
                    int start = 0;
                    if (record_index > 0) {
                        start = (*list)[record_index - 1]->next_table_max_index;
                    }
                    for (int i = start; i < tableRecord->next_table_max_index; ++i) {
                        this->search(table_index + 1, i, where, tableRecord, targetMap, targetFileAttrMap,
                                     check_fileHandle);
                    }
                }

                else {
                    //如果之后没有表
                    this->search(table_index + 1, 0, where, tableRecord, targetMap, targetFileAttrMap,
                                 check_fileHandle);
                }

            }
        }

        void getAssociationSearchResult(Expr* where) {
            for(int i = 0; i < this->getTableCount(); ++i) {
                //每个表作一次查询
                map<string,Record*> targetMap;
                map<string,RM_FileAttr*> targetFileAttrMap;
                cout<<"try to search table: "<<this->table_list[i]<<endl;
                if(i == 0)
                    this->search(0,0,where,NULL,targetMap,targetFileAttrMap,this->fileHandleList[i]);
                else
                    for(int j = 0 ; j < this->table_record_list[0]->size(); ++j) {
                        this->search(0,j,where,NULL,targetMap,targetFileAttrMap,this->fileHandleList[i]);
                    }
                printf("search %s ok, find %d record\n\n",this->table_list[i].c_str(),(this->table_record_list[i]->size()));
                this->table_checked_number ++;
            }
        }

        typedef vector<RID> Result;
        typedef vector<Result> ResultList;

        void getAllResult(int table_index, int record_index, Result& result, ResultList& list) {
            if(table_index >= this->table_list.size()-1) {
                //已经是最后一个表了
                RecordList* record_list = this->table_record_list[table_index];
                //要的超过限制
                if(record_index >= record_list->size())
                    return;
                //
                TableRecord* record = (*record_list)[record_index];
                result.push_back(record->rid);
                //往列表中塞入
                list.push_back(result);
                //弹出最后项继续
                result.pop_back();
                return;
            }
            else {
                //不是最后个表
                string tableName = this->table_list[table_index];
                RecordList* record_list = this->table_record_list[table_index];

                if(record_index >= (*record_list).size()) {
                    //上表要的记录该表没有，则返回
                    return;
                }

                TableRecord* tableRecord = (*record_list)[record_index];
                result.push_back(tableRecord->rid);

                //往下一个表查询
                int start = 0;
                if (record_index > 0) {
                    start = (*record_list)[record_index - 1]->next_table_max_index;
                }
                for (int i = start; i < tableRecord->next_table_max_index; ++i) {
                    //从下一个表的第i条记录开始查询
                    getAllResult(table_index+1,i,result,list);
                }
                //对于该表的该记录已经全部遍历，弹出
                result.pop_back();

            }
        }

        void printAll(ResultList list,vector<columnDef>& no_columns) {
            if(no_columns.size()==1&&no_columns[0].colName=="*"){
                no_columns.clear();
                for(int i=0;i<this->fileAttrList.size();++i){
                    int attrSize = this->fileAttrList[i]->key_name.size();
                    for(int j=0;j<attrSize;++j){
                        columnDef temp_col;
                        temp_col.tableName = this->table_list[i];
                        temp_col.colName = this->fileAttrList[i]->key_name[j];
                        no_columns.push_back(temp_col);
                    }
                }
            }
            for(columnDef i:no_columns){
                printf("%s.%s     |",i.tableName.c_str(),i.colName.c_str());
            }
            printf("\n");
            for(int i = 0; i < list.size(); ++i) {
                Result result = list[i];
//                printf("number %d: \n",i);
                for(int k=0;k<no_columns.size();++k){
                    RM_FileAttr* fileAttr;
                    RM_FileHandle* fileHandle;
                    columnDef cur_col = no_columns[k];
                    Record record;
                    for(int j = 0; j < result.size(); ++j) {
                        if(this->table_list[j]==cur_col.tableName){
                            RID rid = result[j];
                            fileAttr = this->fileAttrList[j];
                            int  offset = fileAttr->getColValueOffset(cur_col.colName);
                            fileHandle = this->fileHandleList[j];
                            fileHandle->getRec(rid,record);
                            char* data = record.getData(offset);
                            int col_index = fileAttr->getColIndex(cur_col.colName);
                            if (record.isNULL(col_index)) {
                                printf("null  \t");
                            } else {
                                fileAttr->printData(data,cur_col.colName);
                            }
                            break;
                        }
                    }
                }
                printf("\n");
            }
        }

        void printTest(vector<columnDef>& no_columns) {
            Result result;
            ResultList list;
            for(int j = 0 ; j < this->table_record_list[0]->size(); ++j) {
                this->getAllResult(0,j,result,list);
            }
            //this->getAllResult(0,0,result,list);
            cout<<"found: "<<list.size()<<endl;
            this->printAll(list,no_columns);
        }

        RC firgureTableTime(Expr* whereclause, map<string,int>& tableMap){
            //没有where语句则直接返回
            if (whereclause == NULL) {
                return RC();
            }
            CompOp op = EQ_OP;

            switch (whereclause->op_type) {
                case Expr::NOT:
                case Expr::LESS_EQ:
                case Expr::GREATER_EQ:
                case Expr::NOT_EQUALS:
                case Expr::LIKE:
                case Expr::ISNULL:
                case Expr::SIMPLE_OP: {
                    //= < >
                    //递归基，符号两边为列名和属性值，进行查找
                    columnDef left_col,right_col;
                    if(whereclause->expr->table!=NULL)
                        left_col.tableName = whereclause->expr->table;
                    tableMap[left_col.tableName]++;
                    if(whereclause->isTableAssosicateOP()) {
                        if (whereclause->expr2->table != NULL)
                            right_col.tableName = whereclause->expr2->table;
                        tableMap[right_col.tableName]++;
                    }
                    break;
                }
                    //符号两边为表达式，继续递归根据符号取交、并、补
                case Expr::AND:
                case Expr::OR: {
                    RC l_rc = firgureTableTime(whereclause->expr,tableMap);
                    RC r_rc = firgureTableTime(whereclause->expr2,tableMap);
                    break;
                }
                default: {
                    printf("%d\n", whereclause->op_type);
                    break;
                }
            }
            return RC();
        }
    };

};



#endif //DATABASE_DATABASESYSTEM_H
