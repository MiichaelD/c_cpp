/*
	Name:	        TreeIndex.
  Description:   Given a tree (not a binary tree), convert it to an array of TreeIndex.  
    The `treeIndex` of the TreeIndex is the index of the `treeNode`'s parent in the array.
    If the `treeNode` doesn't have a parent (ie: it is the root), then the `treeIndex` is the index
    of that node's index in the array.

    For example:
           N1
          /  \
        N2    N3       => One possible array is [ N1, N2, N3, N4, N5, N6]
      / | \               You can construct the array anyway you like.
    N4  N5  N6            Then the result is [ (N1, 0), (N2, 0), (N3, 0), (N4, 1), (N5, 1), (N6, 1)]
    
  Explanation:
    N1 is root, so it use its own index, thereforem (N1, 0).
    N2's parent is N1, so it use N1's index, therefore (N2, 0).
    N3's parent is N1, so it use N1's index, therefore (N3, 0).
    N4's parent is N2, so it use N2's index, therefore (N4, 1).
    N5's parent is N2, so it use N2's index, therefore (N5, 1).
    N6's parent is N2, so it use N2's index, therefore (N6, 1).


	Programmer:		Michael Duarte
	Date:	     		Aug 23, 2018.
*/

#include <iostream>
#include <iomanip>      // std::setfill, std::setw
#include <vector>
#include <cmath>

using namespace std;

class Node {
  public:
  int data;
  vector<Node*> children;

  Node(int val) : data(val) {};
  ~Node() {
    for (Node *child : children) {
      delete child;
    }
    children.clear();
    // cout << "Node " << data << ", was deleted" << endl;
  }
};

class TreeIndex {
  public:
  int treeIndex;
  const Node* treeNode;
  TreeIndex(int index, const Node *node) : treeIndex(index), treeNode(node) {}
};

Node * createTree() {
  Node* root = new Node(1);
  Node* n2 = new Node(2);
  Node* n3 = new Node(3);
  Node* n4 = new Node(4);
  Node* n5 = new Node(5);
  Node* n6 = new Node(6);
  Node* n7 = new Node(7);
  Node* n8 = new Node(8);
  root->children.push_back(n2);
  root->children.push_back(n3);

  n2->children.push_back(n4);
  n2->children.push_back(n5);
  n2->children.push_back(n6);

  n3->children.push_back(n7);

  n5->children.push_back(n8);
  return root;
}


/** Appends the children in order recursively. Depth-first  */
void appendNodesChildrenToTreeIndexVec(
    vector<TreeIndex> &treeIndexVec, const Node *parent, int parentIndex) {
  if (parent == nullptr) {
    return;
  }

  for (Node *child : parent->children) {
    int childIndex = treeIndexVec.size();
    treeIndexVec.emplace_back(TreeIndex(parentIndex, child));
    appendNodesChildrenToTreeIndexVec(treeIndexVec, child, childIndex);
  }
}

/** Appends the children in order, then appends the children's children in order.*/
void appendNodesChildrenToTreeIndexVec2(
    vector<TreeIndex> &treeIndexVec, const Node *parent, int parentIndex) {
  if (parent == nullptr) {
    return;
  }

  int startIndex = treeIndexVec.size();
  for (Node *child : parent->children) {
    treeIndexVec.emplace_back(TreeIndex(parentIndex, child));
  }

  int children = 0;
  for (Node *child : parent->children) {
    int childIndex = startIndex + children;
    appendNodesChildrenToTreeIndexVec2(treeIndexVec, child, childIndex);
    ++children;
  }
}

vector<TreeIndex> createTreeIndex(const Node* root) {
  vector<TreeIndex> treeIndexVec;
  treeIndexVec.emplace_back(TreeIndex(0, root));
  appendNodesChildrenToTreeIndexVec2(treeIndexVec, root, 0);
  return treeIndexVec;
}

void printTreeIndex(const vector<TreeIndex> &treeIndexVec) {
  cout << "TreeIndex: \n[";
  for (TreeIndex treeIndex : treeIndexVec) {
    cout << " (N" << treeIndex.treeNode->data << ", " << treeIndex.treeIndex << ")"; 
  }
  cout << "]" << endl;
}

int main(){
  Node* root = createTree();
  vector<TreeIndex> treeIndexVec = createTreeIndex(root);
  printTreeIndex(treeIndexVec);
  delete root;
	return EXIT_SUCCESS;
}
