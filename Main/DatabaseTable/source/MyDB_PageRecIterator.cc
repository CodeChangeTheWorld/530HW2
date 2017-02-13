//
// Created by Liu Fang on 2/11/17.
//

#ifndef PAGE_ITERATOR
#define PAGE_ITERATOR


#include "MyDB_PageRecIterator.h"

MyDB_PageRecIterator::MyDB_PageRecIterator(MyDB_RecordPtr record, MyDB_PageReaderWriter * pgrw){
    this->pgrw = pgrw;
    this->currentRec = record;
    this->cursor = pgrw->getbegin();
    this->head = pgrw->gethead();
}

void MyDB_PageRecIterator::getNext(){
//    if(hasNext()){
        cursor = currentRec->fromBinary(cursor);
//    }
}

bool MyDB_PageRecIterator::hasNext(){
//    void * head = pgrw->gethead();
//    std::cout<<(char*)cursor - (char*)head<<endl;
//    std::cout<<GET_OFFSET_UNTIL_END(head)<<endl;
//    std::cout<<"locA::"<<&head<<endl;
    if((char*)cursor - (char*)head >= pgrw->offset()) return false;
    return true;
}
#endif