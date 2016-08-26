
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

struct Result{
	int sum, startIndex, endIndex;
	Result():sum(0),startIndex(-1),endIndex(-1){}
	
};

// If we just care about the sum:
int findMaxSubArraySum(int array[], int length){
	int maxEnding = array[0], maxSF = array[0];
	for (int i = 1 ; i < length; ++i){
		maxEnding = max(array[i], maxEnding + array[i]);
  		maxSF = max(maxSF, maxEnding);
  	}
  	return maxSF;
}


// If we care about indexes and sum:
Result findSubArrayWithGreaterSum(int array[], int length){
	Result res;
	int maxEnding = array[0], res.sum = array[0]; // 
	for (int i = 1 ; i < length; ++i){
		if (maxEnding < 0){
			maxEnding = array[i];
			res.startIndex = i+1; // right after negative sums
		} else {
			maxEnding += array[i];
		}

		if (maxEnding > res.sum){
			res.sum = maxEnding;
			res.endIndex = i; // on sums > than maxSoFar
		}


	}
	return res;
}

int main() {
	int arr[] = {-2,1,-3,4,-1,2,1,-5,4};
	Result res = findSubArrayWithGreaterSum(arr, 9);
	cout << "Sum: " << res.sum << ". Indexes: ["<< res.startIndex<<", " <<res.endIndex<<"]\n";
}
