
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
    for(long i = 0; i <= me->lastPage(); i++){
        pagerwvec.push_back(MyDB_PageReaderWriter(mybuffer->getPage(me,i), mybuffer->getPageSize()));
    }
}

MyDB_PageReaderWriter &MyDB_TableReaderWriter :: operator [] (size_t id) {
//	static MyDB_PageReaderWriter temp;
//	return temp;
//	MyDB_PageHandle page = mybuffer->getPage(me,(long)id);
//	pagerw = make_shared<MyDB_PageReaderWriter>(page,mybuffer->getPageSize());
//	return *pagerw.get();
    return pagerwvec[id];

}

MyDB_RecordPtr MyDB_TableReaderWriter :: getEmptyRecord () {
	//MyDB_Record (MyDB_SchemaPtr mySchema);
	MyDB_Record nullrecord = MyDB_Record(me->getSchema());
	return make_shared<MyDB_Record>(nullrecord);
}

MyDB_PageReaderWriter &MyDB_TableReaderWriter :: last () {
    std::cout<<me->lastPage()<<endl;
//    return this->operator[](long(me->lastPage()));
    if(me->lastPage() == -1){
        me->setLastPage(0);
        pagerwvec.push_back(MyDB_PageReaderWriter(mybuffer->getPage(me,0), mybuffer->getPageSize()));
    }
    return this->operator[](long(me->lastPage()));
}


void MyDB_TableReaderWriter :: append (MyDB_RecordPtr record) {
	MyDB_PageReaderWriter lastpage = last();
	if(!lastpage.append(record)){
		me->setLastPage(me->lastPage()+1);
        pagerwvec.push_back(MyDB_PageReaderWriter(mybuffer->getPage(me,me->lastPage()), mybuffer->getPageSize()));
		MyDB_PageReaderWriter pagerw= this->operator[](long(me->lastPage()));
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
    me->setLastPage(-1);
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
    string s;
    while ((read = getline(&line, &len, fp)) != -1) {
        s = line;
        s.erase(s.length()-1);
        record->fromString(s);
        this->append(record);
    }

    fclose(fp);
    if (line)
        free(line);


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

