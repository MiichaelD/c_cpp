/*
	Description:	4.5 Validate BST: implement a function to check if a binary tree
					is a binary search tree.

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


shared_ptr<Node> createBST(vector<int> &array, int start, int end){
	if (start > end)
		return shared_ptr<Node>(nullptr);
	int mid = (end + start) / 2;
	shared_ptr<Node> node(new Node(array[mid]));
	node->left = createBST(array, start, mid-1);
	node->right = createBST(array, mid+1, end);
	return node;
}

void printInOrder(shared_ptr<Node> root, int level = 0){
	if (root == nullptr)
		return;

	printInOrder(root->left, ++level);
	cout << root->value << " ";
	printInOrder(root->right, level);
	
	if (level == 1){
		cout << endl;
	}
}



// checking only immediate children is not enough!
// i.e.:
//				(20)
//			   /	\
//			(10)	 (30)
//			   \
//				(25)
//
bool isBST1(shared_ptr<Node> root){
	if (root == nullptr)
		return true;


	if (root->left != nullptr){
		if (root->left->value > root->value){
			cout << "\t" << root->left->value << " > " << root->value << endl; 
			return false;
		}
		if (!isBST1(root->left))
			return false;
	}
	if (root->right != nullptr){
		if (root->right->value <= root->value){
			cout << "\t" <<  root->right->value << " <= " << root->value << endl;
			return false;
		}
		if (!isBST1(root->right))
			return false;
	}
	return true;
}

bool isBST(shared_ptr<Node> root, int *min = nullptr, int *max = nullptr){
	if (root == nullptr)
		return true;


	if ( (min != nullptr && root->value <= *min) || (max != nullptr && root->value > *max) )
		return false;

	if (! (isBST(root->left, min, &root->value) && isBST(root->right, &root->value, max)) )
		return false;

	return true;
}



int main(){

	vector<int> array = {0,1,2,3,4,5,6,7,8,9};
	shared_ptr<Node> root = createBST(array, 0, array.size()-1);
	printInOrder(root);

	// this would be a vald BST acording to isBST1(): vector<int> array = {0,1,5,6,4,5,6,7,8,9};
	cout << "is Binary Search Tree: " << (isBST(root)? "YES":"NO") << endl;

	return 0;
}