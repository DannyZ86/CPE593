#include <iostream>

/*
	Daniel Zatko
	CPE 593
	Section A
	Double Linked List
	w head and tail
*/

using namespace std;

class DoubleLinkedList {
private:
	class Node {
	public:
		Node* next;
		Node* prev;
		int val;
		//Constructor to create a node, makes the code cleaner
		Node(Node* n, Node* p, int v) : next(n), prev(p), val(v) {}
	};

	Node* head;
	Node* tail;

public:
	DoubleLinkedList() : head(nullptr), tail(nullptr) {}
  ~DoubleLinkedList() {}
//Copy Constructors
	DoubleLinkedList(const DoubleLinkedList& orig) = delete;
	DoubleLinkedList& operator =(const DoubleLinkedList& orig) = delete;

	// implement to print out the list
	friend ostream& operator <<(ostream& s, const DoubleLinkedList& list) {}

	void addStart(int v) {
		//Case if list is empty
			if(head == nullptr){
			temp = new Node(nullptr, nullptr, v)
			head = temp;
			tail = temp;
			delete temp;
		}
		else{

		}
	}

	void addEnd(int v) {
		//Case if list is empty
		if(head == nullptr){
			temp = new Node(nullptr, nullptr, v)
			head = temp;
			tail = temp;
			delete temp;
		}
		else{

		}
	}

	void removeStart() {
		//Case if list is empty
		if(head == nullptr){
			return;
		}
	}

	void removeEnd() {
		//Case if list is empty
		if(head == nullptr){
			return;
		}
	}

	// insert v before pos. insert(0,v) would insert at the front.
	void insert(int pos, int v) {
	}
};

int main() {
	DoubleLinkedList a;
	const uint32_t n = 1000000;
	for (int i = 0; i < n; i++)
		a.addStart(i);
	for (int i = 0; i < n; i++)
		a.addEnd(i);
	for (int i = 0; i < 3*n/2; i++)
		a.removeStart();

	for (int i = 0; i < n/2 - 5; i++)
		a.removeEnd();

	cout << a << '\n';
	for (int i = 0; i < 10; i++)
		a.insert(1, i);
	cout << a << '\n';
}
