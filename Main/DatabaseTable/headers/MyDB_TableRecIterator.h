//
// Created by Liu Fang on 2/11/17.
//

#ifndef A2_MYDB_TABLERECITERATOR_H
#define A2_MYDB_TABLERECITERATOR_H

#include "MyDB_TableReaderWriter.h"
#include "MyDB_PageRecIterator.h"

class MyDB_TableRecIterator: public MyDB_RecordIterator{
public:
    void getNext();
    bool hasNext();

    MyDB_TableRecIterator(MyDB_RecordPtr,MyDB_TableReaderWriterPtr);
    ~MyDB_TableRecIterator(){};

private:
    MyDB_RecordPtr currentRecord;
    MyDB_TableReaderWriterPtr tableRw;
    MyDB_RecordIteratorPtr pageIt;
    int curPageID;
};

#endif //A2_MYDB_TABLERECITERATOR_H
