#include <iostream>
#include "../code_1/miniGit.hpp"
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. init " << endl;
    cout << " 2. add " << endl;
    cout << " 3. rm " << endl;
    cout << " 4. commit " << endl;
    cout << " 5. checkout" << endl;
    cout << " 6. search" << endl;
    cout << " 7. quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
int main(int argc, char* argv[]) {
   
    MiniGit minigit;
    HashTable ht(5);
    string path = "minigit";
    
    string ans,commitID, key, filename;
    char msg[40];
    char line[100];
    int option;
    do{
      
        displayMenu();
        cin >> option;
        switch(option)
        {
            case 1:  { 

                minigit.init(5);
                minigit.printList();
                ht.printTable();
                minigit.printdirectory(path);
                
                break;
            }
            case 2:{
                
                
                cout << "Enter name of file to add: (f1.txt, f2.txt..etc)\n";
                cin >> filename;
                cout << endl;
                
                while (minigit.searchFile(filename) == true){
                    cout << "File already exists." << endl;
                    cout << "Enter name of file to add: (f1.txt, f2.txt..etc)\n";
                    cin >> filename;
                }
                    
                cout << endl;
                minigit.add(filename);
                minigit.printList();
                cout << "-----------------"<< endl;
                ht.printTable();
                cout << "-----------------"<< endl;
                minigit.printdirectory(path);
            
                break;
            }
            case 3:{
                
                cout << "Enter name of file to remove: (f1.txt, f2.txt..etc)\n";
                cin >> filename;
                cout << endl;
                
                while (minigit.searchFile(filename) == false){
                    cout << "File does not exist." << endl;
                    cout << "Enter name of file to remove: (f1.txt, f2.txt..etc)\n";
                    cin >> filename;
                }
                    
                minigit.rm(filename);
                minigit.printList();
                cout << "-----------------"<< endl;
                ht.printTable();
                cout << "-----------------"<< endl;
                minigit.printdirectory(path);
              
        
                break;
            }
            case 4:{
  
                cout << "Enter a new commit message: \n" ;
                cin.ignore();
                cin.getline(msg, 40);
               
                minigit.commit(msg, ht);
                minigit.printList();
                cout << "-----------------"<< endl;
                ht.printTable();
                cout << "-----------------"<< endl;
                minigit.printdirectory(path);
                string ss = filename;
                const char* cc= ("files/" + ss).c_str();
                cout << cc << endl;
                minigit.delete_line(cc, line);
                break;
            }
            case 5:{
                cout << "Enter a commit ID you want to check: " << endl;
                cin >> commitID;
                cout << endl;
                cout << "Overwriting files into minigit.." << endl;
                minigit.checkout(commitID);
                cout << "finished." << endl;
                
                break;
                
            }
          case 6:{
                cout << "Enter a key that you want to search: (one word)" << endl;
                cin >> key ;
                cout << endl;
                int size = ht.searchItem(key)->commitNums.size();
                if(size == 0){
                    cout << "no key found" << endl;
                } 
                else{
                    for(int i = 0; i < size; i++){
                       cout << ht.searchItem(key)->commitNums[i] << " ";
                    }
                }
                
                break;
          }
            default:

                cout << "Quitting..." << endl;
                cout << "Goodbye!"<<endl;
                break;   
        }
    } while(option != 7);
    
    
    
    
    return 0;
}
