#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include <filesystem>
namespace fs = std::filesystem;
#include <unistd.h>
#include "miniGit.hpp"
#include <vector>

MiniGit::MiniGit() {
    // system("pwd");
    // system("ls -la");
    fs::remove_all("minigit");
    fs::create_directory("minigit");
    // sleep(3);
    // system("mkdir minigit");
    //fs::directory_iterator("minigit");

}

MiniGit::~MiniGit() {   
    // Any postprocessing that may be required
    //fs::remove_all("minigit");
}


void MiniGit::init(int hashtablesize) {
    
    // A doubly linked list created with a single head node
    commitHead = new BranchNode;
    commitHead->commitMessage = "";
    commitHead->commitID = 0; //unique commit number
    commitHead->fileHead = nullptr;
    commitHead->next = nullptr;
    commitHead->previous = nullptr;
    
}

void MiniGit::add(string fileName) {
    
    BranchNode *branch = commitHead;
    while(branch->next!= NULL){
    
        branch = branch->next;
    }
    FileNode* head = branch->fileHead;

    string versionNumber = "_0";
    string str1 = fileName.substr(0,2);
    string str2 = fileName.substr(2,5);
    string str3 = str1 + versionNumber + str2;
    

    if(head == NULL){
     
        commitHead->fileHead = new FileNode;
        commitHead->fileHead->name = str3 ;
        commitHead->fileHead->version = 0;
        commitHead->fileHead->next = NULL;
    }

    else{
        
        FileNode* newNode = new FileNode;
        newNode->name = str3;
        newNode->version = 0;
        newNode->next = NULL;
        FileNode* temp = head;
        while(temp->next != NULL){
            temp = temp->next;
        }
       
       temp->next = newNode;

    }
    
    
}

void MiniGit::rm(string fileName) {
    
    BranchNode* br = commitHead;
    FileNode* pres;
    FileNode* prev;

    while(br){

        if(br->fileHead == NULL){
            cout<< "SLL List is already empty"<<endl;
        }
        else{
            if (fileName == br->fileHead->name) {
                FileNode* temp = br->fileHead->next;
                delete br->fileHead;
                br->fileHead = temp;
        
            }
            pres = br->fileHead;
            prev = NULL;
            while(pres != NULL && pres->name != fileName){
                prev = pres;
                pres = pres->next;
             }

            if(pres != NULL){
                prev->next = pres->next;
                delete pres;
                pres = nullptr;
            }
          
        }
        br = br->next;
    }

}



void MiniGit::printSearchTable()
{
     ht->printTable();
}



void MiniGit::search(string key)
{
    
     BranchNode* br = new BranchNode;
    while (br){
        if (br->commitMessage.find(key) != std::string::npos) {
            cout << "found!" << '\n';
        }
        br = br->next;

    }  
}


bool MiniGit::searchFile(string fileName){

    string versionNumber = "_0";
    string str1 = fileName.substr(0,2);
    string str2 = fileName.substr(2,5);
    string str3 = str1 + versionNumber + str2;

    BranchNode* br = commitHead;
    FileNode* file;
    while(br){
        file = br->fileHead;
        while(file){
            if (file->name == str3){
                return true;
            }
            file = file->next;
        }
        br = br->next;

    }
}
        
  

BranchNode* MiniGit::DLLinsert(string msg){


     //new DLL node create
    BranchNode* newNode = new BranchNode;
      
    newNode->commitMessage="";
    newNode->fileHead = NULL;
    newNode->next = NULL;
    
    BranchNode* temp = commitHead;
        
    while(temp->next != NULL){        
        temp = temp->next;
    }
       
    temp->next = newNode;
    newNode->previous = temp;
    newNode->commitID = newNode->previous->commitID + 1;


    //copying SLL files to new DLL node
    
    BranchNode* first = commitHead;
    FileNode* tail = NULL;
    
    while(commitHead->next != NULL){
        commitHead = commitHead->next;
    }
    
    commitHead->previous->commitMessage = msg;
   
    FileNode* file1 = commitHead->previous->fileHead;

    
    while(file1!= NULL){
        
        if(commitHead->fileHead == NULL){
            commitHead->fileHead = new FileNode;
            commitHead->fileHead->name = file1->name;
            
            commitHead->fileHead->version = file1->version;
            
            commitHead->fileHead->next = NULL;
            tail = commitHead->fileHead;        
        }

        else{
            tail->next = new FileNode;
            tail = tail->next;
            tail->name = file1->name;
            tail->version = file1->version;
            tail->next = NULL;        
           
        }
        file1 = file1->next;
    }
    commitHead = first;
    return newNode;
}

string readFileIntoString(const string& path) {
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    return string((istreambuf_iterator<char>(input_file)), istreambuf_iterator<char>());
}



void fileCopy(string fileName, string outputName, string direction){

    string line;

    // For writing text file
    // Creating ofstream & ifstream class object
    if(direction == "LtoB"){
        fileName = "files/" + fileName;
        outputName = "minigit/" + outputName;
    }
    else{
        fileName = "minigit/" + fileName;
        outputName = "files/" + outputName;
    }

    ifstream ini_file;
    ini_file.open(fileName);
     // This is the original file
    ofstream out_file{ outputName };
    if (ini_file && out_file) {
  
        while (getline(ini_file, line)) {
            out_file << line <<"\n";
        }
       
    }
    
    // Closing file
    ini_file.close();
    out_file.close();
}

void MiniGit::printdirectory(string path_minigit){
    
    cout << "List of files in <<.minigit>>: " << endl;
    for (const auto & file : fs::directory_iterator(path_minigit)){

        auto ori = file.path();
        string stringpath = ori.generic_string();
        cout << stringpath << endl;
    }
}


