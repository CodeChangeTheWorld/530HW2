
#ifndef TABLE_RW_C
#define TABLE_RW_C

#include <fstream>
#include "MyDB_PageReaderWriter.h"
#include "MyDB_TableReaderWriter.h"
#include "MyDB_TableRecIterator.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>


using namespace std;

MyDB_TableReaderWriter :: MyDB_TableReaderWriter (MyDB_TablePtr toMe, MyDB_BufferManagerPtr bufferManager) {
	me = toMe;
	mybuffer = bufferManager;
}

MyDB_PageReaderWriter &MyDB_TableReaderWriter :: operator [] (size_t id) {
//	static MyDB_PageReaderWriter temp;
//	return temp;
	MyDB_PageHandle page = mybuffer->getPage(me,(long)id);
	pagerw = make_shared<MyDB_PageReaderWriter>(page,mybuffer->getPageSize());
	return *pagerw.get();

}

MyDB_RecordPtr MyDB_TableReaderWriter :: getEmptyRecord () {
	//MyDB_Record (MyDB_SchemaPtr mySchema);
	MyDB_Record nullrecord = MyDB_Record(me->getSchema());
	return make_shared<MyDB_Record>(nullrecord);
}

MyDB_PageReaderWriter &MyDB_TableReaderWriter :: last () {
    return this->operator[](long(me->lastPage()));
}


void MyDB_TableReaderWriter :: append (MyDB_RecordPtr record) {
	MyDB_PageReaderWriter lastpage = last();
	if(!lastpage.append(record)){
		me->setLastPage(me->lastPage()+1);
		MyDB_PageHandle page = mybuffer->getPage(me,(long)me->lastPage());
		MyDB_PageReaderWriter pagerw= MyDB_PageReaderWriter(page,mybuffer->getPageSize());
		pagerw.append(record);
	}
}

void MyDB_TableReaderWriter :: clear(){
    int id = me->lastPage();
    while(id>=0){
        MyDB_PageReaderWriter pagerw = this->operator[]((long)id);
        pagerw.clear();
        id--;
    }
    me->setLastPage(0);
}

void MyDB_TableReaderWriter :: loadFromTextFile (string pth) {

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    this->clear();
    fp = fopen(pth.c_str() , "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    MyDB_RecordPtr record = this-> getEmptyRecord();
    while ((read = getline(&line, &len, fp)) != -1) {
        record->fromString(line);
        this->append(record);
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);


}

long MyDB_TableReaderWriter::getLastPageID() {
    return me->lastPage();
}

MyDB_RecordIteratorPtr MyDB_TableReaderWriter :: getIterator (MyDB_RecordPtr rcdptr) {
	return make_shared<MyDB_TableRecIterator>(rcdptr,make_shared<MyDB_TableReaderWriter>(me, mybuffer));
}

void MyDB_TableReaderWriter :: writeIntoTextFile (string file) {
    std::ofstream outfile;
    outfile.open(file, std::ios::out);
    MyDB_RecordPtr record = this->getEmptyRecord();
    MyDB_RecordIteratorPtr it = getIterator(record);
    while(it->hasNext()){
        it->getNext();
        outfile << record << endl;
    }

}


#endif

