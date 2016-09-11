/*
	Description:	QuickSort: we pick a random element and partition he array, such that all
					numbers that are less than the partition element come before all the elements
					that are greater than it. The partition can be performed efficiently through
					a series of swaps.

					If we repeatedly partition the array (and its sub-arrays) around an element
					the array will eventyally become sorted. Hoever, as the partition element is
					not guaranteed to be the median (or anywhere near the median), our sorting
					could be very slow. This is the reason for the O(n^2).

	Run-time:		O(n log(n)) average and O(n^2) worst case.
	Memory:			O(log(n)).

	Programmer:		Michael Duarte

	Date:			Sep 10, 2016.	
*/

#include <iostream>
#include <vector>

using namespace std;

void print(const vector<int> &arr){
	cout << "["; 
	for (int i : arr){
		cout << " " << i;
	}
	cout << "]" << endl; 
}

void swap(vector<int> &arr, int x, int y){
	if (x != y){
		cout << "\t\t swaping: " << arr[x] << " <=> " << arr[y] << endl;  
		int aux = arr[x];
		arr[x] = arr[y];
		arr[y] = aux;
	}
}

int partition(vector<int> &arr, int left, int right){
	int index = (left+right)/2;
	int pivot = arr[index];
	cout << "\tPivot: " << pivot << " at index: " << index <<
			". left: " << left << ". right: " << right << endl ;  
	while (left <= right){

		while (arr[left] < pivot){ 
			cout << "\t\t" << arr[left] << " @(" << left << ") < " << pivot << endl;  
			++left;
		}
		while (arr[right] > pivot){
			cout << "\t\t" << arr[right] << " @(" << right << ") > " << pivot << endl;  
			--right;
		}

		while (left <= right){
			swap(arr, left, right);
			++left;
			--right;
		}
	}
	return left;
}

void quickSort(vector<int> &arr, int left, int right){
	int index = partition(arr, left, right);
	cout << "\tPartition: " << index << endl;
	if (left < index-1){ // sorting left half
		quickSort(arr, left, index-1);
	}
	if (index < right){// sorting right half
		quickSort(arr, index, right);
	}
}

void quickSort(vector<int> &arr){
	quickSort(arr, 0, arr.size()-1);
}


int main(){
	// vector<int> arr = {2, 4, 8, 16, 32};
	vector<int> arr = {128, 2, 16, 8, 512, 4, 32, 1, 64, 256};
	print(arr);
	quickSort(arr);
	print(arr);
	return 0;
} 