/*
	Description:	4.4 Check if given binary tree is balanced. For the purposes of the question,
					a balanced tree is defined to be a tree such that the heights of the 2 subtrees
					of any node never differ by more than one

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

int getHeight(shared_ptr<Node> root){
	if (root == nullptr)
		return -1;

	return max(getHeight(root->left), getHeight(root->right)) + 1;
}

unordered_map<Node*, int> heightMap;
int getHeightMemo(shared_ptr<Node> root){
	if (root == nullptr)
		return -1;

	int leftHeight, rightHeight;
	if (heightMap.find(root.get()) != heightMap.end())
		leftHeight = heightMap[root.get()];
	else{
		heightMap[root.get()] = leftHeight = getHeight(root->left);
	}

	if (heightMap.find(root.get()) != heightMap.end())
		rightHeight = heightMap[root.get()];
	else{
		heightMap[root.get()] = rightHeight = getHeight(root->right);
	}
	return max(leftHeight, rightHeight) + 1;
}

bool isBalanced(shared_ptr<Node> root){
	if (root == nullptr)
		return true;

	int heightDiff = abs(getHeightMemo(root->left) - getHeightMemo(root->right));
	if (heightDiff > 1){
		return false;
	} else {
		return isBalanced(root->left) && isBalanced(root->right);
	}
}


int main(){
	vector<int> array = {0,1,2,3,4,5,6,7,8,9};
	shared_ptr<Node> root = createBST(array, 0, array.size()-1);
	printInOrder(root);

	cout << "Height: " << getHeight(root) << endl;
	cout << "Is Balanced: " << (isBalanced(root)?"Yes": "No") << endl;

	return 0;
}