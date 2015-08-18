GTEST_ROOT="/gtest"
cmake_minimum_required(VERSION 2.6)
project(testSample)
find_package (Threads)
message(STATUS GTEST_ROOT=$ENV{GTEST_ROOT})
include_directories($ENV{GTEST_ROOT}/include $ENV{GTEST_ROOT}/)
link_directories($ENV{GTEST_ROOT}/src)
add_executable(testSample testSample.cc testSample_unittest.cc Record.o Comparison.o ComparisonEngine.o Schema.o File.o DBFile.o y.tab.o lex.yy.o test.o)
target_link_libraries(testSample gtest gtest_main)
target_link_libraries(testSample ${CMAKE_THREAD_LIBS_INIT})
add_test(NAME testSample COMMAND testSample)

