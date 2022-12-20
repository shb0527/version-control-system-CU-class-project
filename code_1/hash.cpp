// CPP program to implement hashing with chaining
#include<iostream>
#include "hash.hpp"


using namespace std;

HashNode* HashTable::createNode(string key, HashNode* next)
{
    HashNode* nw = new HashNode;
    nw->key = key;
    nw->next = next;
    
    return nw;
}

HashTable::HashTable(int bsize)
{
    this->tableSize= bsize;
    table = new HashNode*[tableSize];
    for(int i=0;i < bsize;i++)
        table[i] = nullptr;
}

//function to calculate hash function
unsigned int HashTable::hashFunction(string s)
{
    int sum=0, index=0;
    for(string::size_type i=0; i < s.length(); i++){
        sum += s[i];
    }
    index = sum % tableSize;
    return index;

}

// TODO Complete this function
//function to search
HashNode* HashTable::searchItem(string key)
{
   
    //TODO
    for (int i = 0; i < tableSize; i++) {
       
        HashNode* head = table[i];
        // TODO: print all keys in slot i
        while(head!= NULL){
            if(head->key == key)
            {
                return head;
            }
            head = head->next;
    
        } 
    }
    return NULL;
    
}

//TODO Complete this function
//function to insert
bool HashTable::insertItem(string key, int cNum)
{
    
    //TODO
    if(!searchItem(key)){

        int index = hashFunction(key);
        HashNode* head = table[index];
        HashNode* newNode = createNode(key,head);
        newNode->commitNums.push_back(cNum); 
        table[index] = newNode;
        return true;
     }
    else{
        HashNode* node = searchItem(key);
        node->commitNums.push_back(cNum);
    }
    return false;
}


// function to display hash table //
/* assume the table size is 5. For each bucket it will show the 
** the string key and the commit number (separated by comma) within parenthesis
** e.g. the key is science and commit numbers are 1 and 4. The key science
** is hashed to position 0. So the print format will be-

0|| science(1,4,)
1|| 
2|| 
3|| 
4|| difficult(3,)-->fun(2,)-->computer(0,)

*/
void HashTable::printTable()
{
    for (int i = 0; i < tableSize; i++) {
        cout << i <<"|| ";
        HashNode* head = table[i];
        while(head!= NULL){
            cout << head->key;
            cout <<" (" ;
            for(int i = 0; i < head->commitNums.size(); i++){ 
                cout << head->commitNums[i] << "," ;
            }
            cout << ")";
            head = head->next;
            if(head){
                cout << "-->";
            }
        } 
        cout << endl;  
    }
}
