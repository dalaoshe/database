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
                BufType data;
                fileAttr->buildValidInsertData(insertStmt,data);
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

                //获取记录
                Record record;
                RID rid; rid.pid=1; rid.sid=0;
                fileHandle.getRec(rid,record);

                //打印记录
                fileAttr->printRecordInfo(record.getData());


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
};


#endif //DATABASE_DATABASESYSTEM_H
