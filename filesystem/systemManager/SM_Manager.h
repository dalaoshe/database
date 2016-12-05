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
    SM_Manager  (IndexManager* ixm, RecordManager* rmm) {  // Constructor
        //初始化
        fm = new FileManager();
        bpm = new BufPageManager(fm);
        this->ixm = new IndexManager(fm,bpm);
        this->rmm = new RecordManager(fm,bpm);
        ixm = this->ixm;
        rmm = this->rmm;
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
        rmm->createFile(relName,size,attributes);

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
        if(!checkFileExist(relName)){
            printf("the table %s doesn't exist",relName);
        }

        //search for the size and type accroding to name
        RM_FileHandle fileHandle;
        rmm->openFile(relName,fileHandle);
        int i = 0;
        BufType index = bpm->getPage(fileHandle.getFileID(),0,i);
        int attr_offset = 32>>2;
        int attr_count = index[2] ;
        for(int i=0;i<attr_count;++i){
            int offset = attr_offset*i + ATTR_SIZE;
            if(strcmp(((char*)(index[offset])),attrName)==0){
                AttrType  type = (AttrType)index[offset+1];
                int key_size = index[offset+3];
                ixm->CreateIndex(relName,1,type,key_size);
            }
        }
        printf("Error create index %s ",attrName);
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
