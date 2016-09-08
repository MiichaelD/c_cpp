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

using namespace std;

template<class T>
class Node{
	T m_value;
	uint32_t m_childrenCount = 1;
	shared_ptr<Node> m_left, m_right;
	
	shared_ptr<Node> addLeftNode(const T &val){
		m_left = make_shared<Node>(val);
		return m_left;
	}

	shared_ptr<Node> addRightNode(const T &val){
		m_right = make_shared<Node>(val);
		return m_right;
	}

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
	
	shared_ptr<Node> &left(){
		return m_left;
	}

	shared_ptr<Node> &right(){
		return m_right;
	}

	void insert(const T &val){
		if (val <= m_value){
			if (m_left == nullptr){
				addLeftNode(val);
			} else {
				m_left->insert(val);
			}
		} else {
			if (m_right == nullptr){
				addRightNode(val);
			} else {
				m_right->insert(val);
			}
		}
		++m_childrenCount;
	}

	shared_ptr<Node> remove(const T &val){
		if (val == m_value){
			if (m_right == nullptr){
				if (m_left == nullptr){
					return nullptr;
				} else {
					return m_left;
				}
			} else {
				if (m_left == nullptr){
					return m_right;
				} else {
					shared_ptr<Node> aux = m_right;
					while(aux->left() != nullptr){
						aux->m_childrenCount += m_left->getCount();
						aux = aux->right();
					}
					cout << "Adding: " << m_left->value() << '(' << m_left.get()<< "), with size of "<<
						 m_left->getCount()<<". to: " << aux->value() << '(' << aux.get() << ')'<< endl;
					aux->m_left = m_left;
					aux->m_childrenCount += m_left->getCount();
					cout << "new size: " << aux->getCount() << endl; 
					return m_right;
				}
			}
		}
		if (val < m_value){
			bool deleted = false;
			if (m_left != nullptr){
				int size = m_left->getCount();
				m_left = m_left->remove(val);
				if (size > m_left->getCount())
					deleted = true;
			}
			if (deleted == false)
				return std::make_shared<Node>(*this);

		} else {
			bool deleted = false;
			if (m_right != nullptr){
				int size = m_right->getCount();
				m_right = m_right->remove(val);
				if (size > m_right->getCount())
					deleted = true;
			}
			if (deleted == false)
				return std::make_shared<Node>(*this);
		}
		--m_childrenCount;
		return std::make_shared<Node>(*this);
	}

	shared_ptr<Node> find(const T &val){
		if (m_value == val)
			return std::make_shared<Node>(*this);
		else if (val <= m_value){
			return (m_left == nullptr ? m_left : m_left->find(val));
		}
		return (m_right == nullptr ? m_right : m_right->find(val));
	}

	shared_ptr<Node> getRandomNode(){

	}
};

template<class T>
void printInOrder(shared_ptr<Node<T>> root){
	if (root == nullptr)
		return;

	printInOrder(root->left());
	cout << root->value() << " ";
	printInOrder(root->right());
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
shared_ptr<Node<T>> createTree(const vector<T> &values){
	auto it = values.begin();
	shared_ptr<Node<T>> root = std::make_shared<Node<T>>(*it);
	for(++it; it != values.end(); ++it){
		root->insert(*it);
	}
	return root;
}

int main(){
	vector<int> values = {20,10,30,5,15,35,3,7,17};
	shared_ptr<Node<int>> root = createTree(values);

	cout << "Tree: " << endl; 
	printPreOrder(root);
	auto r15 = root->find(15);
	cout << "Root to be promoted: ";
	printPreOrder(r15);
	// cout << "roots size: " << r15->getCount() << endl;

	cout << "Deleting 10" << endl; 
	root = root->remove(10);

	cout << "New tree:" << endl; 
	printPreOrder(root);

	auto rr15 = root->find(15);
	printPreOrder(rr15);
	cout << "rr roots size: " << rr15->getCount() << ". address: " <<rr15.get() << endl;
	printPreOrder(r15);
	cout << "r  roots size: " <<  r15->getCount() << ". address: " << r15.get() << endl;
	return 0;
}