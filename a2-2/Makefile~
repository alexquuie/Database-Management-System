CC = g++ -O2 -w -Wno-deprecated 

tag = -i

GOOGLETESTDIR = ./source/googletest
src = ./source
bin = ./bin

ifdef linux
tag = -n
endif

test1: Record.o Comparison.o ComparisonEngine.o Schema.o File.o BigQ.o DBFile.o Sorted.o Heap.o Pipe.o y.tab.o lex.yy.o test1.o
	$(CC) -o $(bin)/test1 $(bin)/Record.o $(bin)/Comparison.o $(bin)/ComparisonEngine.o $(bin)/Schema.o $(bin)/File.o $(bin)/BigQ.o $(bin)/DBFile.o $(bin)/Sorted.o $(bin)/Heap.o $(bin)/Pipe.o $(bin)/y.tab.o $(bin)/lex.yy.o $(bin)/test1.o -lfl -lpthread

test2: Record.o Comparison.o ComparisonEngine.o Schema.o File.o BigQ.o DBFile.o Sorted.o Heap.o Pipe.o y.tab.o lex.yy.o test2.o
	$(CC) -o $(bin)/test2 $(bin)/Record.o $(bin)/Comparison.o $(bin)/ComparisonEngine.o $(bin)/Schema.o $(bin)/File.o $(bin)/BigQ.o $(bin)/DBFile.o $(bin)/Sorted.o $(bin)/Heap.o $(bin)/Pipe.o $(bin)/y.tab.o $(bin)/lex.yy.o $(bin)/test2.o -lfl -lpthread

googletest: Record.o Comparison.o ComparisonEngine.o Schema.o File.o BigQ.o DBFile.o Sorted.o Heap.o Pipe.o y.tab.o lex.yy.o googletest.o
	$(CC) -o $(bin)/googletest $(bin)/Record.o $(bin)/Comparison.o $(bin)/ComparisonEngine.o $(bin)/Schema.o $(bin)/File.o $(bin)/BigQ.o $(bin)/DBFile.o $(bin)/Sorted.o $(bin)/Heap.o $(bin)/Pipe.o $(bin)/y.tab.o $(bin)/lex.yy.o $(bin)/googletest.o -I$(GOOGLETESTDIR)/include -L$(GOOGLETESTDIR)/lib -lgtest -lpthread

main: Record.o Comparison.o ComparisonEngine.o Schema.o File.o y.tab.o lex.yy.o main.o
	$(CC) -o $(bin)/main $(bin)/Record.o $(bin)/Comparison.o $(bin)/ComparisonEngine.o $(bin)/Schema.o $(bin)/File.o $(bin)/y.tab.o $(bin)/lex.yy.o $(bin)/main.o -lfl

googletest.o: $(src)/googletest.cc
	$(CC) -o $(bin)/googletest.o -g -c -std=gnu++11 -I$(GOOGLETESTDIR)/include -L$(GOOGLETESTDIR)/lib -lgtest -lpthread $(src)/googletest.cc

test1.o: $(src)/test1.cc
	$(CC) -o $(bin)/test1.o -g -c $(src)/test1.cc

test2.o: $(src)/test2.cc
	$(CC) -o $(bin)/test2.o -g -c $(src)/test2.cc

main.o: $(src)/main.cc
	$(CC) -o $(bin)/main.o -g -c $(src)/main.cc
	
Comparison.o: $(src)/Comparison.cc
	$(CC) -o $(bin)/Comparison.o -g -c $(src)/Comparison.cc
	
ComparisonEngine.o: $(src)/ComparisonEngine.cc
	$(CC) -o $(bin)/ComparisonEngine.o -g -c $(src)/ComparisonEngine.cc

Pipe.o: $(src)/Pipe.cc
	$(CC) -o $(bin)/Pipe.o -g -c $(src)/Pipe.cc

BigQ.o: $(src)/BigQ.cc
	$(CC) -o $(bin)/BigQ.o -g -c -std=gnu++11 $(src)/BigQ.cc

Sorted.o: $(src)/Sorted.cc
	$(CC) -o $(bin)/Sorted.o -g -c $(src)/Sorted.cc

Heap.o: $(src)/Heap.cc
	$(CC) -o $(bin)/Heap.o -g -c $(src)/Heap.cc

DBFile.o: $(src)/DBFile.cc
	$(CC) -o $(bin)/DBFile.o -g -c $(src)/DBFile.cc

File.o: $(src)/File.cc
	$(CC) -o $(bin)/File.o -g -c $(src)/File.cc

Record.o: $(src)/Record.cc
	$(CC) -o $(bin)/Record.o -g -c $(src)/Record.cc

Schema.o: $(src)/Schema.cc
	$(CC) -o $(bin)/Schema.o -g -c $(src)/Schema.cc
	
y.tab.o: $(src)/Parser.y
	yacc -b $(src)/y -d $(src)/Parser.y
	sed $(tag) $(src)/y.tab.c -e "s/  __attribute__ ((__unused__))$$/# ifndef __cplusplus\n  __attribute__ ((__unused__));\n# endif/" 
	g++ -w -o $(bin)/y.tab.o -c $(src)/y.tab.c

lex.yy.o: $(src)/Lexer.l
	flex  -o $(src)/lex.yy.c $(src)/Lexer.l
	gcc -w -o $(bin)/lex.yy.o -c $(src)/lex.yy.c

clean:
	rm -f $(bin)/*.exe 
	rm -f $(bin)/*.o
	rm -f $(bin)/*.out
	rm -f $(src)/y.tab.c
	rm -f $(src)/lex.yy.c
	rm -f $(src)/y.tab.h
