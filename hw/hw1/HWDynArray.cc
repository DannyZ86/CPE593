#include <iostream>
#include <cstdint>
#include <vector>

using namespace std;

/*
Daniel Zatko
CPE 593
Section A
*/


class GrowArray {
private:
	int* p;
	uint32_t size; // the number of elements used
	uint32_t capacity; // the amount of memory
	void checkGrow () {
		// if the memory needs to grow, double in size
		// TODO: YOU IMPLEMENT THIS
		if (size > capacity){
			capacity *= 2;
		}
	}

public:
	GrowArray() : size(0), capacity(0), p(nullptr) {}
	GrowArray(uint32_t capacity) : size(0), capacity(capacity), p(new int[capacity]) {}
	~GrowArray() { delete [] p; }

	GrowArray(const GrowArray& orig) = delete;
	GrowArray& operator =(const GrowArray& orig) = delete;

	int get(uint32_t pos) const {
    return p[pos];
  }

	void addEnd(int v) {
		//Initial condition for when size = 0
		if(size == 0){
			int* temp = new int[capacity+1];
			temp[0] = v;
			delete [] p;
			p = temp;
			capacity++;
		}
		else if(size < capacity){
			p[size-1] = v;
		}
		else{
			int* temp = new int[capacity*2];
			for(uint32_t i = 0; i < capacity; i++)
				temp[i] = p[i];
			temp[size] = v;
			delete [] p;
			p = temp;
		}
		size++;
		checkGrow();
	}

	void addStart(int v) {

	}

	void removeStart() {

	}

	void removeEnd() {

	}

	void removeEvens() {

	}
};

int main() {
	//How does this work?
	GrowArray a(500); // empty list, with 500 elements


	for (int i = 0; i < 500; i++)
		a.addEnd(i); // really fast!

	for (int i = 0; i < 100000; i++)
		a.addEnd(i); // every time you need to grow, double

	a.addStart(5);
	// 5 0 1 2 3 4 5 6 7 8....   499 0 1 2 3 4 5 6 .... 99999

	for (int i = 0; i < 90500; i++)
		a.removeEnd();

	for (int i = 0; i < 9000; i++)
		a.removeStart();


	// 999 1000 1001 1002 1003 1004 1005 .... .... 1999

  a.removeEvens();

	//999 1001 1003 ... 1999
  // keep 2 indices (i,j)
	// first index goes through the array
	// second advances only when you have one you want
	/*
		example
           j
     5 4 3 2 1
     5 3 1 2 1
             i
    j = 0
    for i = 0 to 4
     if want a[i]
      a[j++] = a[i]
     end
    end
	 */

	 //This wont work...
	//cout << a << '\n';
}
