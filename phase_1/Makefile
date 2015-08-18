CC = g++ -O2 -Wno-deprecated 

tag = -i

# definition
GTEST_DIR = source/googletest
CPPFLAGS += -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -g -L/opt/gtest/lib -lgtest -lgtest_main -lpthread
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h
USER_DIR = source
TARGET_DIR = bin

ifdef linux
tag = -n
endif
DBFileUnittest:Record.o Comparison.o ComparisonEngine.o Schema.o File.o DBFile.o y.tab.o lex.yy.o DBFileUnittest.o
	$(CC) -o $(TARGET_DIR)/DBFileUnittest Record.o Comparison.o ComparisonEngine.o Schema.o File.o DBFile.o y.tab.o lex.yy.o DBFileUnittest.o -lfl -I $(GTEST_DIR)/include -L $(GTEST_DIR)/lib -lgtest -lpthread -lgtest_main

test: Record.o Comparison.o ComparisonEngine.o Schema.o File.o DBFile.o y.tab.o lex.yy.o test.o
	$(CC) -o $(TARGET_DIR)/test Record.o Comparison.o ComparisonEngine.o Schema.o File.o DBFile.o y.tab.o lex.yy.o test.o -lfl -I $(GTEST_DIR)/include -L $(GTEST_DIR)/lib -lgtest -lpthread -lgtest_main
	
main: Record.o Comparison.o ComparisonEngine.o Schema.o File.o y.tab.o lex.yy.o main.o
	$(CC) -o $(TARGET_DIR)/main Record.o Comparison.o ComparisonEngine.o Schema.o File.o y.tab.o lex.yy.o main.o -lfl


DBFileUnittest.o : $(USER_DIR)/DBFileUnittest.cc $(USER_DIR)/DBFileUnittest.h $(GTEST_HEADERS) 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -g -c $(USER_DIR)/DBFileUnittest.cc

DBFileGUnittest.o : $(USER_DIR)/DBFileGUnittest.cc $(USER_DIR)/DBFileGUnittest.h $(GTEST_HEADERS) 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -g -c $(USER_DIR)/DBFileGUnittest.cc

test.o: $(USER_DIR)/test.cc $(GTEST_HEADERS) 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -g -c $(USER_DIR)/test.cc

main.o: $(USER_DIR)/main.cc
	$(CC) -g -c \
       $(USER_DIR)/main.cc
	
Comparison.o: $(USER_DIR)/Comparison.cc
	$(CC) -g -c \
        $(USER_DIR)/Comparison.cc
	
ComparisonEngine.o: $(USER_DIR)/ComparisonEngine.cc
	$(CC) -g -c $(USER_DIR)/ComparisonEngine.cc
	
DBFile.o: $(USER_DIR)/DBFile.cc
	$(CC) -g -c $(USER_DIR)/DBFile.cc

File.o: $(USER_DIR)/File.cc
	$(CC) -g -c \
        $(USER_DIR)/File.cc

Record.o: $(USER_DIR)/Record.cc
	$(CC) -g -c \
        $(USER_DIR)/Record.cc

Schema.o: $(USER_DIR)/Schema.cc
	$(CC) -g -c \
        $(USER_DIR)/Schema.cc
        
y.tab.o: $(USER_DIR)/Parser.y
	yacc -d $(USER_DIR)/Parser.y 
	sed $(tag) $(USER_DIR)/y.tab.c -e "s/  __attribute__ ((__unused__))$$/# ifndef __cplusplus\n  __attribute__ ((__unused__));\n# endif/" 
	g++ -c $(USER_DIR)/y.tab.c

lex.yy.o: $(USER_DIR)/Lexer.l
	lex  $(USER_DIR)/Lexer.l	 
	gcc  -c		$(USER_DIR)/lex.yy.c

clean: 
	rm -f *.o
	rm -f *.out
	rm -f y.tab.c
	rm -f lex.yy.c
	rm -f y.tab.h
