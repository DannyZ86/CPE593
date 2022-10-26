#include <iostream>
#include <fstream>
#include <cstdint>
/*
  Daniel Zatko
  CPE 593
  Section A
  Hash Maps

  I recieved some help on the Hash function and Chaining class from student Akash Rana
  He helped me by showing me the benefits of using a double pointer(**) instead of a pointer(*)
  for my keyTable. We also came up with the idea of adding a collision variable for each node.

*/
using namespace std;

class HashMapLinearProbing{
private:
  struct probingNode{
    string key;
    uint32_t value;
    int collisions;
    probingNode() : key(""), value(0), collisions(0) {}
  };

  uint32_t size;
  uint32_t capacity;
  probingNode* keyTable;

  uint32_t hash(string key){
    uint32_t sum = 0;
    for(uint32_t i = 0; i < key.size(); i++){
      sum = ((sum << 17) | (sum >> 15)) ^ ((sum << 7) | (sum >> 25)) + key[i];
    }
    return sum;
  }

public:
  //Constructors
  HashMapLinearProbing(int capacity) : size(0), capacity(capacity), keyTable(new probingNode[capacity]) {
    for(uint32_t i=0; i<capacity; i++){
        keyTable[i].key = "";
    }
  }
  ~HashMapLinearProbing(){
    delete [] keyTable;
  }
  HashMapLinearProbing(const HashMapLinearProbing& orig) = delete;

    //Add a word to Probing
  void add(string word, int value){
		uint32_t index = hash(word) % capacity;
    int count = 0;
		while(keyTable[index].key != ""){
			index++;
      count++;
			if(index >= capacity)
				index = 0;
		}
		keyTable[index].key = word;
		keyTable[index].value = value;
    keyTable[index].collisions = count;
    size++;
	}

	bool get(string word, int* id){
		uint32_t index = hash(word) % capacity;
		while(keyTable[index].key != ""){
			if(keyTable[index].key == word){
				*id = keyTable[index].value;
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
    int histogram[10] = {0}; //Initialize the histogram array
    //This way of finding collisions takes up more memory but im not sure how much more this would affect runtime
    for(uint32_t i = 0; i < capacity; i++){
      if(keyTable[i].collisions >= 9){
        histogram[9]++;
      }
      else{
        histogram[keyTable[i].collisions]++;
      }
    }

    /*
    This was my original way of trying to create the histogram but I realized my logic seemed off
    //This loop walks through the HashMap
    for(uint32_t i = 0; i < capacity; i++){
      key = keyTable[i].key;  //get the key from the table
      if(key == "") //If there is nothing in the bin then add to hist[0]
        histogram[0]++;
      else{ //Otherwise there is an element in the bin, so we need to see how many times it collided
        uint32_t index = hash(key) % capacity; //get the index number
        int count = 0; //start a counter at 0
    		while(keyTable[index].key != ""){ //do the same thing as in the add loop and see how many times you increase index
    			index++; //The amount of times you increase index is the amount of collisions
          count++;
    			if(index >= capacity)
    				index = 0;
    		}
        //Once you get out of the while loop add colisions to histogram
        if(count >= 9)
          histogram[9]++;
        else
          histogram[count]++;
      }
    }
    */

    //Print out histogram
    for(int i = 0; i<10; i++){
      cout << "Bin [" << i << "] = " << histogram[i] << endl;
    }
	}
  };

class HashMapLinearChaining{
private:
  struct chainingNode{
    string key;
		int value;
    chainingNode* next;
		chainingNode() : key(""), value(0), next(nullptr) {}
  };
  uint32_t size;
  uint32_t capacity;
  chainingNode** keyTable;

  uint32_t hash(string key){
    uint32_t sum = 0;
    for(uint32_t i = 0; i < key.size(); i++){
      sum = ((sum << 17) | (sum >> 15)) ^ ((sum << 7) | (sum >> 25)) + key[i];
    }
    return sum;
  }

public:
  //Constructors
  HashMapLinearChaining(int capacity) : size(0), capacity(capacity), keyTable(new chainingNode*[capacity]) {
    for(uint32_t i=0; i<capacity; i++){
      keyTable[i] = nullptr;
    }
  }
  ~HashMapLinearChaining(){
    delete [] keyTable;
  }
  HashMapLinearChaining(const HashMapLinearProbing& orig) = delete;

  //Add a word to Chaining
  void add(string word, int value){
    chainingNode* temp;
		uint32_t index = hash(word) % capacity;
		if(keyTable[index] != nullptr){
      temp = new chainingNode();
      temp->key = word;
      temp->value = value;
      temp->next = keyTable[index];
      keyTable[index] = temp;
		}
		else{
      temp = new chainingNode();
      temp->key = word;
			temp->value = value;
			temp->next = nullptr;
      keyTable[index] = temp;
		}
    size++;
	}

	bool get(string word, int* id){
		uint32_t index = hash(word) % capacity;
    chainingNode* head = keyTable[index];
		if(head != nullptr){
      if(head->next == nullptr){
        if(head->key == word){
					*id = head->value;
					return true;
        }
      }
			for(chainingNode* temp = head; temp->next != nullptr; temp = temp->next){
				if(temp->key == word){
					*id = temp->value;
					return true;
				}
			}
		}
    *id = index;
    return false;
  }

  void hist(){
    chainingNode* temp;
    int histogram[10] = {0}; //Initialize the histogram array
    //This loop walks through the HashMap
    for(uint32_t i = 0; i < capacity; i++){
      int count = 0;
      if(keyTable[i] == nullptr) //If there is no node bin size is 0
        histogram[0]++;
      else{ //Otherwise count how many node in the index
        temp = keyTable[i]; //make a helper node at the head of the list
        while(temp != nullptr){
          count++;
          temp = temp->next;
          }
        }
      if(count >= 9)
        histogram[9]++;
      else
        histogram[count]++;
    }
    //Print out histogram
    for(int i = 0; i<10; i++){
      cout << "Bin [" << i << "] = " << histogram[i] << endl;
    }
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
	//read in the dictionary (213k words)
	ifstream dict("en213k.txt");
  //ifstream dict("temp.txt");
	{// write your loop!
    while( getline(dict, line) ){
      m1.add(line, count);
      m2.add(line, count);
      count++;
    }
  }
  dict.close();
	int id;

	cout << "\n\nLinear probing\n";
  string words[] = {"apple", "bear", "cat", "dog", "arggg", "juwqehtrkqwejhr", "underbishop", "ting", "wonderwall"};
	for (int i = 0; i < 9; i++) {
		bool found = m1.get(words[i], &id);
		cout << "word " << words[i] << " " << found << "id=" << id << '\n';
	}
	// print out the histogram showing count of inserts taking 1, 2, 3, ... 9+
  cout << endl;
	m1.hist();

	cout << "\n\nLinear chaining\n";
	for (int i = 0; i < 9; i++) {
		bool found = m2.get(words[i], &id);
		cout << "word " << words[i] << " " << found << "id=" << id << '\n';
	}
	// print out the histogram showing bins of size 0, 1, 2, 3, ... 9+
  cout << endl;
	m2.hist();
}
