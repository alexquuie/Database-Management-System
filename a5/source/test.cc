#include <iostream>

#include "Interpreter.h"

using namespace std;

char* catalog_path = "../source/catalog";
char* dbfile_dir = "../dbfile/";
char* tpch_dir = "../data/";

int main (int argc, char* argv[]) {
  Interpreter it;
  it.run();
  return 0;
}
