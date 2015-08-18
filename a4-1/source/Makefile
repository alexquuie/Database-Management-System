CC = g++ -O2 -w -Wno-deprecated

tag = -i

GOOGLETESTDIR = /home/yogesh/gtest
src = .
bin = .

ifdef linux
tag = -n
endif

googletest: Record.o Comparison.o ComparisonEngine.o Schema.o File.o   Pipe.o y.tab.o lex.yy.o googletest.o
	$(CC) -o googletest Record.o Comparison.o ComparisonEngine.o Schema.o File.o  Pipe.o y.tab.o lex.yy.o googletest.o -I$(GOOGLETESTDIR)/include -L$(GOOGLETESTDIR)/lib -lgtest -lpthread

test: Record.o Comparison.o ComparisonEngine.o Schema.o File.o Statistics.o Pipe.o Function.o y.tab.o yyfunc.tab.o lex.yy.o lex.yyfunc.o test.o
	$(CC) -o test Record.o Comparison.o ComparisonEngine.o Schema.o File.o Statistics.o Pipe.o Function.o y.tab.o yyfunc.tab.o lex.yy.o lex.yyfunc.o test.o -lfl -lpthread

googletest.o: googletest.cc
	$(CC) -o googletest.o -g -c -std=gnu++11 -I$(GOOGLETESTDIR)/include -L$(GOOGLETESTDIR)/lib -lgtest -lpthread googletest.cc

test.o: test.cc
	$(CC) -o test.o -g -c test.cc

Statistics.o: Statistics.cc
	$(CC) -o Statistics.o -g -c Statistics.cc
	
Comparison.o: Comparison.cc
	$(CC) -o Comparison.o -g -c Comparison.cc
	
ComparisonEngine.o: ComparisonEngine.cc
	$(CC) -o ComparisonEngine.o -g -c ComparisonEngine.cc

Pipe.o: Pipe.cc
	$(CC) -o Pipe.o -g -c Pipe.cc



Function.o: Function.cc
	$(CC) -o Function.o -g -c Function.cc

File.o: File.cc
	$(CC) -o File.o -g -c File.cc

Record.o: Record.cc
	$(CC) -o Record.o -g -c Record.cc

Schema.o: Schema.cc
	$(CC) -o Schema.o -g -c Schema.cc
	
y.tab.o: Parser.y
	yacc -d Parser.y
	g++ -c y.tab.c

yyfunc.tab.o: ParserFunc.y
	yacc -p "yyfunc" -b "yyfunc" -d ParserFunc.y
	g++ -c yyfunc.tab.c

lex.yy.o: Lexer.l
	flex  Lexer.l
	gcc  -c lex.yy.c

lex.yyfunc.o: LexerFunc.l
	flex -Pyyfunc LexerFunc.l
	gcc  -c lex.yyfunc.c

clean:
	rm -f *.exe 
	rm -f *.o
	rm -f *.out
	rm -f y.tab.*
	rm -f yyfunc.tab.*
	rm -f lex.yy.*
	rm -f lex.yyfunc*