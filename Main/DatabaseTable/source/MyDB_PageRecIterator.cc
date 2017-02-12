//
// Created by Liu Fang on 2/11/17.
//

#ifndef PAGE_ITERATOR
#define PAGE_ITERATOR


#include <MyDB_PageType.h>
#include "MyDB_PageRecIterator.h"

MyDB_PageRecIterator::MyDB_PageRecIterator(MyDB_RecordPtr record, MyDB_PageHandle handle){
    this->myPageHandle = handle;
    this->currentRec = record;
    void * head = handle->getBytes();
    this->cursor = ((char*)head) + HEADER_SIZE;
}

void MyDB_PageRecIterator::getNext(){
    if(hasNext()){
        cursor = currentRec->fromBinary(cursor);
    }
}

bool MyDB_PageRecIterator::hasNext(){
    void * head = myPageHandle->getBytes();
    std::cout<<(char*)cursor - (char*)head<<endl;
    std::cout<<GET_OFFSET_UNTIL_END(head)<<endl;
    std::cout<<"locA::"<<&head<<endl;
    if((char*)cursor - (char*)head >= GET_OFFSET_UNTIL_END(head)) return false;
    return true;
}
#endif