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

#include "TemplatedSharedTree.h"
	
int main(){
	using namespace std;
	using namespace Tree;
	
	vector<int> array = {0,1,2,3,4,5,6,7,8,9};
	shared_ptr<Node<int>> root = createTreeFromVector<int>(array, 0, array.size()-1);
	// printInOrder(root);

	// vector<vector<shared_ptr<Node<int>>>> listOfLists = getTreeAsVector(root);
	// printListsOfLists(listOfLists);
	return 0;
}