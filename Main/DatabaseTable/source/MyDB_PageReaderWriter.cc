
#ifndef PAGE_RW_C
#define PAGE_RW_C

#include <MyDB_PageRecIterator.h>
#include "MyDB_PageReaderWriter.h"
#include "MyDB_TableReaderWriter.h"

void MyDB_PageReaderWriter :: clear () {
    cursor=head;
}

MyDB_PageType MyDB_PageReaderWriter :: getType () {
	return MyDB_PageType :: RegularPage;
}

MyDB_RecordIteratorPtr MyDB_PageReaderWriter :: getIterator(MyDB_RecordPtr rec) {
    return make_shared<MyDB_PageRecIterator>(rec, pageHandle);
}

void MyDB_PageReaderWriter :: setType (MyDB_PageType) {
}

int MyDB_PageReaderWriter::getPageSize(){
    return pageSize;
}
bool MyDB_PageReaderWriter :: append (MyDB_RecordPtr newrec) {
    pageHandle->wroteBytes();
    if(pageSize-((char*)cursor-(char*)head) < newrec->getBinarySize()){
        return false;
    }
    cursor = newrec->toBinary(cursor);
	return true;
}
MyDB_PageReaderWriter::MyDB_PageReaderWriter(MyDB_PageHandle pageHandle, size_t pageSize){
	this->pageHandle = pageHandle;
    this->pageSize = pageSize;
    head = pageHandle->getBytes();
//    cursor = ((char*)head)+(*((size_t *) ((char *) head)));
//    std::cout<<(char*)cursor-(char*)head<<endl;
//    cursor = head;
    GET_OFFSET_UNTIL_END (head) = HEADER_SIZE;
}

#endif
