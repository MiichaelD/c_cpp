/*
	Description:	Sorted Search, No Size: You are given an array-like data structure Listy
					which lacks a size method. It does, however, have an elementAt(i) method
					that returns the element i in O(1) time. If i is beyond the bounds of the
					data structure, it returns -1 (For this reason, the data structure only
					supports positive integers). Given a List ywhich contains sorted positive
					integers, find the index at which an element x occurs. If x occurs
					multiple times, you may return any index.

	Programmer:		Michael Duarte

	Date:			Sep 11, 2016.	
*/
#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;


class Listy : public vector<int>{
private:
	mutable int foundSize = -1;

protected:	
	size_t size() const { return vector<int>::size(); }

	int findSize() const {
		static int fast_runner = 5;
		if (foundSize != -1)
			return foundSize;
		for(int i = 0, j = 0; true; ++i, j+=fast_runner){
			if (at(j) == -1){
				cout << "\t" << j << " is out of bounds, looking from " << j-fast_runner << " to " << j << endl; 
				for (i = j-fast_runner;i<j && at(i) != -1; ++i);
				foundSize = i - 1;
				return foundSize;
			}
		}
		return -1;
	}

	bool hasSizeBeenFound() const {
		return foundSize != -1; 
	}

	void saveSize(int s) const { 
		foundSize = s;
		cout << "\tListy has a size of " << foundSize << endl; 
	}

	void push_back(int i) { vector<int>::push_back(i);}
	void emplace_back(int i) { vector<int>::emplace_back(i);}
	void pop_back() { vector<int>::pop_back();}
	// Yeah, vector has many more modifiers and it would have been easier to
	// just have a member vector within Listy class (or to private inherit it),
	// but I wanted to be able to do a for-each search as in a normal vector :P.
	// This is not necessary for the solution anyway.
public:
	Listy(initializer_list<int> list){
		foundSize = -1;
		reserve(list.size());
		for (int i : list){
			push_back(i);
		}
	}

	int operator[](int index) const {
		return at(index);
	}

	int at(int index) const {
		if (index >= size())
			return -1;
		return vector<int>::at(index);
	}

	int getSize() const { 
		if (!hasSizeBeenFound()){
			findSize();
		}
		return foundSize;
	}
};

// First solution was to look linearly for the end of the array
// the problem is that this brings a O(n) time.
// This solution is mmm okay if we cache the value and do many queries on the same list
int binarySearch(const Listy &arr, int x){
	int low = 0;
	int mid;
	// I encapsulated the search for the end within the struct, the problem specifies
	// that there is no getSize() function on Listy, but I did it just to be able to
	// cache the found sizes per list, and not to keep the cache in the solution itself,
	// just for convenience.
	int high = arr.getSize(); 
	
	while (low <= high){
		mid = (low + high) / 2;
		if (arr[mid] == x)
			return mid;
		if (arr[mid] < x)
			low = mid + 1;
		else 
			high = mid - 1;
	}
	return -1;
}

// Basically a normal binary search but counting "-1" as a big number
int bookSearch(const Listy &list, int x, int low, int high){
	int mid;
	while (low <= high){
		mid = (low + high) / 2;
		int middle = list[mid];
		if (middle > value || middle == -1){
			high = mid - 1; // search left
		} else if(middle < value){
			low = mid + 1; // search right
		} else {
			return mid;
		}
	}
	return -1;
}

// Book solution takes O(log(n)) time just as it normally would with a normal array
int bookSearch(const Listy &list, int x){
	int index = 1;
	// we look for a range of indexes where the value might be growing exponentially
	// instead of linearly. This will take log(n) time to find the index range
	for(;list[index] != -1 && list[index < value]; index *= 2);

	// and log (n) to find the number
	return bookSearch(list, x, index / 2, index)
}

void print(const Listy &arr){
	cout << "["; 
	for (int i : arr){
		cout << " " << i;
	}
	cout << "]" << endl; 
}

int main() {
	Listy arr = {1,3,4,5,7,10,14,15,16,19,20,25};
	print(arr);
	for (int i : {5, 14, 4, 24, 26}){
		int index = binarySearch(arr, i);
		if (index < 0){
			cout << "Element " << i << " not found." << endl;
		} else {
			cout << "Element " << i << " was found at index: " << index << endl; 
		}
	}
	return EXIT_SUCCESS;
}

