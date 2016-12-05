//
// Created by dalaoshe on 16-10-17.
//
#include "RecordManager.h"
RC RM_FileHandle::getRec(const RID &rid, Record &rec) {
    int index;
    BufType page = bpm->getPage(fileID,rid.pid,index);
    pm->resetPage(page);
    return pm->getRecordCopy(rid,rec);
};

RC RM_FileHandle::insertRec(BufType data, RID &rid){
    int index;
    int pid = this->_findFreePage();
    rid.pid = pid;
    BufType page = bpm->getPage(fileID,pid,index);
    pm->resetPage(page);
    if(pm->insertRecord(data,rid)) {
        bpm->markDirty(index);
        return RC();
    }
    return RC(-1);
};

RC RM_FileHandle::deleteRec(const RID &rid) {
    int index;
    BufType page = bpm->getPage(fileID,rid.pid,index);
    pm->resetPage(page);
    if(pm->deleteRecord(rid.sid)) {
        bpm->markDirty(index);
        return RC();
    }
    return RC(-1);
};

RC RM_FileHandle::updateRec(const Record &rec){
    int index;
    BufType page = bpm->getPage(fileID,rec.getRID().pid,index);
    pm->resetPage(page);
    BufType data = rec.getData();
    RID rid = rec.getRID();
    if(pm->updateRecord(rid.sid,data)) {
        bpm->markDirty(index);
        return RC();
    }
    return RC(-1);
};

RC RM_FileHandle::close() {
    bpm->close();
    delete fm;
    return RC();
}

RC RM_FileHandle::init() {
    this->fileHeader = this->bpm->getPage(fileID,0,this->headIndex);
    bpm->markDirty(this->headIndex);
    return RC();
}

RC RM_FileHandle::getPageNum(int &page_num) {
    page_num = fileHeader[0];
    /*
    pm->resetPage(fileHeader);
    RID rid;
    rid.pid = 0;
    rid.sid = 0;

    page_num = (pm->getRecordCopy(rid)).getHeaderPageNum();
    */
    return RC();
}

RC RM_FileHandle::getSlotNum(int pid, int &slot_num) {
    BufType page = bpm->getPage(fileID,pid,this->headIndex);
    pm->resetPage(page);
    pm->getSlotNum(slot_num);
    return RC();
}


RC RecordManager::createFile(const char* name ,int record_int_size) {
    if(this->fm->createFile(name)) {
        int fileID;
        fm->openFile(name,fileID);
        int index,findex;
        BufType page_header = bpm->allocPage(fileID,0,index);
        BufType page_first = bpm->allocPage(fileID,1,findex);
        //code to edit page_header
        //0 page_num
        //1 slot_size
        page_header[0] = 1;
        page_header[1] = record_int_size;
        //....

        bpm->writeBack(index);
        bpm->writeBack(findex);
        return RC();
    }
    return RC(-1);
}

RC RecordManager::destroyFile(const char* name) {
    if(fm->destroyFile(name)) {
        return RC();
    }
    return RC(-1);
}

RC RecordManager::openFile(const char* name, RM_FileHandle& fileHandle) {
    FileManager *fm = new FileManager();
    int fileID;
    if(fm->openFile(name,fileID)) {
        BufPageManager *bpm = new BufPageManager(fm);
        fileHandle.setBufManager(bpm);
        fileHandle.setFileID(fileID);
        fileHandle.setFileManager(fm);
        fileHandle.init();
        return RC();
    }
    printf("error\n");
    return RC(-1);
}

RC RecordManager::closeFile(RM_FileHandle& fileHandle) {
    fileHandle.close();
    return RC();
}




RC RM_FileScan::openScan(RM_FileHandle *fileHandle, AttrType attrType, int attrLength, int attrOffset,
                         CompOp compOp, void *value, ClientHint pinHint) {
    this->attrType = attrType;
    this->attrLength = attrLength;
    this->attrOffset = attrOffset;
    this->op = compOp;
    this->value = value;
    this->fileHandle = fileHandle;
    //pid=0 为文件头，sid=0 为位图
    pid = 1;
    sid = 1;
    fileHandle->getPageNum(this->page_num);
}

RC RM_FileScan::getNextRec(Record &rec) {
    while(pid < page_num) {
        int sid_num;
        fileHandle->getSlotNum(pid, sid_num);
        while(sid < sid_num) {
            Record r;
            RID rid;
            rid.pid = pid;
            rid.sid = sid;
            fileHandle->getRec(rid, r);
            sid ++;
            if(checkoutRecord(r)) {
                rec.setRID(rid);
                rec.setData(r.getData());
                return RC();
            }
        }
        sid = 1;
        pid ++;
    }
    return RC(-1);
}

bool RM_FileScan::checkRecord(Record &rec) const {
    void* target_v = this->value;
    void* rec_v = rec.getData(this->attrOffset);
    switch (attrType) {
        case FLOAT: {
            target_v = (float*)target_v;
            rec_v = (float*)rec_v;
            break;
        }

        case INT : {
            target_v = (int*)target_v;
            rec_v = (int*)rec_v;
            break;
        }

        case STRING: {
            target_v = (char*)target_v;
            rec_v = (char*)rec_v;
            break;
        }

        default: {
            return false;
        }
    }
    switch (op) {
        case EQ_OP: {
            return (*rec_v) == (*target_v);
        }
        case LT_OP: {
            return (*rec_v) < (*target_v);
        }
        case GT_OP: {
            return (*rec_v) > (*target_v);
        }
        case LE_OP: {
            return (*rec_v) <= (*target_v);
        }
        case GE_OP: {
            return (*rec_v) >= (*target_v);
        }
        case NE_OP: {
            return (*rec_v) < (*target_v) || (*rec_v) > (*target_v);;
        }
        case NO_OP: {
            return target_v == NULL;
        }
    }
}

RC RM_FileScan::closeScan() {

}