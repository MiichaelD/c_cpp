/*
	Description:	4.8 First Common Ancestor: Design an algorithm and write code to find
					the first common ancestor of 2 nodes in a binary tree.

	Nodes:			- This is not a Binary Search Tree.
					- Avoid storing additional nodes in a data structure.

	Special cases:	- Both nodes are the same node.
					- Only one of the nodes exists in the tree.
					- One node is contained in the other's node subtree.

	Programmer:		Michael Duarte

	Date:			Aug 2nd, 2016.
	
*/

#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
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
		left = new Node<T>(val);
		return left;
	}
	Node *addRightNode(const T &val) {
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
bool lookFor(const Node<T> *node, const T &val, vector<const Node<T>*> &path) {
	if (node == nullptr) {
		return false;
	}
	path.push_back(node);
	if (node->data == val) {
		return true;
	}

	if (lookFor(node->left, val, path))
		return true;
	if (lookFor(node->right, val, path))
		return true;

	path.pop_back();
	return false;
}

template<class T>
vector<const Node<T>*> findPath(const Node<T> *node, const T &val) {
	vector<const Node<T>*> path;
	lookFor(node, val, path);
	return path;
}


// OWN solution:
// Find the paths from the root all the way down to the nodes and compare them
// until we find the node where paths fork. If there is no fork we return the 
// last node from the shorter path.
// NOTE: this solution requires 2 additionals data structures (vectors of nodes)
// to keep track of the paths.
template<class T>
const Node<T>* getFirstCommonAncestor(const Node<T> *root, const T &val1, const T&val2) {
	vector<const Node<T>*> path1 = findPath(root, val1);
	vector<const Node<T>*> path2 = findPath(root, val2);
	int minPathLength = path1.size() < path2.size() ? path1.size() : path2.size();

	if (minPathLength > 0 ){
		for (int i = 0; i < minPathLength; ++i) {
			if (path1[i]->data != path2[i]->data) {
				return i > 0 ? path1[i - 1] : nullptr;
			}
		}

		// if we reached this point one node is parent of the other and there
		// was no difference in the paths, just one was shorter than the other.
		return path1[minPathLength-1];
	}

	return nullptr;
}


// Cracking the coding interview solution.
// with the variant of having originalRoot, this is just so if we don't find
// both nodes when we are in the real tree root, we return nullptr, that is,
// to diferentiate when a node is child of another and when we didn't find both nodes.
template<class T>
const Node<T>* getFirstCommonAncestor2(const Node<T> *originalRoot, const Node<T> *root, const Node<T> *p, const Node<T> *q) {
	if (root == nullptr || (root == p && root == q))
		return root;

	auto left = getFirstCommonAncestor2(originalRoot, root->left, p, q);
	if (left != nullptr && ( (left == p && left == q) || (left != p && left != q) ) ){
		// We found a node which is not P or Q OR a node which is P and Q, it must be ancestor.
		return left;
	}

	auto right = getFirstCommonAncestor2(originalRoot, root->right, p, q);
	if (right != nullptr && ( (right == p && right == q) || !(right == p || right == q) ) ){
		// We found a node which is not P or Q OR a node which is P and Q, it must be ancestor.
		return right;
	}

	if (right != nullptr && left != nullptr){
		return root; // this is the ancestor.
	} 
	if (root == p || root == q){ // root is one value we were looking for
		bool foundOtherNode = left != nullptr || right != nullptr; 
		if (foundOtherNode){ // check if the other node is one of roots children.
			return root; // this is the ancestor.
		} else if (originalRoot != root){
			return root; // return either p or q
		} else {
			return nullptr; // we didn't find both nodes;
		}
	} else {
		// if we are on the original tree root and we only found one node in either
		// subtree, there is no ancestor.
		return originalRoot == root ? nullptr : (left != nullptr ? left : right); // return non-null value
	}

}


int main() {
	shared_ptr<Node<char>> root(loadTree());
	printPreOrder(root.get());
	cout << endl << endl;

	// char val1 = 'd', val2 = 'g'; // b is ancestor
	// char val1 = 'a', val2 = 'i'; // a is ancestor
	// char val1 = 'a', val2 = 'm'; // NO ancestor
	// char val1 = 'b', val2 = 'm'; // NO ancestor
	char val1 = 'f', val2 = 'f';
	const Node<char> *antecestor = getFirstCommonAncestor(root.get(), val1, val2);
	if (antecestor != nullptr) {
		cout << "First Common Ancestor of node: \'" << val1 << "\' and \'" << val2 << "\' is: \t" << antecestor->data << endl;
	}
	else {
		cout << "No common ancestor found" << endl;
	}


	auto node1 = findPath(root.get(), val1).back();
	auto node2 = findPath(root.get(), val2).back();
	antecestor = getFirstCommonAncestor2(root.get(), root.get(), node1, node2);
	if (antecestor != nullptr) {
		cout << "First Common Ancestor of node: \'" << val1 << "\' and \'" << val2 << "\' is: \t" << antecestor->data << endl;
	}
	else {
		cout << "No common ancestor found" << endl;
	}

	return EXIT_SUCCESS;
}

