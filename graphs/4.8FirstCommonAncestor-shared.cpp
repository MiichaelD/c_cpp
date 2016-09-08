/*
	Description:	4.8 First Common Ancestor: Design an algorithm and write code to find
					the first common ancestor of 2 nodes in a binary tree.

	Notes:			- This is not a Binary Search Tree.
					- Avoid storing additional nodes in a data structure.

	Special cases:	- Both nodes are the same node.
					- Only one of the nodes exists in the tree.
					- One node is contained in the other's node subtree.

	Programmer:		Michael Duarte

	Date:			Sep 2nd, 2016.
	
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
class Node{
private:
	T m_value;
	shared_ptr<Node> m_left, m_right;
	
public:
	Node(const T &val):m_value(val){}

	T &setValue(const T &val){
		m_value = val;
		return m_value;
	}

	const T& value() const {
		return m_value;
	}
	
	std::shared_ptr<Node> &left(){
		return m_left;
	}

	std::shared_ptr<Node> addLeftNode(const T &val){
		m_left = std::make_shared<Node>(val);
		return m_left;
	}

	std::shared_ptr<Node> addLeftNode(const std::shared_ptr<Node<T>> &other){
		m_left = other;
		return m_left;
	}

	std::shared_ptr<Node> &right(){
		return m_right;
	}

	std::shared_ptr<Node> addRightNode(const T &val){
		m_right = std::make_shared<Node>(val);
		return m_right;
	}

	std::shared_ptr<Node> addRightNode(const std::shared_ptr<Node<T>> &other){
		m_right = other;
		return m_right;
	}

};

template<class T>
void printPreOrder(std::shared_ptr<Node<T>> root){
	if (root == nullptr)
		return;

	std::cout << root->value() << " ";
	printPreOrder(root->left());
	printPreOrder(root->right());
}


std::shared_ptr<Node<char>> loadTree() {
	std::shared_ptr<Node<char>> root = std::make_shared<Node<char>>('a');
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
bool getNodesPathToRoot(std::shared_ptr<Node<T>> node, const T &val, std::vector<std::shared_ptr<Node<T>>> &path) {
	if (node == nullptr) {
		return false;
	}
	path.push_back(node);
	if (node->value() == val) {
		return true;
	}

	if (getNodesPathToRoot(node->left(), val, path))
		return true;
	if (getNodesPathToRoot(node->right(), val, path))
		return true;

	path.pop_back();
	return false;
}

template<class T>
std::vector<std::shared_ptr<Node<T>>> getPathToRoot(std::shared_ptr<Node<T>> node, const T &val) {
	vector<std::shared_ptr<Node<T>>> path;
	getNodesPathToRoot(node, val, path);
	return path;
}

// OWN solution:
// Find the paths from the root all the way down to the nodes and compare them
// until we find the node where paths fork. If there is no fork we return the 
// last node from the shorter path.
// NOTE: this solution requires 2 additionals data structures (vectors of nodes)
// to keep track of the paths.
template<class T>
std::shared_ptr<Node<T>> getFirstCommonAncestor(std::shared_ptr<Node<T>> root, const T &val1, const T&val2) {
	std::vector<std::shared_ptr<Node<T>>> path1 = getPathToRoot(root, val1);
	std::vector<std::shared_ptr<Node<T>>> path2 = getPathToRoot(root, val2);
	int minPathLength = path1.size() < path2.size() ? path1.size() : path2.size();

	if (minPathLength > 0 ){
		for (int i = 0; i < minPathLength; ++i) {
			if (path1[i]->value() != path2[i]->value()) {
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
std::shared_ptr<Node<T>> getFirstCommonAncestor2(std::shared_ptr<Node<T>> originalRoot,
	std::shared_ptr<Node<T>> root, std::shared_ptr<Node<T>> p, std::shared_ptr<Node<T>> q) {

	if (root == nullptr || (root == p && root == q))
		return root;

	auto left = getFirstCommonAncestor2(originalRoot, root->left(), p, q);
	if (left != nullptr && ( (left == p && left == q) || (left != p && left != q) ) ){
		// We found a node which is not P or Q OR a node which is P and Q, it must be ancestor.
		return left;
	}

	auto right = getFirstCommonAncestor2(originalRoot, root->right(), p, q);
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


template<class T>
std::shared_ptr<Node<T>> findNode(std::shared_ptr<Node<T>> root, const T &val){
	if (root == nullptr) return nullptr;

	if (root->value() == val)
		return root;

	std::shared_ptr<Node<T>> left = findNode(root->left(), val);
	if (left != nullptr)
		return left;
	
	std::shared_ptr<Node<T>> right = findNode(root->right(), val);
	if (right != nullptr)
		return right;

	return nullptr;
}

int main() {
	shared_ptr<Node<char>> root(loadTree());
	printPreOrder(root);
	cout << endl << endl;

	// char val1 = 'd', val2 = 'g'; // b is ancestor
	// char val1 = 'a', val2 = 'i'; // a is ancestor
	// char val1 = 'a', val2 = 'm'; // NO ancestor
	// char val1 = 'b', val2 = 'm'; // NO ancestor
	char val1 = 'f', val2 = 'f';
	auto antecestor = getFirstCommonAncestor(root, val1, val2);
	if (antecestor != nullptr) {
		cout << "First Common Ancestor of node: \'" << val1 << "\' and \'" << val2 << "\' is: \t" << antecestor->value() << endl;
	}
	else {
		cout << "No common ancestor found" << endl;
	}


	auto node1 = findNode(root, val1);
	auto node2 = findNode(root, val2);
	antecestor = getFirstCommonAncestor2(root, root, node1, node2);
	if (antecestor != nullptr) {
		cout << "First Common Ancestor of node: \'" << val1 << "\' and \'" << val2 << "\' is: \t" << antecestor->value() << endl;
	}
	else {
		cout << "No common ancestor found" << endl;
	}

	return EXIT_SUCCESS;
}

