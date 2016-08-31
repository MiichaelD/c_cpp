/*
	Description:	4.9 BST Sequences: A binary search tree was created tby traversing through
					an array from left to right and inserting each element. Given a BST with
					distinct elements, print all possible arrays that could have led to this tree.

	Programmer:		Michael Duarte

	Date:			Aug 2nd, 2016.
	
*/

#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <deque>
#include <unordered_map>
#include <memory>
#include <set>

using namespace std;

template<class T>
struct Node {
	T data;
	Node *left = nullptr, *right = nullptr;

	Node(const T &val) : data(val) { }
	~Node() {
		if (left) {
			delete left;
			left = nullptr;
		}
		if (right) {
			delete right;
			right = nullptr;
		}
	}
	Node *addLeftNode(const T &val) {
		if (left)
			delete left;

		left = new Node<T>(val);
		return left;
	}
	Node *addRightNode(const T &val) {
		if (right)
			delete right;
		right = new Node<T>(val);
		return right;
	}
};

Node<char> *loadTree() {
	Node<char> *root = new Node<char>('a');
	auto b = root->addLeftNode('b');
	auto c = root->addRightNode('c');

	auto d = b->addLeftNode('d');
	auto e = b->addRightNode('e');

	e->addLeftNode('f');
	e->addRightNode('g');

	auto h = c->addLeftNode('h');
	auto i = c->addRightNode('i');

	h->addLeftNode('j');

	return root;
}

template<class T>
void printInOrder(Node<T> *node) {
	if (node == nullptr)
		return;

	printInOrder(node->left);
	cout << node->data << ", ";
	printInOrder(node->right);
}

template<class T>
void printPreOrder(const Node<T> *node) {
	if (node == nullptr)
		return;

	cout << node->data << ", ";
	printPreOrder(node->left);
	printPreOrder(node->right);
}

template<class T>
void printSequences(const vector<deque<T>> &seqs){
	cout << "Sequences: " << endl; 
	for (auto &seq : seqs){
		for (auto &element : seq){
			// cout << ++counter << ") " << element << ". ";
			cout << element << " ";
		}
		cout << endl;
	}
	cout << "Total = " << seqs.size() << endl; 
}

template<class T>
void weaveLists(vector<deque<T>> &results, deque<T> &first, deque<T> &second,
	deque<T> &prefix){

	if (first.empty() || second.empty()){
		deque<T> result = prefix;
		result.insert(result.end(), first.begin(), first.end());
		result.insert(result.end(), second.begin(), second.end());
		results.push_back(result);
		return;
	}

	for (deque<T> *list : {&first, &second}){
		T head = list->front();
		list->pop_front();
		prefix.push_back(head);
		weaveLists(results, first, second, prefix);
		prefix.pop_back();
		list->push_front(head);
	}
}


template<class T>
vector<deque<T>> allSequences(const Node<T> *node){
	vector<deque<T>> results;
	if (node == nullptr){
		results.emplace_back();
		return results;
	}

	deque<T> prefix;
	prefix.push_back(node->data);

	auto leftSeq = allSequences(node->left);
	auto rightSeq = allSequences(node->right);

	for (auto &left: leftSeq){
		for (auto &right: rightSeq){
			vector<deque<T>> weaved;
			weaveLists(results, left, right, prefix);
			results.insert(results.end(), weaved.begin(), weaved.end());
		}
	}
	return results;
}

int main() {
	shared_ptr<Node<char>> root(loadTree());
	printPreOrder(root.get());
	cout << endl << endl;

	auto sequences = allSequences(root.get());
	printSequences(sequences);
	return EXIT_SUCCESS;
}

