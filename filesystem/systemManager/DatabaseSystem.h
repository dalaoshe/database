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
                int attrCount = createStatement->columns->size();
                for(int i=0;i<attrCount;++i){
                    printf("attr_name: %s \t  ",(*(createStatement->columns))[i]->name);
                    printf("attr_type: %d \t  ",(*(createStatement->columns))[i]->type);
                    printf("attr_size: %d \t  ",(*(createStatement->columns))[i]->size);
                    printf("attr_not_null: %d\t\n",(*(createStatement->columns))[i]->not_null);
                }
                RM_FileAttr* attr = new RM_FileAttr[1];
                for(int i=0;i<attrCount;++i){
                    attr->key_name.push_back(string((*(createStatement->columns))[i]->name));
                    attr->key_type.push_back((*(createStatement->columns))[i]->type);
                    attr->value_length.push_back((*(createStatement->columns))[i]->size);
                    int k = (*(createStatement->columns))[i]->not_null;
                    attr->not_null.push_back(k);
                }
                system_manager->CreateTable(createStatement->tableName,attrCount,attr);
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
                fileAttr->buildValidInsertData(insertStmt,data);
                //打印记录
                //fileAttr->printRecordInfo(data);
                //插入槽
                RID rid;
                fileHandle.insertRec(data,rid);
                printf("rid pid %d sid %d\n",rid.pid,rid.sid);
                delete fileAttr;
                return "";
            }
            case kStmtSelect:{
                //打印语句信息
                printSelectStatementInfo((SelectStatement*)stmt, 0);
                printf("select options\n");
                SelectStatement* selectStatement = (SelectStatement*)stmt;
                //获取要选取的表名
                string filename = selectStatement->fromTable->getName();
                RM_FileHandle fileHandle;

                //获取rm handle
                recordManager->openFile(filename.c_str(),fileHandle);
                BufType fileHeader = fileHandle.getFileHeader();
                //获取表头信息
                RM_FileAttr* fileAttr = new RM_FileAttr();
                fileAttr->getFileAttrFromPageHeader(fileHeader);


                map<RID,int>rid_list;
                this->searchRIDListByWhereClause(selectStatement->whereClause,rid_list,fileHandle,0,selectStatement->fromTable->getName());
                printf("rid size %d\n",rid_list.size());
//                //获取记录
//                Record record;
//                RID rid; rid.pid=1; rid.sid=6;
//                fileHandle.getRec(rid,record);

                //打印记录
                map<RID, int>::iterator it;
                //循环遍历左边表达式选取的项在右边表达式是否存在
                for (it = rid_list.begin(); it != rid_list.end(); ++it) {
                    //判断在右边是否存在

                    RID rid = it->first;
                    printf("rid<%d,%d> \t",rid.pid,rid.sid);
                    Record record;
                    fileHandle.getRec(rid,record);
                    //不存在则下一个

                    fileAttr->printRecordInfo(record.getData());
                }



                return "";
            }
            case kStmtUpdate:{
                //printUpdateStatementInfo((UpdateStatement*)stmt, 0);
                printf("update \n  ");
                return "";
            }
            case kStmtDelete:{
                //printDeleteStatementInfo((DeleteStatement*)stmt, 0);

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
            while (getline(fin,sql_stmt)){
                if(sql_stmt=="")
                    continue;
                cout<<sql_stmt<<endl;
                string result = readSQL(sql_stmt);
                printf("\n");
//                printf("%s",result.c_str());
            }
        }
        fin.close();
        return  "";
    }

    RC searchRIDListByWhereClause(Expr* whereclause, map<RID,int> & rid_list , RM_FileHandle &fileHandle , int numIndent, char* tableName) {
        //whereclause type is kExprOperator
        if (whereclause == NULL) {
            printf("null\n", numIndent);

            return RC(-1);
        }
        map<RID,int> left;
        map<RID,int> right;
        CompOp op;
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
                        //print(expr->fval, numIndent);
                        break;
                    case kExprLiteralInt:
                        *((int *) col_values) = whereclause->expr2->ival;
                        //inprint(expr->ival, numIndent);
                        break;
                    case kExprLiteralString:
                        strcpy(col_values, whereclause->expr2->name);
                        //inprint(expr->name, numIndent);
                        break;
                    default:
                        //fprintf(stderr, "Unrecognized expression type %d\n", expr->type);
                        return RC(-1);
                }
                if(col_type == ColType::INDEX || col_type == ColType::UNIQUE) {
                    printf("index search\n");
                    IX_IndexScan* indexScan = new IX_IndexScan();
                    string indexName = fileAttr->getIndexName(tableName,col_name);
                    IX_IndexHandle indexHandle;
                    printf("index filename %s\n",indexName.c_str());
                    this->indexManager->OpenIndex(indexName.c_str(),1,indexHandle);
                    indexScan->OpenScan(&indexHandle,op,col_values);
                    indexScan->getAllRecord(rid_list);
                    delete indexScan;
                }
                else {
                    RM_FileScan *fileScan = new RM_FileScan();
                    fileScan->openScan(&fileHandle, value_type, value_size, offset, op, col_values);
                    printf("base search\n");
                    printf("op %c\n", whereclause->op_char, numIndent);
                    fileScan->getAllRecord(rid_list);
                    printf("base search ok %c\n", whereclause->op_char, numIndent);
                    delete fileScan;
                }
                delete fileAttr;

                printf("delete ok %c size %d \n", whereclause->op_char, rid_list.size());
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
                printf("AND", numIndent);
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
                printf("OR", numIndent);
                return RC();
            }
            case Expr::NOT: {
                printf("NOT", numIndent);
                break;
            }
            default: {
                printf("%d\n", whereclause->op_type, numIndent);
                break;
            }
        }
    }
};


#endif //DATABASE_DATABASESYSTEM_H
