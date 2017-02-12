//
// Created by Liu Fang on 2/11/17.
//

#ifndef A2_MYDB_PAGERECITERATOR_H
#define A2_MYDB_PAGERECITERATOR_H


#include <MyDB_PageHandle.h>
#include "MyDB_Table.h"
#include "MyDB_Record.h"
#include "MyDB_RecordIterator.h"

class MyDB_PageRecIterator: public MyDB_RecordIterator{
public:
    void getNext();
    bool hasNext();

    MyDB_PageRecIterator(MyDB_RecordPtr record, MyDB_PageHandle pageHandle);
    ~MyDB_PageRecIterator(){};

private:
    void* cursor;
    MyDB_RecordPtr currentRec;
    MyDB_PageHandle myPageHandle;
};



#endif //A2_MYDB_PAGERECITERATOR_H
