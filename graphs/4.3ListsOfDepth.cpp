/*
	Description:	4.3 List of Depths: Given a binary tree, design an algorithm which
					creates a linked list of all the nodes at each depth.
					i.e., if you have a tree with depth D, you will have D linked lists.

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

// pushing each node in a queue, root first then its children
vector<vector<shared_ptr<Node>>> getTreeAsVector(shared_ptr<Node> root){
	vector<vector<shared_ptr<Node>>> result;
	queue<shared_ptr<Node>> queue;
	queue.push(root);
	cout << "Hello world" << endl; 
	while(!queue.empty()){
		int queueSize = queue.size();
		auto aux = queue.front();
		queue.pop();
		if ((queueSize & (queueSize-1)) == 0 ){
			if (result.empty() || result[result.size()-1].size())
				result.emplace_back();
		}

		if (aux == nullptr)	
			continue;
		result[result.size()-1].push_back(aux);
		queue.push(aux->left);
		queue.push(aux->right);
	}
	if (result[result.size()-1].empty())
		result.pop_back();
	return result;
}


// Using the recently created lists to iterate in order. We don't have to keep track
// of an extra data structure like we do in the first implementation.
vector<vector<shared_ptr<Node>>> getTreeAsVector2(shared_ptr<Node> root){
	vector<vector<shared_ptr<Node>>> result;
	result.emplace_back();
	if (root != nullptr)
		result.back().push_back(root);

	cout << "Hello world" << endl; 
	while(result.back().size()){
		result.emplace_back();
		vector<shared_ptr<Node>> &parents = result[result.size()-2];
		for (auto child : parents){
			if(child->left != nullptr)
				result.back().push_back(child->left);
			if(child->right != nullptr)
				result.back().push_back(child->right);
		
		}
	}
	if (result[result.size()-1].empty())
		result.pop_back();
	return result;
}

void printListsOfLists(vector<vector<shared_ptr<Node>>> &listOfLists){
	for (int i = 0; i < listOfLists.size(); ++i){
		cout << "List: " << i << " has: "; 
		for (int j = 0; j < listOfLists[i].size(); ++j){
			cout << listOfLists[i][j]->value << " ";
		}
		cout << endl;
	}
}

int main(){
	vector<int> array = {0,1,2,3,4,5,6,7,8,9};
	shared_ptr<Node> root = createBST(array, 0, array.size()-1);
	printInOrder(root);

	vector<vector<shared_ptr<Node>>> listOfLists = getTreeAsVector2(root);
	printListsOfLists(listOfLists);
	return 0;
}