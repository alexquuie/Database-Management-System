#include "TwoWayList.h"
#include "Record.h"
#include "Schema.h"
#include "File.h"
#include "Comparison.h"
#include "ComparisonEngine.h"
#include "DBFile.h"
#include "Defs.h"
#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


using namespace std;

// stub file .. replace it with your own DBFile.cc

const char* DBFile::META_FILE_PREFIX = ".meta";

DBFile::DBFile () {
	pageEmpty = true;
	currentPageIndex = 0;
	numberOfRecords = 0;
}

DBFile::~DBFile () {
}

int DBFile::GetRecNum(){
	return numberOfRecords;
}

int DBFile::Create (char *f_path, fType f_type, void *startup) {
	//create a meta file and write file type in it
	string meta_file_name;
	meta_file_name.append(f_path);
	meta_file_name.append(META_FILE_PREFIX); 
	ofstream meta_file(meta_file_name.c_str());
	if (!meta_file) {
		cerr << "Not able to create meta file"<<endl;
		return 0;
	}
	meta_file << "HEAP"<<endl;
	meta_file.close();

	//create a dbfile
	currentFile.Open(0, f_path);

	return 1;
}

//TODO: use File::AppendPage in this function after below code works fine
void DBFile::Load (Schema &f_schema, char *loadpath) {
	//open file from loadpath
	FILE *input_file = fopen(loadpath, "r");
	if (!input_file){
		//#ifdef verbose
		cerr << "Not able to open input file " << loadpath << endl;
		//#endif
		exit(1);
	}

	//if empty file then page number starts with 0 else current file length - 1
	off_t page_no = currentFile.GetLength();
	if (page_no != 0) page_no--;

	//if program is in reading mode and there are records in page then empty out the page and set mode to writing mode
	if (!pageEmpty && currentPage.NumRecords() != 0){
		currentPage.EmptyItOut();
	}
	pageEmpty = true;

	Record temp;
	while (temp.SuckNextRecord(&f_schema, input_file)){
		//write current record to page
		int isAppended = currentPage.Append(&temp);

		if (!isAppended){
			//page is full, write page to file on disk
			currentFile.AddPage(&currentPage, page_no++);
			currentPage.EmptyItOut();

			//write current record to page
			currentPage.Append(&temp);
		}
		numberOfRecords++;
	}
	//write last page to file on disk
	currentFile.AddPage(&currentPage, page_no);
	currentPage.EmptyItOut();
	fclose(input_file);
}

int DBFile::Open (char *f_path) {
	//open db file using file.open, pass length as 1
	currentFile.Open(1, f_path);
	
	// read in the second few bits, which is the number of records
		lseek (currentFile.GetMyFilDes(), sizeof (off_t), SEEK_SET);
		read (currentFile.GetMyFilDes(), &numberOfRecords, sizeof (off_t));
		
	return 1;
}

//TODO: use File::AppendPage in this function after below code works fine
void DBFile::MoveFirst () {
	//if there is anything that is not written to file yet, write it
	if (pageEmpty && currentPage.NumRecords()){
		//if empty file then page number starts with 0 else current file length - 1
		off_t page_no = currentFile.GetLength();
		if (page_no != 0) page_no--;

		currentFile.AddPage(&currentPage, page_no);
		currentPage.EmptyItOut();
	}
	pageEmpty = false;

	currentPageIndex = 0;
	currentFile.GetPage(&currentPage, currentPageIndex);
	currentPageIndex++;
}

//TODO: use File::AppendPage in this function after below code works fine
int DBFile::Close () {
	//if there is anything that is not written to file yet, write it
	if (pageEmpty && currentPage.NumRecords() != 0){
		//if empty file then page number starts with 0 else current file length - 1
		off_t page_no = currentFile.GetLength();
		if (page_no != 0) page_no--;

		currentFile.AddPage(&currentPage, page_no);
		currentPage.EmptyItOut();
	}
	//write number of records after number of pages
	lseek (currentFile.GetMyFilDes(), sizeof (off_t), SEEK_SET);
	write (currentFile.GetMyFilDes(), &numberOfRecords, sizeof (off_t));
	//close the file
	int file_len = currentFile.Close();
	return 1;
}

//TODO: use File::AppendPage in this function after below code works fine
void DBFile::Add (Record &rec) {
	if (!pageEmpty && currentPage.NumRecords() != 0){
		currentPage.EmptyItOut();
	}
	pageEmpty = true;

	//write record to page
	Record temp;
	temp.Consume(&rec);
	int isAppended = currentPage.Append(&temp);
	if (!isAppended){
		//if empty file then page number starts with 0 else current file length - 1
		off_t page_no = currentFile.GetLength();
		if (page_no != 0) page_no--;

		//page is full, write page to file on disk
		currentFile.AddPage(&currentPage, page_no);
		currentPage.EmptyItOut();

		//write record to page
		currentPage.Append(&temp);
	}
	numberOfRecords++;
}

int DBFile::GetNext (Record &fetchme) {
	//if there is anything that is not written to file yet, write it
	if (pageEmpty && currentPage.NumRecords() != 0){
		//if empty file then page number starts with 0 else current file length - 1
		off_t page_no = currentFile.GetLength();
		if (page_no != 0) page_no--;

		currentFile.AddPage(&currentPage, page_no);
		currentPage.EmptyItOut();

		//fetch current page from disk for reading
		//currentFile.GetPage(&currentPage, currentPageIndex);
	}
	pageEmpty = false;

	if (!pageEmpty && currentPage.NumRecords() == 0){
		//if reached at the end of current page then fetch next page if current page is not last page
		if (currentPageIndex < currentFile.GetLength()-1){
			currentFile.GetPage(&currentPage, currentPageIndex);
			currentPageIndex++;
			
		}
		else{
			return 0;
		}
	}
	
	return currentPage.GetFirst(&fetchme);
}

int DBFile::GetNext (Record &fetchme, CNF &cnf, Record &literal) {
	ComparisonEngine comp;
	while (GetNext(fetchme)){
		if (comp.Compare(&fetchme, &literal, &cnf)){
			return 1;
		}
	}

	return 0;
}
