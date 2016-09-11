/*
	Description:	MergeSort: Divides the array in half, sorts each half and then merges them
					back together. Each of those halves has the same sorting algorithm applied
					to it. Eventually, you are merging just 2 single-element arrays. It is the
					"merge" part that does all the heavy lifting.

					The merge method operates by copying all the elements from the target array
					elements from the target array segment into a helper array, keeping track of
					where the start of the left and right halves should be (helperLeft and
					helperRight). We then iterate through helper, copying the smaller element
					from each half into the target array. At the end, we copy any remaining
					elements into the target array.

	Run-time:		O(n log(n)) average and worst case.
	Space:			O(n) due to auxiliary space used  to merge parts of the array
	Memory:			Depends.

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

void merge(vector<int> &arr, vector<int> &helper, int low, int mid, int high){
	// Copy both halves into a helper array
	for (int i = low; i <= high; ++i){
		helper[i] = arr[i];
	}

	int helperLeft = low;
	int helperRight = mid + 1;
	int current = low;

	// Iterate through helper array. Compare the left and right half, copying back
	// the smaller element from the 2 halves into the original array.
	while (helperLeft <= mid && helperRight <= high){
		if(helper[helperLeft] <= helper[helperRight]){
			arr[current] = helper[helperLeft];
			++helperLeft;
		} else {
			arr[current] = helper[helperRight];
			++helperRight;
		}
		++current;
	}

	// Copy the rest of the left side of the aray int othe target array
	int remaining = mid - helperLeft;
	for (int i = 0 ; i <= remaining; ++i){
		arr[current + i] = helper[helperLeft + i];
	}

	// You may notice that only the remaining elements from the left half of the helper
	// array are copied into the target array. Why not the right half? The right half
	// doesn't need to be copied bc it is already there.
}

void mergeSort(vector<int> &arr, vector<int> &helper, int low, int high){
	if (low < high){
		int mid = (low + high) / 2;
		mergeSort(arr, helper, low, mid); // sort left half
		mergeSort(arr, helper, mid+1, high); // sort right half
		merge(arr, helper, low, mid, high); // merge them
	}
}

void mergeSort(vector<int> &arr){
	vector<int> helper(arr.size());
	int high = arr.size() - 1;
	mergeSort(arr, helper, 0, high);
}


int main(){
	// vector<int> arr = {2, 4, 8, 16, 32};
	vector<int> arr = {128, 2, 16, 8, 512, 4, 32, 1, 64, 256};
	print(arr);
	mergeSort(arr);
	print(arr);
	return 0;
} 