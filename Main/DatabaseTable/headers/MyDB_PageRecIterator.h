//
// Created by Liu Fang on 2/11/17.
//

#ifndef A2_MYDB_PAGERECITERATOR_H
#define A2_MYDB_PAGERECITERATOR_H


#include <MyDB_PageHandle.h>
#include "MyDB_Table.h"
#include "MyDB_Record.h"
#include "MyDB_RecordIterator.h"
#include "MyDB_PageReaderWriter.h"

//#define HEADER_SIZE (sizeof (MyDB_PageType) + sizeof (size_t))
//#define GET_TYPE(ptr) (*((MyDB_PageType *) ptr))
//#define GET_OFFSET_UNTIL_END(ptr)  (*((size_t *) (((char *) ptr) + sizeof (MyDB_PageType))))

class MyDB_PageRecIterator: public MyDB_RecordIterator{
public:
    void getNext();
    bool hasNext();

    MyDB_PageRecIterator(MyDB_RecordPtr record, MyDB_PageReaderWriter * pgrw);
    ~MyDB_PageRecIterator(){};

private:
    void* cursor;
    void* head;
    MyDB_RecordPtr currentRec;
    MyDB_PageReaderWriter* myPgrw;
};



#endif //A2_MYDB_PAGERECITERATOR_H
