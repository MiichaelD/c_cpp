/*
	Description:	4.12 Paths with sums: You are given a binary tree which each node
					contains an integer value (which might be positive or negative).
					Design an algorithm to count the number of paths that sum to a given
					value. The path does not need to start or end at the root or a leaf,
					but it must go downwards (traveling only from parent nodes to child nodes).

	Programmer:		Michael Duarte

	Date:			Sept 6, 2016.
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
std::shared_ptr<Node<T>> createTreeFromVector(vector<int> &array, int start, int end){
	if (start > end)
		return shared_ptr<Node<T>>(nullptr);
	int mid = (end + start) / 2;
	shared_ptr<Node<T>> node = make_shared<Node<T>>(array[mid]);
	node->addLeftNode( createTreeFromVector<T>(array, start, mid-1) );
	node->addRightNode( createTreeFromVector<T>(array, mid+1, end) );
	return node;
}

template<class T>
std::shared_ptr<Node<T>> createTree(){
	vector<int> array = {3,3,-2};
	shared_ptr<Node<int>> sub3 = createTreeFromVector<int>(array, 0, array.size()-1);

	auto sub5 = std::make_shared<Node<T>>(5);
	sub5->addLeftNode(sub3);
	sub5->addRightNode(2);
	sub5->right()->addRightNode(1);

	auto root = std::make_shared<Node<T>>(10);
	root->addLeftNode(sub5);
	root->addRightNode(-3);
	root->right()->addRightNode(11);

	return root;
}

int getPathCountOrDefault(std::unordered_map<int,int> &map, int sum, int defaultVal = 0){
	auto foundVal = map.find(sum);
	if (foundVal == map.end()){
		return defaultVal;
	}
	return foundVal->second;
}

void incrementMap(std::unordered_map<int,int> &map, int sum, int delta){
	int newCount = getPathCountOrDefault(map, sum) + delta;
	if (newCount == 0){
		map.erase(sum);
	} else {
		map[sum] = newCount;
	}
}

template<class T>
int getPathsWithSums(std::shared_ptr<Node<T>> root, int targetSum,
	std::unordered_map<int, int> &map, int runningSum = 0){
	if (root == nullptr)
		return 0;

	runningSum += root->value();
	// if we find previous nodes with runningsum == desiredsum we have found a path
	// adding to target sum.
	int desiredSum = runningSum - targetSum; 
	int total = getPathCountOrDefault(map, desiredSum);
	// if (total){
	// 	cout << "\tElement: " << root->value() << " found desired: " << desiredSum << endl; 
	// }
	if (runningSum == targetSum)
		++total;

	incrementMap(map, runningSum, 1);
	total += getPathsWithSums(root->left(), targetSum, map, runningSum);
	total += getPathsWithSums(root->right(), targetSum, map, runningSum);
	incrementMap(map, runningSum, -1);

	return total;
}

template<class T>
int getPathsWithSums(std::shared_ptr<Node<T>> root, int targetSum){
	unordered_map<int, int> map;
	return getPathsWithSums(root, targetSum, map);
}

int main(){
	shared_ptr<Node<int>> root = createTree<int>();
	printInOrder(root);
	cout << endl;
	
	for (int i : {8, 5, 1, 6}){
		cout << "Number of paths with sum = " << i << ": " << getPathsWithSums(root, i) << endl; 
	}
	return 0;
}


		//		 					10 - 10
					
		// 				5  - 15					-3  - 7

		// 		3 - 18			2 - 17					11 - 18

		// 3 - 21	 -2 - 16			1 - 18