#pragma once

#include<iostream>
#include<vector>
#include "hash.hpp"

using namespace std;


enum GITOP {init, add, rm, commit, checkout, status};

struct FileNode {
    string name;
    int version;
    FileNode* next;
};

struct BranchNode {
    int commitID;
    string commitMessage;
    BranchNode* next;
    BranchNode* previous;
    FileNode* fileHead;   
};

//*** You can add helper functions if you desire ***//
class MiniGit {
private:    
    BranchNode* commitHead;
    int commits;
    HashTable* ht;
    
   

public:
    MiniGit();
    ~MiniGit();

    void init(int hashtablesize);
    void add(string fileName);
    void rm(string fileName);
    void search(string key);
    string commit(string msg, HashTable ht);
    void checkout(string commitID);
    void printSearchTable();
    BranchNode* DLLinsert(string msg);
    void writefile(string add, string filename);
    void printList();
    void printdirectory(string path_minigit);
    void DiffAndStatus(string filename);
    void delete_line(const char *file_name, string delete_line);
    bool searchFile(string fileName);
};
