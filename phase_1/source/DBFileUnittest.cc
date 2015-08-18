#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<gtest/gtest.h>
#include "DBFileUnittest.h"
#include "DBFile.h"
#include "Record.h"
#include "test.h"
//#include "gtest/gtest_prod.h"

using namespace std;

char *dbfile_dir = "../tmp/"; // dir where binary heap files should be stored
char *tpch_dir ="/cise/tmp/dbi_sp11/DATA/1G/"; // dir where dbgen tpch files (extension *.tbl) can be found
char *catalog_path = "../source/catalog"; // relative path of the catalog file
/*
 1. nation 
 2. region
 3. customer
 4. part
 5. partsupp
 6. orders
 7. lineitem
*/

//DBFileUnitTest::load
TEST(DBFileUnitTest,LoadTest){	
	setup (catalog_path, dbfile_dir, tpch_dir);
	relation *rel_ptr[] = {n, r, c, p, ps, o, li};
    	relation *rel;
              
	DBFile *dbfile;
	cout<<green<<"======================================" <<endl;
	cout << green << "            Total Load TestCase : " <<7<<endl;
	for (int i=1;i<=7;i++){	
		cout<<green<<"======================================" <<endl;
		cout<<green<<"           Begin of LoadTest Case"<<i<<endl;	
		dbfile= new DBFile();
		rel = rel_ptr [i - 1];		
		//Examine the private members
		EXPECT_EQ(0, dbfile->currentPageIndex);
		EXPECT_EQ(1, dbfile->pageEmpty);
		EXPECT_EQ(0, dbfile->numberOfRecords);

		dbfile->Create (rel->path(), heap, NULL);
		char *tbl_path=(char*)malloc(100*sizeof(char)); 
		// construct path of the tpch flat text file
		sprintf (tbl_path, "%s%s.tbl", tpch_dir, rel->name()); 
		
		dbfile->Load (*(rel->schema ()), tbl_path);
		EXPECT_EQ(0, dbfile->currentPageIndex);
		EXPECT_EQ(1, dbfile->pageEmpty);
		EXPECT_NE(0, dbfile->numberOfRecords);
		EXPECT_EQ(1, dbfile->Close ());		
		delete dbfile;
		cout<<green<<"              End of LoadTest Case"<<i<<endl;
	}	
	cleanup ();
}
//DBFileUnitTest::scan
TEST(DBFileUnitTest,ScanTest){	
	setup (catalog_path, dbfile_dir, tpch_dir);
	relation *rel_ptr[] = {n, r, c, p, ps, o, li};
    	relation *rel;
              
	DBFile *dbfile;
	cout<<green<<"======================================" <<endl;
	cout << green << "           Total Scan TestCase : " <<7<<endl;
	int noofrecords[7]={25,5,150000,200000,800000,1500000,6001215};
	for (int i=1;i<=7;i++){	
		cout<<green<<"======================================" <<endl;
		cout<<green<<"           Begin of Scan Test Case"<<i<<endl;	
		dbfile= new DBFile();
		rel = rel_ptr [i - 1];		
		//Examine the private members
		EXPECT_EQ(0, dbfile->currentPageIndex);
		EXPECT_EQ(1, dbfile->pageEmpty);
		EXPECT_EQ(0, dbfile->numberOfRecords);
		dbfile->Open (rel->path());
		
		dbfile->MoveFirst ();
		Record temp;
		int counter = 0;
		while (dbfile->GetNext (temp) == 1)counter += 1;
		EXPECT_NE(0, dbfile->currentPageIndex);
		EXPECT_EQ(0, dbfile->pageEmpty);
		EXPECT_EQ(noofrecords[i-1],dbfile->numberOfRecords);
		EXPECT_EQ(noofrecords[i-1], counter);	
		EXPECT_EQ(1, dbfile->Close ());		
		delete dbfile;
		cout<<green<<"              End of Scan Test Case"<<i<<endl;
	}	
	cleanup ();
}
//Don't know how to test it automatically
//DBFileUnitTest::scan&Filter
TEST(DBFileUnitTest,ScanAndFilterTest){	
	setup (catalog_path, dbfile_dir, tpch_dir);
	relation *rel_ptr[] = {n, r, c, p, ps, o, li};
    	relation *rel;
              
	DBFile *dbfile;
	cout<<green<<"======================================" <<endl;
	cout << green << "           Total ScanAndFilter TestCase : " <<7<<endl;
	int noofrecords[7]={25,5,150000,200000,800000,1500000,6001215};
	for (int i=1;i<=7;i++){	
		cout<<green<<"======================================" <<endl;
		cout<<green<<"           Begin of ScanAndFilter Test Case"<<i<<endl;
		rel = rel_ptr [i - 1];			
		CNF cnf; 
		Record literal;
		rel->get_cnf (cnf, literal);

		dbfile= new DBFile();

		dbfile->Open (rel->path());
		EXPECT_EQ(0, dbfile->currentPageIndex);
		EXPECT_EQ(1, dbfile->pageEmpty);
		EXPECT_EQ(0, dbfile->numberOfRecords);

		dbfile->MoveFirst ();
		EXPECT_EQ(1, dbfile->currentPageIndex);
		EXPECT_EQ(1, dbfile->pageEmpty);
		EXPECT_EQ(0, dbfile->numberOfRecords);
		Record temp;

		int counter = 0;
		while (dbfile->GetNext (temp, cnf, literal) == 1) {
			counter += 1;
			temp.Print(rel->schema());
		}
		EXPECT_EQ(0, dbfile->currentPageIndex);
		EXPECT_EQ(0, dbfile->pageEmpty);
		EXPECT_EQ(0, dbfile->numberOfRecords);
		//EXPECT_EQ(noofrecords[i-1], counter);
		cout <<green<<"          selected " << counter << " recs \n";
		EXPECT_EQ(1, dbfile->Close ());		
		delete dbfile;
		cout<<green<<"           End of ScanAndFilter Test Case"<<i<<endl;
	}	
	cleanup ();
}
int main (int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
