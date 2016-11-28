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
#define DBROOT "../../DatabaseRoot"
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

public:
    SM_Manager  (IndexManager & *ixm, RecordManager &*rmm) {  // Constructor
        //初始化
        fm = new FileManager();
        bpm = new BufPageManager(fm);
        this->ixm = new IndexManager(fm,bpm);
        this->rmm = new RecordManager(fm,bpm);
        ixm = this->ixm;
        rmm = this->rmm;
        //更换工作目录
        int des = chdir(DBROOT);
        if(des<0){
            printf("change working directory failed!\n");
            return;
        }

        char root[100];
        getcwd(root,100);
        DBRootPath = string(root);

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
        vector<string>::iterator it = find(DBlist.begin(), DBlist.end(), string(dbname));
        if(it != DBlist.end()){
            printf("Error: The DataBase %s has already exist.\n",dbname);
            return RC(-1);
        }
        int status = mkdir(dbname,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if(status ==-1){
            printf("ERROR: Create database %s failed\n",dbname);
            return RC(-1);
        }
        int des = chdir(dbname);
        if(des<0){
            printf("change working directory %s failed!\n",dbname);
            return RC(-1);
        }
        ofstream fout(TABLELIST);
        fout<<0<<endl;
        fout.close();
        DBlist.push_back(string(dbname));
        printf("Create database %s succeed\n",dbname);
        return RC(0);
    }
    RC dropDB      (const char *dbname){                //drop database
        char old_path[100];
        if(!dbname)return RC(-1);
        getcwd(old_path,100);
        //切换到数据库根目录
//        int des = chdir(DBRootPath.c_str());
//        if(des==-1){
//            printf("change to DBroot failed when drop database %s",dbname);
//            return RC(-1);
//        }
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
        printf("Drop DataBase: %s succeed.\n",dbname);
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
        int des = chdir(dir.c_str());
        if(des == -1){
            printf("change to DBRoot failed when open database %s",dbName);
            return RC(-1);
        }

        ifstream fin(TABLELIST);
        int table_size;
        fin>>table_size;
        char table_name[100];
        for(int i=0;i<table_size;++i){
            fin>>table_name;
            TableList.push_back(string(table_name));
            //TODO 初始化对表的一些列操作

        }
        fin.close();
        printf("use database %s succeed",dbName);
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
        int des = chdir("..");
    }

    RC CreateTable (const char *relName,                // Create relation
                    int        attrCount,
                    AttrInfo   *attributes){
        vector<string>::iterator it = find(TableList.begin(), TableList.end(), string(relName));
        if(it != TableList.end()){
            printf("Error: The table %s already exists.\n",relName);
            return RC(-1);
        }
        //rmm->createFile(relName,);
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

    }

    RC CreateIndex (const char *relName,                // Create index
                    const char *attrName){
        //TODO 已经创建了索引（索引文件存在）

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
        //TODO drop index file
        remove(attrName);
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
