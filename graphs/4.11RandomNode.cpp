/*
	Description:	4.11 Random Node: You are implementing a Binary Search Tree class from 
					scratch, in addition to insert, find, and delete, has method getRandomNode(),
					which return a random node from the tree. All nodes should be equally likely
					to be chosen. Design and implement an algorithm for the getRandomNode(), and
					explain how you would implement the rest of the methods.

	Programmer:		Michael Duarte

	Date:			Sept 4, 2016.
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
#include <stdlib.h>     // srand, rand
#include <time.h>       // time

using namespace std;

template<class T>
class Node{
	T m_value;
	uint32_t m_childrenCount = 1;
	shared_ptr<Node> m_left, m_right;

	public:
	Node(const T &val):m_value(val){}

	~Node() {
		cout << "Node deleted: " << m_value << '(' << this  << ')' << endl; 
	}

	const T& value() const {
		return m_value;
	}

	const uint32_t getCount(){
		return m_childrenCount;
	}

	const uint32_t incrementCount(int amount = 1){
		return m_childrenCount += amount;
	}
	
	shared_ptr<Node> &left(){
		return m_left;
	}

	shared_ptr<Node> &right(){
		return m_right;
	}

	shared_ptr<Node> addLeftNode(const T &val){
		m_left = make_shared<Node>(val);
		return m_left;
	}

	shared_ptr<Node> addRightNode(const T &val){
		m_right = make_shared<Node>(val);
		return m_right;
	}
};

template<class T>
void printInOrder(shared_ptr<Node<T>> root, int level = 0){
	if (root == nullptr)
		return;
	printInOrder(root->left(), level+1);
	// cout << root->value() << " ";
	for (int i = 0; i < level; ++i){
		cout << "\t";
	}
	cout << root->value() << '(' << root.get() << ')'<< endl;
	printInOrder(root->right(), level+1);
}

template<class T>
void printPreOrder(shared_ptr<Node<T>> root, int level = 0){
	if (root == nullptr)
		return;

	for (int i = 0; i < level; ++i){
		cout << "\t";
	}
	cout << root->value() << '(' << root.get() << ')'<< endl;
	printPreOrder(root->left(), ++level);
	printPreOrder(root->right(), level);
}

template<class T>
void insert(shared_ptr<Node<T>> root,  const T &val){
	if (val <= root->value()){
		if (root->left() == nullptr){
			root->addLeftNode(val);
		} else {
			insert(root->left(), val);
		}
	} else {
		if (root->right() == nullptr){
			root->addRightNode(val);
		} else {
			insert(root->right(), val);
		}
	}
	root->incrementCount();
}

template<class T>
shared_ptr<Node<T>> remove(shared_ptr<Node<T>> root,  const T &val){
	if (val == root->value()){
		if (root->right() == nullptr){
			if (root->left() == nullptr){
				return nullptr;
			} else {
				return root->left();
			}
		} else {
			if (root->left() == nullptr){
				return root->right();
			} else {
				shared_ptr<Node<T>> aux = root->right();
				while(aux->left() != nullptr){
					aux->incrementCount(root->left()->getCount());
					aux = aux->right();
				}
				// cout << "Adding: " << root->left()->value() << '(' << root->left().get()<< "), with size of "<<
					 // root->left()->getCount()<<". to: " << aux->value() << '(' << aux.get() << ')'<< endl;
				aux->left() = root->left();
				aux->incrementCount(root->left()->getCount());
				// cout << "new size: " << aux->getCount() << endl; 
				return root->right();
			}
		}
	}
	if (val < root->value()){
		bool deleted = false;
		if (root->left() != nullptr){
			int size = root->left()->getCount();
			root->left() = remove(root->left(), val);
			if (size > root->left()->getCount())
				deleted = true;
		}
		if (deleted == false)
			return root;

	} else {
		bool deleted = false;
		if (root->right() != nullptr){
			int size = root->right()->getCount();
			root->right() = remove(root->right(), val);
			if (size > root->right()->getCount())
				deleted = true;
		}
		if (deleted == false)
			return root;
	}
	root->incrementCount(-1);
	return root;
}

template<class T>
shared_ptr<Node<T>> find(shared_ptr<Node<T>> root, const T &val){
	if (root->value() == val)
		return root;
	else if (val <= root->value()){
		return (root->left() == nullptr ? root->left() : find(root->left(), val));
	}
	return (root->right() == nullptr ? root->right() : find(root->right(), val));
}

template<class T>
shared_ptr<Node<T>> getIthNode(shared_ptr<Node<T>> root, int i = 0){
	if (root == nullptr)
		return nullptr;

	int leftSize = root->left() == nullptr ? 0 : root->left()->getCount();
	if (i < leftSize){
		return getIthNode(root->left(), i);
	} else if (i == (leftSize+1)) {
		return root;
	} else {
		return getIthNode(root->right(), i - (leftSize+1));
	}
}

template<class T>
shared_ptr<Node<T>> getRandomNode(shared_ptr<Node<T>> root){
	if (root == nullptr)
		return nullptr;

	srand(time(NULL));
	int nodeNumber = (rand() % root->getCount()) + 1;
	cout << "Random node number: " << nodeNumber << endl; 
	return getIthNode(root, nodeNumber);	
}



template<class T>
shared_ptr<Node<T>> createTree(const vector<T> &values){
	auto it = values.begin();
	shared_ptr<Node<T>> root = std::make_shared<Node<T>>(*it);
	for(++it; it != values.end(); ++it){
		insert(root, *it);
	}
	return root;
}

int main(){
	vector<int> values = {20,10,30,5,15,35,3,7,17};
	shared_ptr<Node<int>> root = createTree(values);

	cout << "Tree: " << endl; 
	printInOrder(root);

	auto node = getRandomNode(root);
	printInOrder(node);
	return 0;
}