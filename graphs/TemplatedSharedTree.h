/*
	Description:	Full Templated Tree implementation.

	Programmer:		Michael Duarte

	Date:			Sep 2, 2016.-
	
*/
#ifndef TEMPLATEDTREE_H
#define TEMPLATEDTREE_H

#include <vector>
#include <memory>

namespace Tree{

	template<class T> class Node{
	private:
		T m_value;
		std::shared_ptr<Node> m_left, m_right;
		
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
	std::shared_ptr<Node<T>> createTreeFromVector(std::vector<int> &array, int start, int end);

	//-------------------- Print tree traversals -----------------------------//
	template<class T> void printPreOrder(std::shared_ptr<Node<T>> root);

	template<class T> void printInOrder(std::shared_ptr<Node<T>> root);

	template<class T> void printPostOrder(std::shared_ptr<Node<T>> root);

	template<class T>
	std::shared_ptr<Node<T>> findNode(std::shared_ptr<Node<T>> root, const T &val);


	//-------------------- Check Subtree -----------------------------//
	template<class T>
	bool matchSubTree(std::shared_ptr<Node<T>> t1, std::shared_ptr<Node<T>> t2);

	template<class T> 
	bool isSubtree(std::shared_ptr<Node<T>> t1, std::shared_ptr<Node<T>> t2);



	//--------------------  Vector of vectors -----------------------------//
	template<class T>
	std::vector<std::vector<std::shared_ptr<Node<T>>>> getTreeAsVector(std::shared_ptr<Node<T>> root);

	template<class T>
	void printListsOfLists(std::vector<std::vector<std::shared_ptr<Node<T>>>> &listOfLists);



	//-------------------- Check is Balanced -----------------------------//
	template<class T> int getHeight(std::shared_ptr<Node<T>> root);

	template<class T> int getHeightMemo(std::shared_ptr<Node<T>> root, bool clearMemo = false);

	template<class T> bool isBalanced(std::shared_ptr<Node<T>> root);



	//-------------------- Validate is a BST -----------------------------//
	template<class T>
	bool isBST1(std::shared_ptr<Node<T>> root);

	template<class T>
	bool isBST(std::shared_ptr<Node<T>> root, const T *min = nullptr, const T *max = nullptr);


	//-------------------- First common ancestor -----------------------------//
	template<class T>
	bool getNodesPathToRoot(std::shared_ptr<Node<T>> node, const T &val, std::vector<std::shared_ptr<Node<T>>> &path);

	template<class T>
	std::vector<std::shared_ptr<Node<T>>> getPathToRoot(std::shared_ptr<Node<T>> node, const T &val);

	template<class T>
	std::shared_ptr<Node<T>> getFirstCommonAncestor(std::shared_ptr<Node<T>> root, const T &val1, const T&val2);

	template<class T>
	std::shared_ptr<Node<T>> getFirstCommonAncestor2(std::shared_ptr<Node<T>> originalRoot,
		std::shared_ptr<Node<T>> root, std::shared_ptr<Node<T>> p, std::shared_ptr<Node<T>> q);




	//------------------------------------ DEFINITIONS ---------------------------------------//

	template<class T>
	std::shared_ptr<Node<T>> createTreeFromVector(std::vector<int> &array, int start, int end){
		if (start > end)
			return std::shared_ptr<Node<T>>(nullptr);
		int mid = (end + start) / 2;
		std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>(array[mid]);
		node->addLeftNode( createTreeFromVector<T>(array, start, mid-1) );
		node->addRightNode( createTreeFromVector<T>(array, mid+1, end) );
		return node;
	}

	//-------------------- Print Tree traversals -----------------------------//
	template<class T>
	void printPreOrder(std::shared_ptr<Node<T>> root){
		if (root == nullptr)
			return;

		std::cout << root->value() << " ";
		printPreOrder(root->left());
		printPreOrder(root->right());
	}

	template<class T>
	void printInOrder(std::shared_ptr<Node<T>> root){
		if (root == nullptr)
			return;

		printInOrder(root->left());
		std::cout << root->value() << " ";
		printInOrder(root->right());
	}

	template<class T>
	void printPostOrder(std::shared_ptr<Node<T>> root){
		if (root == nullptr)
			return;

		printPostOrder(root->left());
		printPostOrder(root->right());
		std::cout << root->value() << " ";
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

	//-------------------- Check SubTree -----------------------------//
	// Check if 2 subTrees are identical matches.
	template<class T>
	bool matchSubTree(std::shared_ptr<Node<T>> t1, std::shared_ptr<Node<T>> t2){
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
	// once it is found, compare both subTrees match.
	template<class T> 
	bool isSubtree(std::shared_ptr<Node<T>> t1, std::shared_ptr<Node<T>> t2){
		if ( (t1 == nullptr || t2 == nullptr) )
			return false;

		if (t1->value() == t2->value() && matchSubTree(t1, t2))
			return true;

		return isSubTree(t1->left(), t2) || isSubTree(t1->right(), t2);
	}

	//--------------------  Vector of vectors -----------------------------//
	// Using the recently created lists to iterate in order. We don't have to keep track
	// of an extra data structure like we do in the first implementation.
	template<class T>
	std::vector<std::vector<std::shared_ptr<Node<T>>>> getTreeAsVector(std::shared_ptr<Node<T>> root){
		std::vector<std::vector<std::shared_ptr<Node<T>>>> result;
		result.emplace_back();
		if (root != nullptr)
			result.back().push_back(root);

		while(result.back().size()){
			result.emplace_back();
			std::vector<std::shared_ptr<Node<T>>> &parents = result[result.size()-2];
			for (auto child : parents){
				if(child->left() != nullptr)
					result.back().push_back(child->left());
				if(child->right() != nullptr)
					result.back().push_back(child->right());
			
			}
		}
		if (result.back().empty())
			result.pop_back();
		return result;
	}

	template<class T>
	void printListsOfLists(std::vector<std::vector<std::shared_ptr<Node<T>>>> &listOfLists){
		for (int i = 0; i < listOfLists.size(); ++i){
			std::cout << "List: " << i << " has: "; 
			for (int j = 0; j < listOfLists[i].size(); ++j){
				std::cout << listOfLists[i][j]->value() << " ";
			}
			std::cout << std::endl;
		}
	}


	//-------------------- Check is Balanced -----------------------------//

	template<class T>
	int getHeight(std::shared_ptr<Node<T>> root){
		if (root == nullptr)
			return -1;

		return std::max(getHeight(root->left()), getHeight(root->right())) + 1;
	}

	template<class T>
	int getHeightMemo(std::shared_ptr<Node<T>> root, bool clearMemo = false){
		static std::unordered_map<Node<T>*, int> heightMap;
		if (clearMemo)
			heightMap.clear();

		if (root == nullptr)
			return -1;

		int leftHeight, rightHeight;
		if (heightMap.find(root.get()) != heightMap.end())
			leftHeight = heightMap[root.get()];
		else{
			heightMap[root.get()] = leftHeight = getHeight(root->left());
		}

		if (heightMap.find(root.get()) != heightMap.end())
			rightHeight = heightMap[root.get()];
		else{
			heightMap[root.get()] = rightHeight = getHeight(root->right());
		}
		return std::max(leftHeight, rightHeight) + 1;
	}

	template<class T>
	bool isBalanced(std::shared_ptr<Node<T>> root){
		if (root == nullptr)
			return true;

		int heightDiff = abs(getHeightMemo(root->left()) - getHeightMemo(root->right()));
		if (heightDiff > 1){
			return false;
		} else {
			return isBalanced(root->left()) && isBalanced(root->right());
		}
	}


	//-------------------- Validate is a BST -----------------------------//


	// checking only immediate children is not enough!
	// i.e.:
	//				(20)
	//			   /	\
	//			(10)	 (30)
	//			   \
	//				(25)
	//
	template<class T>
	bool isBST1(std::shared_ptr<Node<T>> root){
		if (root == nullptr)
			return true;


		if (root->left() != nullptr){
			if (root->left()->value() > root->value()){
				std::cout << "\t" << root->left->value() << " > " << root->value() << std::endl; 
				return false;
			}
			if (!isBST1(root->left()))
				return false;
		}
		if (root->right() != nullptr){
			if (root->right()->value() <= root->value()){
				std::cout << "\t" <<  root->right()->value() << " <= " << root->value() << std::endl;
				return false;
			}
			if (!isBST1(root->right()))
				return false;
		}
		return true;
	}

	template<class T>
	bool isBST(std::shared_ptr<Node<T>> root, const T *min = nullptr, const T *max = nullptr){
		if (root == nullptr)
			return true;


		if ( (min != nullptr && root->value() <= *min) || (max != nullptr && root->value() > *max) )
			return false;

		if (! (isBST(root->left(), min, &root->value()) && isBST(root->right(), &root->value(), max)) )
			return false;

		return true;
	}

	//-------------------- First common ancestor -----------------------------//
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
		std::vector<std::shared_ptr<Node<T>>> path;
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
	// both nodes when we are in the real Tree root, we return nullptr, that is,
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
			// if we are on the original Tree root and we only found one node in either
			// subTree, there is no ancestor.
			return originalRoot == root ? nullptr : (left != nullptr ? left : right); // return non-null value
		}
	}

};


#endif //TEMPLATEDTREE_H