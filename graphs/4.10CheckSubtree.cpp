/*
	Description:	4.10 Check Subtree: T1 and T2 are 2 very large binary trees, with T1 much bigger
					than T2. Create an algorithm to determine if T2 is a subtree of T1

					A tree T2 is a subtree of T1 if there exists a node n in T1 such that the
					subtree of n is identical to T2. That is, if you cut off the tree at node n,
					the 2 trees would be identical.

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

template<class T>
class Node{
	T m_value;
	shared_ptr<Node> m_left, m_right;
	
	public:
	Node(const T &val):m_value(val){}

	const T& value() const {
		return m_value;
	}
	
	shared_ptr<Node> &left(){
		return m_left;
	}

	shared_ptr<Node> addLeftNode(const T &val){
		m_left = make_shared<Node>(val);
		return m_left;
	}

	shared_ptr<Node> addLeftNode(const shared_ptr<Node<T>> &other){
		m_left = other;
		return m_left;
	}

	shared_ptr<Node> &right(){
		return m_right;
	}

	shared_ptr<Node> addRightNode(const T &val){
		m_right = make_shared<Node>(val);
		return m_right;
	}

	shared_ptr<Node> addRightNode(const shared_ptr<Node<T>> &other){
		m_right = other;
		return m_right;
	}

};

template<class T>
shared_ptr<Node<T>> createTreeFromVector(vector<int> &array, int start, int end){
	if (start > end)
		return shared_ptr<Node<T>>(nullptr);
	int mid = (end + start) / 2;
	shared_ptr<Node<T>> node = make_shared<Node<T>>(array[mid]);
	node->addLeftNode( createTreeFromVector<T>(array, start, mid-1) );
	node->addRightNode( createTreeFromVector<T>(array, mid+1, end) );
	return node;
}


template<class T>
void printInOrder(shared_ptr<Node<T>> root){
	if (root == nullptr)
		return;

	printInOrder(root->left());
	cout << root->value() << " ";
	printInOrder(root->right());
}


// Check if 2 subtrees are identical matches.
template<class T>
bool matchSubTree(shared_ptr<Node<T>> t1, shared_ptr<Node<T>> t2){
	if (t1 == nullptr && t2 == nullptr)
		return true;

	if ( t1 == nullptr || t2 == nullptr || t1->value() != t2->value())
		return false;

	if (!matchSubTree(t1->left(), t2->left()))
		return false;

	if (!matchSubTree(t1->right(), t2->right()))
		return false;

	return true;
}

// Look for a node that has the same value as the root of t2,
// once it is found, compare both subtrees match.
template<class T> 
bool isSubtree(shared_ptr<Node<T>> t1, shared_ptr<Node<T>> t2){
	if ( (t1 == nullptr || t2 == nullptr) )
		return false;

	if (t1->value() == t2->value() && matchSubTree(t1, t2))
		return true;

	return isSubtree(t1->left(), t2) || isSubtree(t1->right(), t2);
}


int main(){
	vector<int> array = {0,1,2,3,4,5,6,7,8,9};
	shared_ptr<Node<int>> root = createTreeFromVector<int>(array, 0, array.size()-1);
	array = {5,6,7,8,9};
	shared_ptr<Node<int>> root2 = createTreeFromVector<int>(array, 0, array.size()-1);
	printInOrder(root);
	cout << endl;
	printInOrder(root2);
	cout << endl << "Checking if T1 contains T2" << endl; 
	bool isSubtree1 = isSubtree(root, root2);
	cout << (isSubtree1 ? "The tree T2 is contained in T1" : "T2 was not found in T1") << endl; 
	
	return 0;
}