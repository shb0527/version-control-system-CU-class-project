#include <gtest/gtest.h>
#include "test_helpers.hpp"

#include "../code_1/hash.hpp"


std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::string readFileIntoString(std::string fileName){
	std::string line, out;
  	ifstream A;
  	A.open(fileName);
  	if(!A){throw std::runtime_error("could not open file: " + fileName);}
	while(getline(A,line)){
		out = out+line+"\n";
	}
	return out;
}

string test_insert(string arr[], int len, int tabSize)
{
    
    testing::internal::CaptureStdout();
    HashTable* ht = new HashTable(tabSize);
    
    for(int i=0;i<len;i++)
    {
        ht->insertItem(arr[i],i);
    }
    
    ht->printTable();
    string output = testing::internal::GetCapturedStdout();
    return output;
}


/*string test_init(){
    
    testing::internal::CaptureStdout();
    
}*/

string test_add(string localfile[], int len, int cases){
    
    MiniGit mini;
    HashTable ht(5);
    string path = "minigit/";
    testing::internal::CaptureStdout();
    if(cases == 1){
        mini.init(5);
        for(int i = 0; i < len; i++){ 
            mini.add(localfile[i]);
        }
    }
    else {
        mini.init(4);
        mini.add("f1.txt");
        mini.add("f2.txt");
        mini.commit("computer science", ht);    
        for(int i = 0; i < len; i++){
            mini.add(localfile[i]);
        }
    }

    mini.printList();
    ht.printTable();
    mini.printdirectory(path);
    string output = testing::internal::GetCapturedStdout();
    return output;
}

string test_rm(string filename){
    
    MiniGit mini;
    HashTable ht(5);
    testing::internal::CaptureStdout();
    
    mini.init(4);
    mini.add("f1.txt");
    mini.add("f2.txt");
    mini.commit("computer science", ht);    
    mini.add("f3.txt");
    mini.printList();
    cout << "After delete:" << endl;
    mini.rm(filename);
    mini.printList();
    string output = testing::internal::GetCapturedStdout();
    
    return output;
}
 
    
string test_commit(int cases){
    
    MiniGit mini;
    HashTable ht(5);
    
    string path = "minigit/";
    testing::internal::CaptureStdout();
    if(cases == 1){
        mini.init(5);
        mini.add("f1.txt");
        mini.add("f2.txt");
        mini.commit("computer science", ht);
        mini.printList();
        ht.printTable();
        mini.printdirectory(path);
    }
    else if(cases== 2){
 
        mini.init(5);
        mini.add("f1.txt");
        mini.add("f2.txt");
        mini.commit("computer science", ht);
        mini.printList();
        ht.printTable();
        mini.printdirectory(path);
    }
    else if(cases==3){
  
        mini.init(5);
        mini.add("f1.txt");
        mini.add("f2.txt");
        mini.commit("computer science", ht);
        mini.add("f3.txt");
        mini.writefile("water punch", "files/f1.txt");
        mini.commit("science fun", ht);
        mini.printList();
        ht.printTable();
        mini.printdirectory(path);
        mini.delete_line("files/f1.txt" , "water punch");
    
    }
    else if(cases == 4){
        mini.init(5);
        mini.add("f1.txt");
        mini.add("f2.txt");
        mini.commit("computer science", ht);
        mini.add("f3.txt");
        mini.writefile("water punch", "files/f2.txt");
        mini.commit("science fun", ht);
        mini.printList();
        ht.printTable();
        mini.printdirectory(path);
        mini.delete_line("files/f2.txt" , "water punch"); //deleting the added line to the local file
    } 
    
    else if(cases==5){ //without changing after second commit in case 4
        mini.init(5);
        mini.add("f1.txt");
        mini.add("f2.txt");
        mini.commit("computer science", ht);
        mini.add("f3.txt");
        mini.writefile("water punch", "files/f2.txt");
        mini.commit("science fun", ht); 
        mini.commit("mathematics homework", ht);
        mini.printList();
        ht.printTable();
        mini.printdirectory(path);
        mini.delete_line("files/f2.txt" , "water punch");

    }
    
    else {
        mini.init(5);
        mini.add("f1.txt");
        mini.add("f2.txt");
        mini.printList();
        mini.commit("computer science", ht);
        mini.add("f3.txt");
        mini.writefile("water punch", "files/f1.txt");
        mini.commit("science fun", ht);
        mini.writefile("hello", "files/f3.txt");
        mini.commit("strawberry cheese", ht);
        mini.printList();
        ht.printTable();
        mini.printdirectory(path);
        mini.delete_line("files/f1.txt" , "water punch");
        mini.delete_line("files/f3.txt" , "hello");
    }
    string output = testing::internal::GetCapturedStdout();
    
    return output;
    
}

string test_searchHash(string word){
    
    MiniGit mini;
    HashTable ht(5);
    
    string path = "minigit/";
    testing::internal::CaptureStdout();
    
        mini.init(5);
        mini.add("f1.txt");
        mini.add("f2.txt");
        mini.commit("computer science", ht);
        mini.add("f3.txt");
        mini.writefile("water punch", "files/f2.txt");
        mini.commit("science fun", ht);
        mini.commit("water ocean", ht);
        mini.writefile("pink people", "files/f3.txt");
        mini.commit("mountain water yellow", ht);
        mini.printList();
        ht.printTable();
        mini.printdirectory(path);
        mini.delete_line("files/f2.txt" , "water punch");
        mini.delete_line("files/f3.txt" , "pink people");
    
        int size = ht.searchItem(word)->commitNums.size();
   
        cout << "commit IDs containing " << word << " ";
        for(int i = 0; i < size; i++){
            cout << ht.searchItem(word)->commitNums[i] << " ";
        }
    
     string output = testing::internal::GetCapturedStdout();
    
    return output;
    
        
}

string test_checkOut(string commitNum){
     
    MiniGit mini;
    HashTable ht(5);
    
    string path = "minigit/";
    testing::internal::CaptureStdout();
    
        mini.init(5);
        mini.add("f1.txt");
        mini.add("f2.txt");
        mini.commit("computer science", ht);
        mini.add("f3.txt");
        mini.writefile("water punch", "files/f2.txt");
        mini.commit("science fun", ht);
        mini.commit("water ocean", ht);
        mini.writefile("pink people", "files/f3.txt");
        mini.commit("mountain water yellow", ht);
        mini.printList();
        ht.printTable();
        mini.printdirectory(path);
        cout <<"------------------------------"<< endl;
        cout << "Overwriting files into minigit.." << endl;
        mini.checkout(commitNum);
        cout << "finished." << endl;
        mini.delete_line("files/f2.txt" , "water punch");
        mini.delete_line("files/f3.txt" , "pink people");
    
        string output = testing::internal::GetCapturedStdout();
    
    return output;
    
}
string test_DiffandStatus(string filename){
    
    
    MiniGit mini;
    HashTable ht(5);
    testing::internal::CaptureStdout();
    
    string path = "minigit/";

    mini.init(4);
    mini.add("f1.txt");
    mini.add("f2.txt");
    mini.commit("computer science", ht);
    mini.add("f3.txt");
    mini.writefile("water punch", "files/f1.txt");
    mini.commit("science fun", ht);    
    mini.DiffAndStatus("f1_0.txt");
    //mini.delete_line("files/f1.txt" , "water punch");
    string output = testing::internal::GetCapturedStdout();
    
    return output;
    
}
