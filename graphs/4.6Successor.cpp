/*
	Description:	4.6 Successor: Writre an algorithm to find the "next" node (i.e., in-order
					successor) of a given node in a BST. You may assume that each node has a
					link to its parent.

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
	shared_ptr<Node> left, right, parent;
	Node(int val):value(val){}
};


shared_ptr<Node> createBST(vector<int> &array, int start, int end){
	if (start > end)
		return shared_ptr<Node>(nullptr);
	int mid = (end + start) / 2;
	shared_ptr<Node> node(new Node(array[mid]));
	node->left = createBST(array, start, mid-1);
	if (node->left != nullptr)
		node->left->parent = node;
	node->right = createBST(array, mid+1, end);
	if (node->right != nullptr)
		node->right->parent = node;
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

shared_ptr<Node> leftMostNode(shared_ptr<Node> node){
	if (node == nullptr)
		return nullptr;

	while (node->left != nullptr){
		node = node->left;
	}
	return node;
}

shared_ptr<Node> findNextInOrderSuccessor(shared_ptr<Node> node){
	if (node == nullptr)
		return nullptr;
	
	if (node->right != nullptr){
		return leftMostNode(node->right);
	} else {
		shared_ptr<Node> parent, aux;
		parent  = node->parent;
		aux = node;
		while(parent != nullptr && parent->left != node){
			node = parent;
			parent = parent->parent;
		}
		return parent;
	}
}

shared_ptr<Node> findNode(shared_ptr<Node> root, int val){
	if (root == nullptr)
		return nullptr;
	if (root->value == val)
		return root;

	shared_ptr<Node> left = findNode(root->left, val);
	if (left != nullptr)
		return left;
	
	shared_ptr<Node> right = findNode(root->right, val);
	if (right != nullptr)
		return right;

	return nullptr;
}

void findNextNodesForNodes(shared_ptr<Node> root, vector<int> nodes){
	for (int n : nodes){
		shared_ptr<Node> node = findNode(root, n);
		shared_ptr<Node> next = findNextInOrderSuccessor(node);
		if (next == nullptr){
			if (node == nullptr)
				cout "There is no node " << n << " in the tree" << endl;
			else
				cout << "There is no next node after " << node->value << endl;
		} else {
			cout << "Next node after " << node->value << " is " << next->value << endl;
		}
	}
}

int main(){
	vector<int> array = {0,1,2,3,4,5,6,7,8,9};
	shared_ptr<Node> root = createBST(array, 0, array.size()-1);
	printInOrder(root);

	findNextNodesForNodes(root, {2,3,9});
	return 0;
}