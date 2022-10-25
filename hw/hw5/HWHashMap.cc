#include <iostream>
#include <fstream>
#include <cstdint>
/*
	Implement methods add(), get() and hist() for both types of hashmap
	You must read the file en213k.txt in the data directory.
	DO NOT put in a path, that will only work on your computer.

*/
using namespace std;

class HashMapLinearProbing {
private:
	struct Node {
		string key;
		uint32_t value;
		Node() : key("-"), value(0) {}
	};
	uint32_t size;
	uint32_t capacity;
	Node* table;

	uint32_t hash(string key){
		uint32_t sum = 0;
		for(uint32_t i = 0; i < key.size(); i++){
			sum = ((sum << 17) | (sum >> 15)) ^ ((sum << 7) | (sum >> 25)) + key[i];
		}
		return sum;
	}
public:
	HashMapLinearProbing(uint32_t capacity) : size(0), capacity(capacity), table(new Node[capacity]){
		for(uint32_t i = 0; i < capacity; i++){
			table[i].key = "-";
		}
	}
	~HashMapLinearProbing(){
		delete [] table;
	}
	HashMapLinearProbing(const HashMapLinearProbing& orig) = delete;

	void add(string word, uint32_t value){
		size++;
		uint32_t index = hash(word) % capacity;
		//cout << "Add Hash = " << index << endl;
		while(table[index].key != "-"){
			index++;
			if(index >= capacity)
				index = 0;
		}
		table[index].key = word;
		//cout << "Add Index = " << index << endl;
		table[index].value = value;
	}

	bool get(string word, uint32_t* id){
		uint32_t index = hash(word) % capacity;
		//cout << "Get Hash = " << index << endl;
		while(table[index].key != "-"){
			if(table[index].key == word){
				*id = table[index].value;
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

class HashMapLinearChaining {
private:
	struct Node {
		string key;
		uint32_t value;
		Node* next;
	};
	uint32_t size;
	uint32_t capacity;
	Node* table;


	uint32_t hash(string key){
		uint32_t sum = 0;
		for(uint32_t i = 0; i < key.size(); i++){
			sum = ((sum << 17) | (sum >> 15)) ^ ((sum << 7) | (sum >> 25)) + key[i];
		}
		return sum;
	}
public:
	HashMapLinearChaining(uint32_t capacity) : size(0), capacity(capacity), table(new Node[capacity]){
		for(uint32_t i = 0; i < capacity; i++){
			table[i].key = "-";
			table[i].value = 0;
			table[i].next = nullptr;
		}
	}
	~HashMapLinearChaining(){
		delete [] table;
	}
	HashMapLinearChaining(const HashMapLinearProbing& orig) = delete;

	void add(string word, uint32_t value){
		size++;
		uint32_t index = hash(word) % capacity;
		Node* temp;
		//cout << "Add Hash = " << index << endl;
		if(table[index].key != "-"){
			table[index].key = word;
			table[index].value = value;
			table[index].next = new Node();
		}
		else{
			temp = new Node();
			temp->key = word;
			temp->value = value;
			temp->next = &table[index];
			table[index]& = temp;
			delete [] temp;
		}
	}

	bool get(string word, uint32_t* id){
		uint32_t index = hash(word) % capacity;
		if(table[index].key != "-"){
			for(Node* temp = &table[index]; temp->next != nullptr; temp = temp->next){
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

int main() {
	constexpr int n = 1000000;
	HashMapLinearProbing m1(n);
	HashMapLinearChaining m2(n);
	int count = 0;
	string line;
	//read in the dictionary (213k words)
	ifstream dict ("en213k.txt");
	if(dict.is_open()){
    while( getline(dict, line) ){
      m1.add(line, count);
			m2.add(line, count);
			count++;
		}
  }
  dict.close();

	uint32_t id;

	cout << "\n\nLinear probing\n";
	const string words[] = {"apple", "bear", "cat", "dog", "arggg", "juwqehtrkqwejhr", "underbishop", "ting", "wonderwall"};
	for (int i = 0; i < 9; i++) {
		bool found = m1.get(words[i], &id);
		cout << "word " << words[i] << " " << found << "id=" << id << '\n';
	}

	// print out the histogram showing count of inserts taking 1, 2, 3, ... 9+
	m1.hist();

	cout << "\n\nLinear chaining\n";
	for (int i = 0; i < sizeof(words[i])/sizeof(char*); i++) {
		bool found = m2.get(words[i], &id);
		cout << "word " << words[i] << " " << found << "id=" << id << '\n';
	}
	// print out the histogram showing bins of size 0, 1, 2, 3, ... 9+
	m2.hist();
}
