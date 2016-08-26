/*
	Description:	4.2 Minimal Tree: Given a sorted (increasing order) array with unique integer elements,
					wite an algorithm to create a binary search tree with minimal-height.

	Programmer:		Michael Duarte

	Date:			Aug 25th, 2016.
	
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


shared_ptr<Node> createBST(vector<int> &array, int start, int end, int level = 0){
	if (start > end)
		return shared_ptr<Node>(nullptr);
	int mid = (end + start) / 2;
	for (int i = 0; i < level; ++i){
		cout << "\t";
	}
	shared_ptr<Node> node(new Node(array[mid]));
	cout << "created node with value: " << array[mid] << endl;
	node->left = createBST(array, start, mid-1, ++level);
	node->right = createBST(array, mid+1, end, level);
	return node;
}

void printInOrder(shared_ptr<Node> root){
	if (root == nullptr)
		return;

	printInOrder(root->left);
	cout << root->value << " ";
	printInOrder(root->right);
}

int main(){
	vector<int> array = {0,1,2,3,4,5,6,7,8,9};
	shared_ptr<Node> root = createBST(array, 0, array.size()-1, 0);
	printInOrder(root);
	cout << endl;
	return 0;
}