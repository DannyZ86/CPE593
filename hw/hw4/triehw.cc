#include <iostream>
#include <fstream>

using namespace std;

/*
  Daniel Zatko
  Homework 4
  Trie Dictionary
  Dictionary Link:
  https://githup.com/StevensDeptECE/CPE593/blob/master/data/dict.txt
  */

/*
  I used code from cplusplus.com as a reference when trying to walk through a file
  https://cplusplus.com/doc/tutorial/files
*/

class TrieDictionary {
private:
  class TrieNode {
  public:
    // 0-25 represents each letter in the alphabet
    TrieNode* next[26];
    bool isWord;
    //Initializeing all 26 index's as null because c++ does not do this
    TrieNode(){
      isWord = false;
      for(int i = 0; i < 26; i++){
        next[i] = nullptr;
      }
    }
  };

  TrieNode* root;

public:
  //Constructor/Destructor
  TrieDictionary(){
    root = new TrieNode();
  }
  ~TrieDictionary() {}
  //Copy Constructors
  TrieDictionary(const TrieDictionary& orig) = delete;
  TrieDictionary& operator =(const TrieDictionary& orig) = delete;

  //Insert a word into the Dictionary
  void insert(string word){
    TrieNode* temp = root;
    //Here the -1 is due to the fact that fstream adds a return value to the end of the string
    for(int i = 0; i < word.size()-1; i++){
      int letter = word[i] - 'a';
      if(temp->next[letter] == nullptr){
        temp->next[letter] = new TrieNode();
      }
      temp = temp->next[letter];
    }
    temp->isWord = true;
  }

  bool find(string word){
    TrieNode* temp = root;
    //Here the -1 is due to the fact that fstream adds a return value to the end of the string
    for(int i = 0; i < word.size()-1; i++){
      int letter = word[i] - 'a';
      //Conditional case incase the word is not a letter a - z
      if(letter < 0 || letter >= 26){
        return false;
      }
      if(temp->next[letter] == nullptr){
        return false;
      }
      temp = temp->next[letter];
    }
    return temp->isWord;
  }

  bool containsPrefix(string prefix){
    TrieNode* temp = root;
    for(int i = 0; i < prefix.size(); i++){
      int letter = prefix[i];
      //Conditional case incase the word is not a letter a - z
      if(letter < 0 || letter >= 26){
        return false;
      }
      temp = temp->next[letter];
      if(temp->next[letter] == nullptr)
        return false;
    }
    return true;
  }
};

int main(){
  TrieDictionary treeDict;
  string line;

  //This will only work if the files are in your folder
  //Storing the words into the Dictionary
  ifstream dictionary ("dict.txt"); //Open file
  if(dictionary.is_open()){
    while( getline(dictionary, line) ){
      treeDict.insert(line);
    }
    dictionary.close();
  }

  //Searching for words in dictionary
  ifstream  spellcheck ("triespellcheck.txt"); //Open file
  if(spellcheck.is_open()){
    while( getline(spellcheck, line) ){
      if(treeDict.find(line) == false)
        cout << line << '\n';
    }
    spellcheck.close();

  }


}
