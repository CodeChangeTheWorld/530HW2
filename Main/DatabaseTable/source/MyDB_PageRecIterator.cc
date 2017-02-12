//
// Created by Liu Fang on 2/11/17.
//

#ifndef PAGE_ITERATOR
#define PAGE_ITERATOR


#include "MyDB_PageRecIterator.h"

MyDB_PageRecIterator::MyDB_PageRecIterator(MyDB_RecordPtr record, MyDB_PageHandle handle){
    this->myPageHandle = handle;
    this->currentRec = record;
    this->cursor = handle->getBytes();
}

void MyDB_PageRecIterator::getNext(){
//    if(hasNext()){
        cursor = currentRec->fromBinary(cursor);
//    }
}

bool MyDB_PageRecIterator::hasNext(){
    if(strlen((char *)cursor) <= 0) return false;
    return true;
}
#endif