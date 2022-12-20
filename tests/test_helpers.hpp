#ifndef TEST_H__
#define TEST_H__
#include <string>
#include <iostream>
#include <fstream>
#include <array>
#include "../code_1/hash.hpp"
#include "../code_1/miniGit.hpp"

using namespace std;

// TODO add detailed explanation on what the function should do
std::string exec(const char* cmd);
std::string readFileIntoString(std::string fileName);
string test_insert(string arr[], int len, int tabSize);
string test_add(string localfile[], int len, int cases);
string test_rm(string filename);
string test_commit(int cases);
string test_searchHash(string word);
string test_checkOut(string commitNum);
string test_DiffandStatus(string filename);

#endif // TEST_H__
