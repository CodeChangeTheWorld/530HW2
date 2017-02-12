//
// Created by Liu Fang on 2/11/17.
//

#ifndef TABLE_ITERATOR
#define TABLE_ITERATOR

#include "MyDB_TableRecIterator.h"
#include "MyDB_TableReaderWriter.h"
#include "MyDB_PageReaderWriter.h"

MyDB_TableRecIterator::MyDB_TableRecIterator(MyDB_RecordPtr cur, MyDB_TableReaderWriterPtr table){
    currentRecord = cur;
    tableRw = table;
    curPageID = 0;
    pageIt = (table->operator[](curPageID)).getIterator(currentRecord );
}

void MyDB_TableRecIterator::getNext(){
    if(pageIt->hasNext()) pageIt->getNext();
    else{
        curPageID++;
        if(curPageID <= tableRw->getLastPageID()){
            pageIt= (tableRw->operator[](curPageID)).getIterator(currentRecord);
            pageIt->getNext();
        }
    }
}

bool MyDB_TableRecIterator::hasNext(){
//    if( tableRw->operator[](curPageID) == tableRw->last()->)
    if(curPageID == tableRw->getLastPageID() && (!pageIt->hasNext())){
        return  false;
    }
    return true;
}

#endif