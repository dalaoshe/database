//
// Created by ykd on 16-11-25.
//
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <sstream>
#include <cstring>
#include "../utils/base.h"
#include "../utils/rc.h"
#include "../indexmanager/IndexManager.h"
#include "../recordmaneger/RecordManager.h"

#ifndef DATABASE_SM_MANAGER_H
#define DATABASE_SM_MANAGER_H

#define DBLIST "DBList.txt"
#define DBROOT "../DatabaseRoot"
#define TABLELIST "TableList.txt"
// Used by SM_Manager::CreateTable
struct AttrInfo {
    char     *attrName;           // Attribute name
    AttrType attrType;            // Type of attribute
    int      attrLength;          // Length of attribute
};

// Used by Printer class
struct DataAttrInfo {
    char     relName[MAXNAME+1];  // Relation name
    char     attrName[MAXNAME+1]; // Attribute name
    int      offset;              // Offset of attribute
    AttrType attrType;            // Type of attribute
    int      attrLength;          // Length of attribute
    int      indexNo;             // Attribute index number
};


class SM_Manager {
    FileManager* fm;
    BufPageManager* bpm;
    IndexManager* ixm;
    RecordManager* rmm;
    vector<string> DBlist;
    vector<string> TableList;
    string DBRootPath;
    string currentDB;
    string currentWorkingPath;//for debug

    //change working dir
    bool changeWorkingDir(const char* dir){
        int des = chdir(dir);
        if(des<0){
            printf("change to working directory %s failed!\n",dir);
            return false;
        }
        currentWorkingPath = string(dir);
    }

