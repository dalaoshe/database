cmake_minimum_required(VERSION 3.6)
project(database)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    filesystem/bufmanager/BufPageManager.h
    filesystem/bufmanager/FindReplace.h
    filesystem/fileio/FileManager.h
    filesystem/fileio/FileTable.h
    filesystem/indexmanager/b_plus_tree.h
    filesystem/indexmanager/BucketPageManager.h
    filesystem/indexmanager/index_util.h
    filesystem/indexmanager/IndexManager.h
    filesystem/indexmanager/IndexPageManager.h
    filesystem/recordmaneger/PageBitmap.h
    filesystem/recordmaneger/PageManager.h
    filesystem/recordmaneger/Record.h
    filesystem/recordmaneger/RecordManager.h
    filesystem/utils/base.h
    filesystem/utils/compare.h
    filesystem/utils/MyBitMap.h
    filesystem/utils/MyHashMap.h
    filesystem/utils/MyLinkList.h
    filesystem/utils/pagedef.h
    filesystem/utils/rc.h
    filesystem/testfilesystem.cpp filesystem/systemManager/SM_Manager.h filesystem/parse/sql/DropDBStatement.h filesystem/parse/sql/UseDBStatement.h filesystem/parse/sql/ShowDBStatement.h filesystem/parse/sql/ShowTableStatement.h filesystem/parse/sql/DescStatement.h filesystem/parse/sql/CreateIndexStatement.h filesystem/parse/sql/DropIndexStatement.h)

add_executable(database ${SOURCE_FILES})