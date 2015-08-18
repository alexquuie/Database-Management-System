CC = g++ -std=c++11 -w -Wno-deprecated 

tag = -i

GOOGLETESTDIR = ./source/googletest
src = ./source
bin = ./bin

ifdef linux
tag = -n
endif

test: Record.o Comparison.o ComparisonEngine.o Schema.o File.o BigQ.o DBFile.o GenericDBFile.o HeapDBFile.o SortedDBFile.o Pipe.o RelOp.o Function.o  Statistics.o QueryPlan.o Ddl.o Interpreter.o y.tab.o yyfunc.tab.o lex.yy.o lex.yyfunc.o test.o
	$(CC) -o $(bin)/test $(bin)/Record.o $(bin)/Comparison.o $(bin)/ComparisonEngine.o $(bin)/Schema.o $(bin)/File.o $(bin)/BigQ.o $(bin)/DBFile.o $(bin)/GenericDBFile.o $(bin)/HeapDBFile.o $(bin)/SortedDBFile.o $(bin)/Pipe.o $(bin)/RelOp.o $(bin)/Function.o  $(bin)/Statistics.o $(bin)/QueryPlan.o $(bin)/Ddl.o $(bin)/Interpreter.o $(bin)/y.tab.o $(bin)/yyfunc.tab.o $(bin)/lex.yy.o $(bin)/lex.yyfunc.o $(bin)/test.o -lfl -lpthread

test.o: $(src)/test.cc
	$(CC) -o $(bin)/test.o -g -c $(src)/test.cc

Interpreter.o: $(src)/Interpreter.cc
	$(CC) -o $(bin)/Interpreter.o -g -c $(src)/Interpreter.cc

Ddl.o: $(src)/Ddl.cc
	$(CC) -o $(bin)/Ddl.o -g -c $(src)/Ddl.cc

QueryPlan.o: $(src)/QueryPlan.cc
	$(CC) -o $(bin)/QueryPlan.o -g -c $(src)/QueryPlan.cc

Statistics.o: $(src)/Statistics.cc
	$(CC) -o $(bin)/Statistics.o -g -c $(src)/Statistics.cc
	
Comparison.o: $(src)/Comparison.cc
	$(CC) -o $(bin)/Comparison.o -g -c $(src)/Comparison.cc
	
ComparisonEngine.o: $(src)/ComparisonEngine.cc
	$(CC) -o $(bin)/ComparisonEngine.o -g -c $(src)/ComparisonEngine.cc

Pipe.o: $(src)/Pipe.cc
	$(CC) -o $(bin)/Pipe.o -g -c $(src)/Pipe.cc

BigQ.o: $(src)/BigQ.cc
	$(CC) -o $(bin)/BigQ.o -g -c -std=gnu++11 $(src)/BigQ.cc

SortedDBFile.o: $(src)/SortedDBFile.cc
	$(CC) -o $(bin)/SortedDBFile.o -g -c $(src)/SortedDBFile.cc

HeapDBFile.o: $(src)/HeapDBFile.cc
	$(CC) -o $(bin)/HeapDBFile.o -g -c $(src)/HeapDBFile.cc

GenericDBFile.o: $(src)/GenericDBFile.cc
	$(CC) -o $(bin)/GenericDBFile.o -g -c $(src)/GenericDBFile.cc

DBFile.o: $(src)/DBFile.cc
	$(CC) -o $(bin)/DBFile.o -g -c $(src)/DBFile.cc

RelOp.o: $(src)/RelOp.cc
	$(CC) -o $(bin)/RelOp.o -g -c $(src)/RelOp.cc

Function.o: $(src)/Function.cc
	$(CC) -o $(bin)/Function.o -g -c $(src)/Function.cc

File.o: $(src)/File.cc
	$(CC) -o $(bin)/File.o -g -c $(src)/File.cc

Record.o: $(src)/Record.cc
	$(CC) -o $(bin)/Record.o -g -c $(src)/Record.cc

Schema.o: $(src)/Schema.cc
	$(CC) -o $(bin)/Schema.o -g -c $(src)/Schema.cc
	
y.tab.o: $(src)/Parser.y
	yacc -d $(src)/Parser.y
	g++ -w -o $(bin)/y.tab.o -c $(src)/y.tab.c

yyfunc.tab.o: $(src)/ParserFunc.y
	yacc -p "yyfunc" -b "yyfunc" -d $(src)/ParserFunc.y
	g++ -w -o $(bin)/yyfunc.tab.o -c $(src)/yyfunc.tab.c

lex.yy.o: $(src)/Lexer.l
	flex  $(src)/Lexer.l
	gcc -w -o $(bin)/lex.yy.o -c $(src)/lex.yy.c

lex.yyfunc.o: $(src)/LexerFunc.l
	flex -Pyyfunc $(src)/LexerFunc.l
	gcc  -w -o $(bin)/lex.yyfunc.o -c $(src)/lex.yyfunc.c

clean:
	rm -f $(bin)/*.exe 
	rm -f $(bin)/*.o
	rm -f $(bin)/*.out
	rm -f $(bin)/y.tab.*
	rm -f $(bin)/lex.yy.*
	rm -f y.tab.c
	rm -f lex.yy.c
	rm -f y.tab.h
	rm -f yyfunc.tab.c
	rm -f yyfunc.tab.h
	rm -f lex.yyfunc.c
