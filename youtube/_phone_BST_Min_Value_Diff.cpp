/*
  Description:  Given a BST, find the minimum value difference between
                any two nodes in the BST.

  For:          YouTube/Google.

  Programmer:   Michael Duarte.

  Date:         Aug 26th, 2016.


       (5)
     /     \
    3       8
   / \     /  \
  2   4   7    9

  min diff = (3-2) == 1


f(<5>, MAX_INT, MAX_INT)
 f(<3>, 5 - 3 = 2, MAX_INT)
  f(<2>, 3 - 2 = 1, MAX_INT)
  min = 1
 min = min {2 ,1} = 1
  f(<4>, (4 - 3) = 1, 1)
  min = 1
 ....


another example:
      10
   5       18
1    7   11   24

  min diff = (11 - 10) == 1
*/


#include <iostream>
#include <string>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cstdint>
#include <vector>
#include <queue>
#include <stack>
#include <memory>
#include <iomanip>

using namespace std;

struct Node{
  int value;
  shared_ptr<Node> left, right;
  Node(int val):value(val){}
};


shared_ptr<Node> createBSTFromSortedArray(vector<int> &array, int start, int end){
  if (start > end)
    return shared_ptr<Node>(nullptr);
  int mid = (end + start) / 2;
  
  shared_ptr<Node> node(new Node(array[mid]));
  node->left = createBSTFromSortedArray(array, start, mid-1);
  node->right = createBSTFromSortedArray(array, mid+1, end);
  return node;
}

shared_ptr<Node> insert(shared_ptr<Node> root, int value) {
  if (!root) 
    return shared_ptr<Node>(new Node(value));
  else if (value == root->value)
    root->value = value;
  else if (value < root->value)
    root->left = insert(root->left, value);
  else  // key > root->key
    root->right = insert(root->right, value);
  return root;
}

shared_ptr<Node> createBSTFromArray(vector<int> &array, int start, int end){
  shared_ptr<Node> root(new Node(array[start]));

  for (int i = start + 1; i <= end; ++i) {
    insert(root, array[i]);
  }
  return root;
}

void printInOrder(shared_ptr<Node> root){
  if (root == nullptr)
    return;

  printInOrder(root->left);
  cout  << root->value << " ";
  printInOrder(root->right);
}


void findMinDiff(shared_ptr<Node> root, int &compareValue, int &min){
  if (root == nullptr || min == 1){ 
    return;
  }

  findMinDiff(root->left, compareValue, min); 

  int diff = abs(root->value - compareValue);
  if (diff < min)
    min = diff;

  compareValue = root->value;

  findMinDiff(root->right, compareValue, min);
}


int findMinDiff(shared_ptr<Node> root){
  int minimum= INT_MAX;
  int compareValue = INT_MAX;
  int rootValue = INT_MAX;

  findMinDiff(root, compareValue , minimum);
  if (root != nullptr){
    rootValue = root->value;
  }
  if (minimum == INT_MAX || ( minimum == (INT_MAX - rootValue)) ){  
    cout << "There is no MINIMUM DIFFERENCE in the tree" << endl;
    minimum = -1; // invalid difference value
  } else{
    cout << "min difference: " << minimum << endl;
  }
  return minimum;
}


int main(){
  // vector<int> array = {0,1,2,3,4,5,6,7,8,9};
  vector<int> sortedArray = {1,5,7,10,12,18,24};
  vector<int> array = {10,5,12,1,24,7,18};
  shared_ptr<Node> root = createBSTFromArray(array, 0, array.size()-1);
  printInOrder(root);
  cout << endl;
  findMinDiff(root);
  
  return 0;
}
