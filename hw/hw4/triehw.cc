#include <iostream>

using namespace std;

/*
  Daniel Zatko
  Homework 4
  Trie Dictionary
  Dictionary Link:
  https://githup.com/StevensDeptECE/CPE593/blob/master/data/dict.txt
  */
class TrieDictionary {
private:
  class TrieNode {
  public:
    // 0-25 represents each letter in the alphabet
    TrieNode* next[26];
    bool isWord;
  };
  TrieNode* root;

public:
  //Constructor/Destructor
  TrieDictionary(){
    //Initializeing all 26 index's as null because c++ does not do this
    root = new TrieNode();
    for(int i = 0; i < 26; i++){
      root[i] = nullptr;
    }
  }
  ~TrieDictionary() {}
  //Copy Constructors
  TrieDictionary(const TrieDictionary& orig) = delete;
  TrieDictionary& operator =(const TrieDictionary& orig) = delete;

  //Insert a word into the Dictionary
  void insert(string word){
    TrieNode* temp = root;
    for(int i = 0; i < word.size(); i++){
      char letter = word[i] - 'a';
      if(temp->next[letter] == nullptr)
        temp->next[letter] = new TrieNode();
      temp = temp->next[letter];
    }
    temp->isWord = true;
  }

  bool find(string word){
    TrieNode* temp = root;
    for(int i = 0; i < word.size(); i++){
      char letter = word[i] - 'a';
      temp = temp->next[letter];
      if(temp[letter] == nullptr)
        return false;
    }
    return temp->isWord;
  }

  bool containsPrefix(string prefix){
    TrieNode* temp = root;
    for(int i = 0; i < word.size(); i++){
      char letter = word[i];
      temp = temp->next[letter];
      if(temp[letter] == nullptr)
        return false;
    }
    return true;
  }
};

int main(){
  TrieDictionary treeDict;
}
