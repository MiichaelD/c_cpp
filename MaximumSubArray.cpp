//
//  MaximumSubArray.cpp
//  https://en.wikipedia.org/wiki/Maximum_subarray_problem
//
//  Created by Michael Duarte on 4/21/16.
//  Copyright © 2016 Michael Duarte. All rights reserved.
//
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Kadane's algorithm:
// Most simple solution, returns 0 if all numbers of the vector are negative
// which might not be the desired behavior.
int findMaxSum(const vector<int> &numbers){
    int maxEnding = 0, maxSoFar = 0;
    for (int number : numbers){
        maxEnding = max(0, number + maxEnding);
        maxSoFar = max(maxSoFar, maxEnding);
        cout << "\tnumber: " << number << ". maxEnding: " << maxEnding << ". MaxSoFar: "<< maxSoFar << endl;
    }
    return maxSoFar;
}

// Variation of Kadane's algorithm: works with vectors of only negative numbers.
int findMaxSumNonLimitedToZero(const vector<int> &numbers){
    if (numbers.empty())
        return 0;
    
    auto number = numbers.begin();
    int maxEnding = *number, maxSoFar = maxEnding;
    
    for (++number;number!=numbers.end(); ++number){
        maxEnding = max(*number, *number + maxEnding);
        maxSoFar = max(maxSoFar, maxEnding);
        cout << "\tnumber: " << *number << ". maxEnding: " << maxEnding << ". MaxSoFar: "<< maxSoFar << endl;
    }
    return maxSoFar;
}


struct SubsetSolution{
    bool found = false;
    size_t startIndex = 0 , endIndex = 0;
    int64_t sum = 0;
    vector<int> subset;
};

SubsetSolution findMaxSubset(const vector<int> &numbers){
    SubsetSolution solution;
    if (numbers.empty())
        return solution;
    
    int maxEnding = numbers.front();
    int maxSoFar = maxEnding;
    size_t startIndex = 0;
    size_t endIndex = 0;
    for (int i = 1 ; i < numbers.size(); ++i){
        int number = numbers[i];
        if (maxEnding > 0){
            maxEnding+=number;
        } else {
            startIndex = i;
            maxEnding = number;
        }
        if (maxEnding > maxSoFar){
            maxSoFar = maxEnding;
            endIndex = i;
        }
        cout << "\tnumber: " << number << ". maxEnding: " << maxEnding << ". MaxSoFar: "<< maxSoFar << endl;
    }
    
    solution.found = true;
    solution.startIndex = startIndex;
    solution.endIndex = endIndex;
    solution.sum = maxSoFar;
    for (size_t i = startIndex ; i <= endIndex; ++i){
        solution.subset.push_back(numbers[i]);
    }
    return solution;
}

int main(){
    vector<int> numbers {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    
    int sum = findMaxSum(numbers);
    cout << "Sum : " << sum << endl;
    
    SubsetSolution subset = findMaxSubset(numbers);
    if (subset.found){
        cout << "\tMax subset sum: " << subset.sum << " indixes: [" << subset.startIndex << '-' << subset.endIndex << ']'<< endl;
        for (int number : subset.subset){
            cout << number << ',';
        }
        cout << endl;
    } else {
        cout << "Subset not found" << endl;
    }
}
