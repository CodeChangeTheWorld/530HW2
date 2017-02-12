
#ifndef PAGE_RW_C
#define PAGE_RW_C

#include <MyDB_PageRecIterator.h>
#include "MyDB_PageReaderWriter.h"
#include "MyDB_TableReaderWriter.h"

void MyDB_PageReaderWriter :: clear () {
    GET_OFFSET_UNTIL_END(head) = HEADER_SIZE;
    cursor = ((char*)head) + GET_OFFSET_UNTIL_END(head);
    pageHandle->wroteBytes();
    std::cout<<(char*)cursor - (char*)head<<endl;
    std::cout<<GET_OFFSET_UNTIL_END(head)<<endl;
    std::cout<<"locB::"<<&head<<endl;
}

MyDB_PageType MyDB_PageReaderWriter :: getType () {
	return MyDB_PageType :: RegularPage;
}

MyDB_RecordIteratorPtr MyDB_PageReaderWriter :: getIterator(MyDB_RecordPtr rec) {
    return make_shared<MyDB_PageRecIterator>(rec, pageHandle);
//    return make_shared<MyDB_PageRecIterator>(rec, this);
}

void MyDB_PageReaderWriter :: setType (MyDB_PageType) {
}

int MyDB_PageReaderWriter::getPageSize(){
    return pageSize;
}
bool MyDB_PageReaderWriter :: append (MyDB_RecordPtr newrec) {
    //std::cout<<GET_OFFSET_UNTIL_END(head)<<endl;
    //std::cout<<newrec->getBinarySize()<<endl;
//    std::cout<<GET_OFFSET_UNTIL_END (head)+newrec->getBinarySize()<<endl;
//    std::cout<<pageSize<<endl;
    if(GET_OFFSET_UNTIL_END (head)+newrec->getBinarySize() > pageSize){
        return false;
    }
    cursor = newrec->toBinary(cursor);
    GET_OFFSET_UNTIL_END (head) = GET_OFFSET_UNTIL_END (head) + newrec->getBinarySize();
    pageHandle->wroteBytes();
	return true;
}
MyDB_PageReaderWriter::MyDB_PageReaderWriter(MyDB_PageHandle pageHandle, size_t pageSize){
	this->pageHandle = pageHandle;
    this->pageSize = pageSize;
    head = pageHandle->getBytes();
    GET_OFFSET_UNTIL_END (head) = HEADER_SIZE;
    cursor = ((char*)head) + GET_OFFSET_UNTIL_END(head);
    //head = ((char*)head) + HEADER_SIZE;
}

#endif
