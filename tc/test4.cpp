/**
	B:5) Using the following code implement the following methods. 
	You may use a compiler to verify your results.

	a) Node::getNode returns a pointer to the first node in which Node::value matches
	the supplied argument "searchValue".  If includeThis is true then the first node's
	value is checked and the function may return this, if false, only a child node
	will be returned. Implement this method using a depth-first search.

	b) Node::getDepth returns an integer value indicating how many parents the current
	node has (a node does not have a parent if its parent pointer is set to 0). 
	Implement this method.

	c) OPTIONAL BONUS: Feel free to implement getNode as a breadth-first search.


	#include <vector>

	using namespace std;

	class Node {
		Node* parent;
		vector< Node* > children;
		int value;
	public:
		Node(int a_value):value(a_value),parent(0){}
		~Node(){for(int i = 0;i < children.size();++i){delete children[i];}}

		int getValue(){
			return value;
		}
		Node* addChild(const Node &child){
			children.push_back(new Node(child));
			children.back()->parent = this;
			return children.back();
		}
		Node* getNode(int searchValue, bool includeThis = false);
		int getDepth();
	};






	Programmer:	Michael Duarte
	Compile:	g++ test.cpp tools/debug_new.cpp -o test
					g++ test.cpp -o test
	Date:		October/2014
*/

#include <iostream> // std::cin, std::cout
#include <queue>    // std::queue
#include <vector>	// std::vector
#include <stack> 	//std::
#include "tools/debug_new.h"

// TO USE BREATH FIRST SEARCH uncomment next line;
#define _BREATH_FIRST_ 

using namespace std;

class Node {
	Node* parent;
	vector< Node* > children;
	int value;

public:
	Node(int a_value):value(a_value),parent(0){}
	~Node(){for(int i = 0;i < children.size();++i){delete children[i];}}

	int getValue(){
		return value;
	}

	Node* addChild(Node* child){
		children.push_back(child);
		children.back()->parent = this;
		return children.back();
	}

	Node* addChild(const Node &child){
		children.push_back(new Node(child));
		children.back()->parent = this;
		return children.back();
	}

	// check current node, if not the searched value, check its children
	// when no more children backtrace.
	static Node* depthFirstSearch(int &searchValue, Node* root){
		Node* aux;
		stack<Node*> toBeChecked;
		int len = root->children.size();

		//int iterations = 0;

		//push the root children to the stack, because we are not
		//interested in checking the root
		for(int i = len-1; i >= 0 ; i--){
			toBeChecked.push(root->children[i]);
		}		

		while(len){
			//iterations++;
			
			//check if the last node has the searchValue
			aux = toBeChecked.top();
			if(aux->value == searchValue){
				//cout<<"depthFirst iterations: " << iterations << endl;
				return aux;
			}

			//if it has a different value remove it from the stack
			toBeChecked.pop();
			
			//and add its children to be checked (LIFO)
			len = aux->children.size();
			for(int i = len-1; i >= 0 ; i--){
				toBeChecked.push(aux->children[i]);
			}

			//update the number of elements on stack
			len = toBeChecked.size();
		}
		//cout<<"depthFirst iterations: " << iterations << endl;

		//we couldn't find the searchValue
		return NULL;
	}

	//Check for the searchValue one level at the time
	static Node* breathFirstSearch(int searchValue, Node* root){
		Node* aux;
		queue<Node*> toBeChecked;
		int len = root->children.size();

		//int iterations = 0;

		//push the root children to the stack, because we are not
		//interested in checking the root
		for(int i = 0;  i < len ; i++){
			toBeChecked.push(root->children[i]);
		}		

		while(len){
			//iterations++;
			//check if the last node has the searchValue
			aux = toBeChecked.front();
			if(aux->value == searchValue){
				//cout<<"breathFist iterations: " << iterations << endl;
				return aux;
			}

			//if it has a different value remove it from the queue, continuing with
			// the other nodes already in the queue (FIFO)
			toBeChecked.pop();
			
			//and add its children to be checked
			len = aux->children.size();
			for(int i = 0;  i < len ; i++){
				toBeChecked.push(aux->children[i]);
			}

			//update the number of elements on stack
			len = toBeChecked.size();
		}
		//cout<<"breathFist iterations: " << iterations << endl;

		//we couldn't find the searchValue
		return NULL;
		
	}

	Node* getNode(int searchValue, bool includeThis = false){
		if(includeThis && value == searchValue)
			return this;

		#ifdef _BREATH_FIRST_
			return breathFirstSearch(searchValue, this);
		#else
			return depthFirstSearch(searchValue, this);
		#endif
	}

	int getDepth(){
		Node *aux = this;
		int depth = 0;
		while(aux->parent != 0){
			depth++;
			aux = aux->parent;
		}
		return depth;
	}

	//utility function to print a nodes' properties
	static void printNode(Node* root, bool recursive){

		Node *aux;
		int len = root->children.size();
		cout << "Value: " << root->value << ", children: " << len << " ->  ";
		for(int i = 0; i < len ; i++){
			cout << root->children[i]->value <<", ";
		}
		if (root->parent != NULL)
			cout << " Parent: " << root->parent->value;
		cout << endl;

		if(recursive)
			for(int i = 0; i < len ; i++)
				printNode(root->children[i], true);		
	}
};

int main(void) {

	Node** nodes = new Node*[20];
	for(int i = 0 ; i < 20 ; i++){
		nodes[i] = new Node(i+1);
	}

	nodes[11]->addChild(nodes[16]);

	nodes[4]->addChild(nodes[11]);
	nodes[4]->addChild(nodes[10]);
	nodes[4]->addChild(nodes[9]);

	nodes[1]->addChild(nodes[4]);
	nodes[1]->addChild(nodes[5]);

	nodes[6]->addChild(nodes[13]);
	nodes[6]->addChild(nodes[12]);

	nodes[2]->addChild(nodes[6]);

	nodes[18]->addChild(nodes[19]);

	nodes[14]->addChild(nodes[18]);
	nodes[14]->addChild(nodes[17]);

	nodes[7]->addChild(nodes[14]);

	nodes[8]->addChild(nodes[15]);

	nodes[3]->addChild(nodes[8]);
	nodes[3]->addChild(nodes[7]);

	nodes[0]->addChild(nodes[1]);
	nodes[0]->addChild(nodes[2]);
	nodes[0]->addChild(nodes[3]);


	//Node::printNode(nodes[0], true);

	cout << "LOOKING FOR VALUE 11... " << endl;
	Node* aux =  NULL;
	aux = nodes[0]->getNode(11, false);

	if(aux == NULL){
		cout << "Node not found:"<<endl;
	}
	else{
		cout << "Node found!, INFO: ";
		Node::printNode(aux, false);
		cout << "Depth (number of parents): "<< aux->getDepth() << endl;
	}

	//cout<< "Deleting  pointers" <<endl;
	// the destructor is in charge of destroying all of the children, so
	// destroying the root node is enough;
	delete nodes[0];

	//cout<< "deleting pointer to array of pointers" <<endl;
	delete[] nodes;

	return 0;
}