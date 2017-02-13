//
// Created by Liu Fang on 2/11/17.
//

#ifndef PAGE_ITERATOR
#define PAGE_ITERATOR


//#include <MyDB_PageType.h>
#include "MyDB_PageRecIterator.h"

MyDB_PageRecIterator::MyDB_PageRecIterator(MyDB_RecordPtr record, MyDB_PageReaderWriter * pgrw){
    this->myPgrw = pgrw;
    this->currentRec = record;
    this->cursor = myPgrw->gethead();
    this->head = myPgrw->realhead();
}

void MyDB_PageRecIterator::getNext(){
    if(hasNext()){
        cursor = currentRec->fromBinary(cursor);
    }
}

bool MyDB_PageRecIterator::hasNext(){
    std::cout<<(char*)cursor - (char*)head<<endl;
    std::cout<<myPgrw->getoffset()<<endl;
    std::cout<<"locA::"<<head<<endl;
    if((char*)cursor - (char*)head >= myPgrw->getoffset()) return false;
    return true;
}
#endif