int DiffCheck_(FileNode* file, string localfile){
    

    string path_new, str1, str2, substr1, substr2, minigit_file_name;
    string path_minigit = "minigit/";
    path_new = "files/";
      
    if(fs::exists(path_minigit + file->name)==0){ //not exist in minigit    
        fileCopy(localfile, file->name, "LtoB");
    }
    else{ //exist in minigit
                
        str1 = readFileIntoString(path_new + localfile);
        str2 = readFileIntoString(path_minigit + file->name);
                
        if(str1.compare(str2) != 0){ //if file is updated
                
                    file->version = file->version + 1;
                    substr1 = file->name.substr(0,2);
                    substr2 = file->name.substr(4,7);
                    minigit_file_name = substr1 + "_"+to_string(file->version) + substr2;
                     
                    file->name = minigit_file_name;
                    fileCopy(localfile, minigit_file_name, "LtoB");
                    
        } 
    }
    file = file->next;  
    return 0;


}


bool DiffCheck_2(FileNode* file1, FileNode* file2){
    

    string path_new, str1, str2, substr1, substr2, minigit_file_name;
    string path_minigit = "minigit/";
    //path_new = "C:/Users/sookk/Desktop/C++/2275(2)/final-project-suhyun/code_1/";
    
    str1 = readFileIntoString(path_minigit + file2->name );
    str2 = readFileIntoString(path_minigit + file1->name);
               
    if(str1.compare(str2) != 0){ //different
        return true;
    } 
    return false; // same 


}


string MiniGit::commit(string msg, HashTable ht) {
    
    //traverse SLL and check if fileVersion file exist in minigit
    BranchNode* branch = commitHead;
    FileNode* file;

    string path_new, str1, str2, substr1, substr2, minigit_file_name;
    string path_minigit = "minigit/";
    path_new = "files/";
    
    while(branch->next!= NULL){
        branch = branch->next;
    }
    file = branch->fileHead;

    while(file){

        str1 = file->name.substr(0,2);
        str2 = file->name.substr(4,7);
        string localfile = str1+str2; //f1.txt
        DiffCheck_(file, localfile);
        file = file->next;
    }


    /*if(branch->previous){
            cout << "previous commit Message: " << branch->previous->commitMessage << endl;
    }*/
    
    //commit message adding to hashtable
    
    istringstream ss(msg);
    string del;
 
    while(getline(ss, del, ' ')) {
        ht.insertItem(del,branch->commitID);

    }
 
    //create new DLL 
    BranchNode* brnode = DLLinsert(msg);

    return to_string(brnode->commitID);
}


void MiniGit::printList(){

  
  BranchNode* br = commitHead;

  while(br){
    FileNode* tmp = br->fileHead;
    cout << "commitID: " << br->commitID << endl;
    cout << "commit message:" <<  br->commitMessage << endl;
    if(tmp == NULL)
    {
        cout << "SLL Head: NULL" << endl;
    }
    else {
        while(tmp->next != NULL){
            cout<< tmp->name <<" -> ";
            tmp = tmp->next;
        }
  
        cout<<tmp->name<<endl;
    }
    br = br->next; 
    
  }   
}

void MiniGit::writefile(string add, string filename){
    
    ofstream of;
    fstream f;
   
    // opening file using ofstream
    of.open(filename, ios::app);
    
    if (!of)
        cout << "No such file found";
    else {
        of << "\n"+add+"\n";
        of.close();
        string word;
       
        // opening file using fstream
        f.open(filename);
        while (f >> word) {
            of << word << " ";
        }
        f.close();
    }
}


void MiniGit::checkout(string commitID) {
    
   string path_new = "files/";
   BranchNode* br = commitHead;

   while(br){
    if(br->commitID == stoi(commitID)){
        
        FileNode* file = br->fileHead; 
        while(file){
            cout << file->name << endl;
            if(fs::exists("minigit/"+file->name)== 0){ //file not exist       
                cout << "not exist in .minigit " << endl;
                fileCopy(file->name, file->name, "BtoL");

            }
            else{ //file already exist ->  overwrite from minigit
                fs::remove(path_new + file->name);
                fileCopy(file->name, file->name, "BtoL");
            }
            file = file->next;
        }

    } br = br->next;
   }

}





void MiniGit::DiffAndStatus(string filename){
    

    string str1, str2, substr1, substr2, minigit_file_name;
    string path_minigit = "minigit/";
    string path = "files/";
    cout << readFileIntoString(path_minigit+ filename)<<endl;
    cout << "__________________________________________" << endl;
    
    
    //finding most recent version of given file 
    BranchNode* br = commitHead;
    while(br->next){
        br = br->next;
    }

    FileNode* newFile = br->fileHead;
    
    while(newFile){
        if(newFile->name[1] ==filename[1]){
            cout << readFileIntoString(path_minigit+ newFile->name) << endl;
        }
        newFile = newFile->next;
    } 
 
}

void MiniGit::delete_line(const char* file_name, string delete_line)
{
    // open file in read mode or in mode
    ifstream is(file_name);
    string line;
    // open file in write mode or out mode
    ofstream ofs;
    ofs.open("temp.txt", ofstream::out);
  
    // loop getting single characters
    while(getline(is, line)){
        if(line != delete_line){
            ofs << line << endl;
        }
    }
    // closing output file
    ofs.close();
  
    // closing input file
    is.close();
  
    // remove the original file
    remove(file_name);
  
    // rename the file
    rename("temp.txt", file_name);
}
