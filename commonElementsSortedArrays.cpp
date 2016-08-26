/* 
    Problem:    Given 2 sorted arrays, find he number of elements in common.
                The arrays are the same length and each has distinct elements.

    Source:     Cracking the coding interview 6th Ed. Best Conceivable Runtime (BCR)
*/

#include <unordered_set>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


void printCommonElements(int arrA[], size_t sizeA, int arrB[], size_t sizeB){
    int commonAmount = 0;
    for (int i = 0, j = 0; i < sizeA && j < sizeB;){
        if (arrA[i] < arrB[j]){
            ++i;
        } else if (arrA[i] > arrB[j]){
            ++j;
        } else {
            cout << " |" <<arrA[i] << "| ";
            ++commonAmount;
            ++j;
            ++i;
        }
    }
    cout << endl <<"Common elements found: " << commonAmount << endl; 
}


int main() {
    int arrA[] = {13,27,35,40,49,55,59};
    int arrB[] = {17,35,39,40,55,58,60};
    printCommonElements(arrA, sizeof(arrA)/sizeof(int), arrB, sizeof(arrB)/sizeof(int));
    return 0;
}

