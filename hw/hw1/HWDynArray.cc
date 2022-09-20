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
		if(capacity == 0){
			capacity++;
		}
		else{
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
	//Runtime Big Omega (1) or O(size)
	void addEnd(int v) {
		if(size < capacity){
			p[size-1] = v;
		}
		else{
			checkGrow();
			int* temp = new int[capacity];
			for(uint32_t i = 0; i < size - 1; i++)
				temp[i] = p[i];
			temp[size-1] = v;
			delete [] p;
			p = temp;
		}
		size++;
	}
	//runtime is always O(size)
	void addStart(int v) {
		if(size < capacity){
			int past;
			for(uint32_t i = 1; i < size; i++){
				past = p[i];
				p[i] = p[i-1];
				
			}
			p[0] = v;
		}
		else{
			checkGrow();
			int* temp = new int[capacity];
			for(uint32_t i = 1; i < size; i++){
				temp[i] = p[i-1];
			}
			temp[0] = v;
			delete [] p;
			p = temp;
		}
		size++;
	}
	// Runtime O(size)
	void removeStart() { 
		int* temp = new int[capacity-1];
    		for (uint32_t i = 1; i < size; i++) {
        		temp[i-1] = data[i];
    		}
    		delete [] data;
    		data = temp;
    		capacity--;
		size--;
	}
	// Runtime O(size)
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
