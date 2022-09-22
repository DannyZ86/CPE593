#include <iostream>
#include <cstdint>

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
		//This function assumes that the capacity is not zero
		if(size < capacity){
			return;
		}
		else{
			int* temp = new int[capacity*2];
			for(uint32_t i = 0; i < size; i++)
				temp[i] = p[i];
			delete [] p;
			p = temp;
			capacity *= 2;
		}
	}

public:
	//For the constructor and destructor stuff, I had help from a alumni
	//He helped me understand the purpose and syntax
	//His name is Joey Kuhn
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
		checkGrow();
		p[size] = v;
		size++;
	}

	//runtime is always O(size)
	//No matter what you always have to shift the array over once
	//Therefore the code does not need to change from BadDynamicArray
	void addStart(int v) {
		int* temp = new int[capacity+1];
		temp[0] = v;
		for(uint32_t i = 1; i <= size; i++){
			temp[i] = p[i-1];
		}
		delete [] p;
		p = temp;
		size++;
	}

	// Runtime O(size)
	//No matter what you always have to shift the array over once
	//Therefore the code does not need to change from BadDynamicArray
	void removeStart() {
		int* temp = new int[capacity-1];
    for (uint32_t i = 1; i < size; i++) {
      temp[i-1] = p[i];
    }
    delete [] p;
    p = temp;
		size--;
	}

	// Runtime O(1)
	void removeEnd() {
		size--;
	}

	int getSize(){
		return size;
	}

	void removeEvens() {
		int* temp = new int[capacity];
		int j = 0;
		for(uint32_t i = 0; i < size; i++){
			if(p[i] % 2 != 0){
				temp[j] = p[i];
				j++;
			}
		}
		delete [] p;
		p = temp;
		size = j;
	}
};

int main() {
	GrowArray a(500); // empty list, with 500 elements\

	//Tested and it seems to work as it should
	for (int i = 0; i < 500; i++)
		a.addEnd(i); // really fast!

	//code to check my array after addEnd function
/*
	for(uint32_t i=0; i < a.getSize(); i++)
		cout << a.get(i) << " ";
	cout << '\n';
*/

	//Tested and seems to grow as it should
	for (int i = 0; i < 100000; i++)
		a.addEnd(i); // every time you need to grow, double

	//Tested and seems to output as shown
	a.addStart(5);
	// 5 0 1 2 3 4 5 6 7 8....   499 0 1 2 3 4 5 6 .... 99999

	//Both functions tested and seem to have correct output which was corrected on discord
	for (int i = 0; i < 90500; i++)
		a.removeEnd();

	for (int i = 0; i < 9000; i++)
		a.removeStart();

	// 999 1000 1001 1002 1003 1004 1005 .... .... 1999

  a.removeEvens();
/*
	for(uint32_t i=0; i < a.getSize(); i++)
		cout << a.get(i) << " ";
	cout << '\n';
*/
//	cout << a.getSize();



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
