/*
  Name:         TreeLevelsSum.cc
  Description:  Sum up the levels of a tree
  Example:
    Input:
           3
         / | \
       1   5  10
      /   / \   \ 
     6   2   4   7
        /       /
       8       9

    Output:    3, 16, 19, 8

  Programmer:		Michael Duarte
  Date:	     		Aug 28, 2018.
*/

#include <iostream>
#include <iomanip>      // std::setfill, std::setw
#include <vector>
#include <queue>
#include <utility>      // std::pair and std::make_pair
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

Node * createTree() {
  Node* n1 = new Node(1);
  Node* n2 = new Node(2);
  Node* n3 = new Node(3);
  Node* n4 = new Node(4);
  Node* n5 = new Node(5);
  Node* n6 = new Node(6);
  Node* n7 = new Node(7);
  Node* n8 = new Node(8);
  Node* n9 = new Node(9);
  Node* n10 = new Node(10);
  Node* root = n3;
  root->children.push_back(n1);
  root->children.push_back(n5);
  root->children.push_back(n10);
  n1->children.push_back(n6);
  n5->children.push_back(n2);
  n5->children.push_back(n4);
  n10->children.push_back(n7);
  n2->children.push_back(n8);
  n7->children.push_back(n9);
  return root;
}

void printTreeIndex(const vector<int> &sumVector) {
  cout << "Sums per level: \n[";
  for (int sum : sumVector) {
    cout << sum << ", "; 
  }
  cout << "]" << endl;
}

void processLevelSums(const Node *node, int level, vector<int> &sumVector) {
  if (sumVector.size() == level) {
    sumVector.push_back(node->data);
  } else {
    sumVector[level] += node->data;
  }

  for (Node *child : node->children) {
    processLevelSums(child, level + 1, sumVector);
  }
}

vector<int> getSumVectorRecursively(const Node *root) {
  vector<int> sumVector;
  processLevelSums(root, 0, sumVector);
  return sumVector;
}

vector<int> getSumVectorIteratively(const Node *root) {
  vector<int> sumVector;
  queue<pair<const Node*, int>> nodeLevelQueue;
  nodeLevelQueue.push(make_pair(root, 0));
  while(!nodeLevelQueue.empty()) {
    auto &pair = nodeLevelQueue.front();
    nodeLevelQueue.pop();
    if (sumVector.size() == pair.second) {
      sumVector.push_back(pair.first->data);
    } else {
      sumVector[pair.second] += pair.first->data;
    }
    for (Node *child : pair.first->children) {
      nodeLevelQueue.push(make_pair(child, pair.second + 1));
    }
  }
  return sumVector;
}

int main(){
  Node* root = createTree();
  vector<int> sumVector = getSumVectorIteratively(root);
  printTreeIndex(sumVector);
  delete root;
	return EXIT_SUCCESS;
}