    //check whether file exists
    bool checkFileExist(const char* file){
        FILE* fh = fopen(file,"r");
        if(fh == NULL)
        {
            return false;
        }
        return true;
    }
public:
    SM_Manager  (IndexManager* ixm, RecordManager* rmm, FileManager* fm, BufPageManager* bpm) {  // Constructor
        //初始化
        this->fm = fm;
        this->bpm = bpm;
        this->ixm = ixm;
        this->rmm = rmm;

        //更换工作目录
        ifstream db_root;
        db_root.open(DBROOT);
        if(!db_root){
            if(mkdir(DBROOT,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)) {
                printf("DBROOT working directory failed to be craeted!\n");
                return ;
            }
        }
        db_root.close();

        changeWorkingDir(DBROOT);

        char root[100];
        getcwd(root,100);
        DBRootPath = string(root);

        ifstream db_list;
        db_list.open(DBLIST);
        if(!db_list){
            fopen(DBLIST,"W");
            ofstream fout(DBLIST);
            fout<<0<<endl;
            fout.close();
        }
        db_list.close();

        ifstream fin(DBLIST);
        int num = 0;
        fin>>num;
        char db_name[100];
        for(int i=0;i<num;++i){
            fin>>db_name;
            DBlist.push_back(string(db_name));
        }
        fin.close();
    }
    ~SM_Manager (){// Destructor
        CloseDB();
        ofstream fout(DBLIST);
        unsigned long size = DBlist.size();
        fout<<size<<endl;
        for(unsigned long i=0;i<size;++i){
            fout<<DBlist[i]<<endl;
        }
        fout.close();
        DBlist.clear();
    }
    RC createDB    (const char *dbname) {                //create database
        //save old path
        char old_path[100];
        if(!dbname)return RC(-1);
        getcwd(old_path,100);

        vector<string>::iterator it = find(DBlist.begin(), DBlist.end(), string(dbname));
        if(it != DBlist.end()){
            printf("Error: The DataBase %s has already exist.\n",dbname);
            return RC(-1);
        }
        changeWorkingDir(DBRootPath.c_str());
        int status = mkdir(dbname,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if(status ==-1){
            printf("ERROR: Create database %s failed\n",dbname);
            return RC(-1);
        }

        vector<string> db_names;
        int db_count = 0;
        ifstream fin(DBLIST);
        fin>>db_count;
        string temp_name;
        while (getline(fin,temp_name)){
            if(temp_name!="")
                db_names.push_back(temp_name);
        }
        fin.close();
        ++db_count;
        db_names.push_back(string(dbname));
        ofstream fout1(DBLIST);
        fout1<<db_count<<endl;
        for(int i=0;i<db_count;++i){
            fout1<<db_names[i]<<endl;
        }

        changeWorkingDir(dbname);
        ofstream fout2(TABLELIST);
        fout2<<0<<endl;
        fout2.close();
        DBlist.push_back(string(dbname));
        printf("Create database %s succeed\n",dbname);

        //back to original working dir
        changeWorkingDir(old_path);
        return RC(0);
    }
    RC dropDB      (const char *dbname){                //drop database
        char old_path[100];
        if(!dbname)return RC(-1);
        getcwd(old_path,100);

        if(currentDB == string(dbname)){
            CloseDB();
        }
        string dir = DBRootPath+"/"+string(dbname);
        ////cout<<dir<<endl;
        DIR* Dir = opendir(dir.c_str());
        if(Dir == NULL){
            printf("Error: The DataBase %s does not exist.\n",dbname);
            return RC(-1);
        }
        //remove file
        struct dirent *dirEntry = NULL;
        while((dirEntry = readdir(Dir)) != NULL)
        {
            if(dirEntry->d_name[0] == '.')
                continue;
            string fileDir = dir + string("/") + string(dirEntry->d_name);
            int res = remove(fileDir.c_str());
            if(res == -1){
                printf("Error: drop DataBase : %s failed.\n",dbname);
                return RC(-1);
            }
        }
        closedir(Dir);
        //remove dirctory
        int res = rmdir(dir.c_str());
        if(res == -1){
            printf("Error: drop DataBase: %s failed.\n",dbname);
            return RC(-1);
        }
        //remove from DBlist
        vector<string>::iterator it = find(DBlist.begin(), DBlist.end(), dbname);
        DBlist.erase(it);
        changeWorkingDir(DBRootPath.c_str());
        ofstream fout1(DBLIST);
        unsigned long db_count = DBlist.size();
        fout1<<db_count<<endl;
        for(int i=0;i<db_count;++i){
            fout1<<DBlist[i]<<endl;
        }
        printf("Drop DataBase: %s succeed.\n",dbname);

        changeWorkingDir(old_path);
        return RC();
    }

    RC OpenDB      (const char *dbName){                // Open database
        //not exist
        vector<string>::iterator it = find(DBlist.begin(), DBlist.end(), string(dbName));
        if(it == DBlist.end()){
            printf("Error: The DataBase %s doesn't exist.\n",dbName);
            return RC(-1);
        }
        //already open
        if((string)dbName == currentDB){
            printf("Error: The DataBase %s already open.\n",dbName);
            return RC(-1);
        }
        CloseDB();
        currentDB = dbName;
        string dir = DBRootPath+"/"+string(dbName);
        changeWorkingDir(dir.c_str());

        ifstream fin(TABLELIST);
        int table_size;
        fin>>table_size;
        string table_name;
        for(int i=0;i<table_size;++i){
            fin>>table_name;
            TableList.push_back(table_name);
            //TODO 初始化对表的一些列操作

        }
        fin.close();
        printf("use database %s succeed ! tablelist size: %d\n",dbName,TableList.size());
        return RC();
    }

    RC CloseDB     (){// Close database
        if(!currentDB.empty()){
            ofstream fout(TABLELIST);
            unsigned long size = TableList.size();
            fout<<size<<endl;
            for(unsigned long i=0;i<size;++i){
                fout<<TableList[i]<<endl;
            }
            fout.close();
            TableList.clear();
        }
        TableList.clear();
        //TODO 关闭数据库时各种文件管理的输入输出句柄应关闭
        /*
         *
         */
        changeWorkingDir(DBRootPath.c_str());
    }

    RC ShowDatabases(){
        ifstream fin(DBRootPath+"/"+DBLIST);
        int count = 0;
        fin>>count;
        printf("database size : %d\n",count);
        for(int i=0;i<count;++i){
            string db_name;
            fin>>db_name;
            printf("%s\n",db_name.c_str());
        }
        printf("\n");
    }

    RC CreateTable (const char *relName,                // Create relation
                    int        attrCount,
                    RM_FileAttr   *attributes){
        printf("tablelist size: %d\n",TableList.size());
        vector<string>::iterator it = find(TableList.begin(), TableList.end(), string(relName));
        if(it != TableList.end()){
            printf("Error: The table %s already exists.\n",relName);
            return RC(-1);
        }
        int size = 0;
        for(int i=0;i<attributes->value_length.size();++i){
            size += attributes->value_length[i];
        }
        rmm->createFile(relName,attributes);

        TableList.push_back(string(relName));
        ifstream fin(TABLELIST);
        int table_size;
        fin>>table_size;
        ++table_size;
        fin.close();
        ofstream fout(TABLELIST);
        fout<<table_size<<endl;
        for(int i=0;i<table_size;++i){
            fout<<TableList[i]<<endl;
        }
    }

    RC DropTable   (const char *relName) {               // Destroy relation
        vector<string>::iterator it = find(TableList.begin(), TableList.end(), string(relName));
        if(it != TableList.end()){
            TableList.erase(it);
            remove(relName);
            // TODO 对表的一些操作
        }
        else {
            printf("Error: The table %s doesn't exist.\n",relName);
            return RC(-1);
        }
        ifstream fin(TABLELIST);
        int table_size;
        fin>>table_size;
        --table_size;
        fin.close();
        ofstream fout(TABLELIST);
        fout<<table_size<<endl;
        for(int i=0;i<table_size;++i){
            fout<<TableList[i]<<endl;
        }

    }

    RC ShowTables(){
        ifstream fin(TABLELIST);
        int count = 0;
        fin>>count;
        printf("table size : %d\n",count);
        for(int i=0;i<count;++i){
            string tb_name;
            fin>>tb_name;
            printf("%s\n",tb_name.c_str());
        }
        printf("\n");
    }

    RC CreateIndex (const char *relName,                // Create index
                    const char *attrName){
        //TODO 已经创建了索引（索引文件存在）
        //检查表是否存在
        if(!checkFileExist(relName)){
            printf("the table %s doesn't exist",relName);
            return RC(-1);
        }




        RM_FileHandle fileHandle;
        rmm->openFile(relName,fileHandle);
        BufType fileHeader = fileHandle.getFileHeader();
        RM_FileAttr* fileAttr = new RM_FileAttr();
        //获取头页信息
        fileAttr->getFileAttrFromPageHeader(fileHeader);
        //检查索引文件是否已经建立
        string indexName = fileAttr->getIndexName(relName,attrName);
        if(checkFileExist(indexName.c_str())){
            printf("the indexFile %s has exist",indexName);
            delete fileAttr;
            return RC(-1);
        }
        //获取要建立为索引的列的信息
        AttrType key_type = fileAttr->getColValueType(attrName);
        int key_size = fileAttr->getColValueSize(attrName);
        //建立索引
        if(ixm->CreateIndex(indexName.c_str(),0,key_type,key_size).equal(RC())) {
            //建立索引文件成功，修改头页对应列的列类型
            fileAttr->setColType(attrName,ColType::INDEX);
            //获取索引列的信息
            int offset = fileAttr->getColValueOffset(attrName);
            //数据列对应数据长度
            int value_size = fileAttr->getColValueSize(attrName);
            //数据类型
            AttrType value_type = fileAttr->getColValueType(attrName);
            //获取所有记录，为其建立索引
            RM_FileScan* fileScan = new RM_FileScan();
            fileScan->openScan(&fileHandle, value_type, value_size, offset, CompOp::EQ_OP, NULL);
            map<RID,char*>rid_list;
            fileScan->getAllIndexPairOfFile(rid_list);

            IX_IndexHandle indexHandle;
            this->ixm->OpenIndex(indexName.c_str(),1,indexHandle);
            //插入索引
            map<RID, char*>::iterator it;
            for (it = rid_list.begin(); it != rid_list.end(); ++it) {
                RID rid = it->first;
                printf("insert rid<%d,%d> id %d\t\n",rid.pid,rid.sid,*((int*)(it->second)));
                indexHandle.InsertEntry(it->second,rid);
            }
            indexHandle.close();

            delete fileScan;
            delete fileAttr;
            return RC();
        }

        return RC(-1);
    }
    RC DropIndex   (const char *relName,                // Destroy index
                    const char *attrName){
        //TODO more than drop index file
        remove(attrName);
    }

    //TODO 列出表的模式(schema)信息
    RC ShowSchema(const char *relName){
        if(checkFileExist(relName)){
            RM_FileHandle handle;
            rmm->openFile(relName,handle);
            handle.ShowSchema();
            return RC();
        }
        else {
            printf("table %s doesn't exist\n",relName);
            return RC(-1);
        }
    }
    RC Load        (const char *relName,                // Load utility
                    const char *fileName){

    }
    RC Help        ();                                  // Help for database
    RC Help        (const char *relName);               // Help for relation
    RC Print       (const char *relName);               // Print relation
    RC Set         (const char *paramName,              // Set system parameter
                    const char *value);
};
#endif //DATABASE_SM_MANAGER_H
