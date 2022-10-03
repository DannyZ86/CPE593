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
	friend ostream& operator <<(ostream& s, const DoubleLinkedList& list) {
		for (Node* temp = list.head; temp != nullptr; temp = temp->next)
      s << temp->val << ' ';
    return s;
	}

	void addStart(int v) {
		Node* temp;
		//Case if list is empty
		if(head == nullptr){ // O(1)
			temp = new Node(nullptr, nullptr, v);
			head = temp;
			tail = temp;
		}
		else{ // O(1)
			temp = new Node(head, nullptr, v);
			head = temp;
		}
	}

	void addEnd(int v) {
		Node* temp;
		//Case if list is empty
		if(head == nullptr){ // O(1)
			temp = new Node(nullptr, nullptr, v);
			head = temp;
			tail = temp;
		}
		else{	// O(1)
			Node* p = tail;
			temp = new Node(nullptr, tail, v);
			p->next = temp;
			tail = temp;
		}
	}

	void removeStart() { // O(1)
		//Case if list is empty
		if(head == nullptr){ // O(1)
			return;
		}
		else{	//O(1)
			Node* temp = head;
			head = head->next;
			//Checks to see if the element removed was the last element in the list
			if (head == nullptr)
				tail = nullptr;
			delete temp;
		}
	}

	void removeEnd() {
		//Case if list is empty
		if(head == nullptr){ // O(1)
			return;
		}
		else{	// O(1)
			Node* temp = tail;
			if(tail->prev == nullptr){
				tail = nullptr;
				head = nullptr;
				delete temp;
			}
			else{ // O(1)
				tail = tail->prev;
				tail->next = nullptr;
				delete temp;
			}
		}
	}

	// insert v before pos. insert(0,v) would insert at the front.
	void insert(int pos, int v) {
		if(head == nullptr)
			return;
		else{
			Node* temp;
			Node* p = head;
			for(int i = 0; i < pos - 1; i++){
				if(p == nullptr)
					return;
				p = p->next;
			}
			temp = new Node(p->next, p, v);
			p->next = temp;
		}
	}
};

int main() {
	DoubleLinkedList a;
	const uint32_t n = 100; //1000000
	for (int i = 0; i < n; i++)
		a.addStart(i);
	//cout << a << '\n';

	for (int i = 0; i < n; i++)
		a.addEnd(i);
	//cout << a << '\n';

	for (int i = 0; i < 3*n/2; i++)
		a.removeStart();
	//cout << a << '\n';

	for (int i = 0; i < n/2 - 5; i++)
		a.removeEnd();
	//cout << a << '\n';

	for (int i = 0; i < 10; i++)
		a.insert(1, i);
	//cout << a << '\n';

}
