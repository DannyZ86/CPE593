#include <iostream>
#include <fstream>
#include <cstdint>

using namespace std;

class HashMapLinearProbing{
private:
  struct probingNode{
    string key;
    int value;
    probingNode() : key("-"), value(0) {}
  };
  int size;
  int capacity;
  probingNode* keyTable;

  int hash(string key){
    int sum = 0;
    for(int i = 0; i < key.size(); i++){
      sum = ((sum << 17) | (sum >> 15)) ^ ((sum << 7) | (sum >> 25)) + key[i];
    }
    return sum;
  }

public:
  //Constructors
  HashMapLinearProbing(int capacity) : size(0), capacity(capacity), keyTable(new probingNode[capacity]) {
    for(int i=0; i<capacity; i++){
        keyTable->key = "-";
    }
  }
  ~HashMapLinearProbing(){
    delete [] keyTable;
  }
  HashMapLinearProbing(const HashMapLinearProbing& orig) = delete;
    //Add a word to Probing
  void add(string word, int value){
		size++;
    probingNode* temp;
		int index = hash(word) % capacity;
    temp = &keyTable[index];
    cout << "Hash index is " << index << endl;
		while(temp->key != "-"){
			index++;
			if(index >= capacity)
				index = 0;
		}
    cout << "Index is " << index << endl;
		temp->key = word;
		temp->value = value;
    size++;
	}

	bool get(string word, int* id){
    probingNode* temp;
		uint32_t index = hash(word) % capacity;
    temp = &keyTable[index];
		while(temp->key != "-"){
			if(temp->key == word){
				*id = temp->value;
				return true;
			}
			index++;
			if(index >= capacity)
				index = 0;
		}
		*id = index;
		return false;
	}

	void hist(){

	}
  };

class HashMapLinearChaining{
private:
  struct chainingNode{
    string key;
		int value;
    chainingNode* next;
		chainingNode() : key("-"), value(0), next(nullptr) {}
  };
  int size;
  int capacity;
  chainingNode* keyTable;

  int hash(string key){
    int sum = 0;
    for(int i = 0; i < key.size(); i++){
      sum = ((sum << 17) | (sum >> 15)) ^ ((sum << 7) | (sum >> 25)) + key[i];
    }
    return sum;
  }

public:
  //Constructors
  HashMapLinearChaining(int capacity) : size(0), capacity(capacity), keyTable(new chainingNode[capacity]) {
    for(int i=0; i<capacity; i++){
      keyTable->key = "0";
    }
  }
  ~HashMapLinearChaining(){
    delete [] keyTable;
  }
  HashMapLinearChaining(const HashMapLinearProbing& orig) = delete;

  //Add a word to Chaining
    chainingNode* temp;
    chainingNode* head;
    void add(string word, int value){
		int index = hash(word) % capacity;
    head = &keyTable[index];

		if(head->key != "-"){
			head->key = word;
			head->value = value;
			head->next = new chainingNode();
		}
		else{
			temp = new chainingNode();
			temp->key = word;
			temp->value = value;
			temp->next = head;
			head = temp;
			delete [] temp;
		}
    size++;
	}

	bool get(string word, int* id){
    chainingNode* head;
		int index = hash(word) % capacity;
    head = &keyTable[index];
		if(head->key != "-"){
			for(chainingNode* temp = head; temp->next != nullptr; temp = temp->next){
				if(temp->key == word){
					*id = index;
					return true;
				}
			}
		}
	  *id = index;
  	return false;
  	}

  void hist(){
	}
};
/*
	Implement methods add(), get() and hist() for both types of hashmap
	You must read the file en213k.txt in the data directory.
	DO NOT put in a path, that will only work on your computer.

*/

int main() {
	constexpr int n = 1000000;
	HashMapLinearProbing m1(n);
	HashMapLinearChaining m2(n);
	int count = 0;
  string line;
  cout << "BEFORE ADD" << endl;
	//read in the dictionary (213k words)
	//ifstream dict("en213k.txt");
  ifstream dict("temp.txt");
	{// write your loop!
    while( getline(dict, line) ){
      m1.add(line, count);
      //m2.add(line, count);
      count++;
    }
  }
  dict.close();
  cout << "AFTER ADD" << endl;
	int id;

	cout << "\n\nLinear probing\n";
  string words[] = {"apple", "bear", "cat", "dog", "arggg", "juwqehtrkqwejhr", "underbishop", "ting", "wonderwall"};
	for (int i = 0; i < 9; i++) {
		bool found = m1.get(words[i], &id);
		cout << "word " << words[i] << " " << found << "id=" << id << '\n';
	}
	// print out the histogram showing count of inserts taking 1, 2, 3, ... 9+
	m1.hist();

	cout << "\n\nLinear chaining\n";
	for (int i = 0; i < 9; i++) {
		bool found = m2.get(words[i], &id);
		cout << "word " << words[i] << " " << found << "id=" << id << '\n';
	}
	// print out the histogram showing bins of size 0, 1, 2, 3, ... 9+
	m2.hist();
}
