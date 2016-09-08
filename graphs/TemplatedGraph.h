/*
	Description:	Templated graph implementation.

	Programmer:		Michael Duarte

	Date:			Sep 2, 2016.-
	
*/

#include <vector>
#include <queue>
#include <memory>

enum class State { kUnvisited, kVisited, kVisiting };

struct Edge{
	int nodeIndex;
	int dist;
	Edge(int index, int d):nodeIndex(index),dist(d){}
};

template<typename T = int>
struct Node{
	T value;
	std::vector<Edge> children;
	int id;
	Node(const T &val, int ind):value(val),id(ind){}
};

template<typename T = int>
class Graph{
	private:
	int index = -1;

	public: 
	std::vector<Node<T>> nodes;

	Node<T> &getNode(int id){
		if (id < 0 || id >= nodes.size())
			throw "Index out of bounds while getting node.";
		return nodes[id];
	}

	template<typename... Args>
	void addNode(Args&&... args){
		nodes.emplace_back(std::forward<Args>(args)..., ++index);
		// cout << "Node " << index << ") added with value: " << nodes[index].value << endl; 
	}

	bool addEdge(int n1Index, int n2Index, int dist, bool bidirectional = true){
		if (n1Index < 0 || n1Index > nodes.size() || 
			n2Index < 0 || n2Index > nodes.size() ) 
			return false;

		nodes[n1Index].children.emplace_back(n2Index, dist);
		if (bidirectional)
			nodes[n2Index].children.emplace_back(n1Index, dist);
		return true;
	}

	bool areNodesConnected(int startIndex, int endIndex){
		if (startIndex == endIndex)
			return true;

		std::vector<State> states(nodes.size(), State::kUnvisited);	
		std::queue<int> nodeQueue;
		states[startIndex] = State::kVisiting;
		nodeQueue.push(startIndex);
		while(!nodeQueue.empty()){
			Node<T> &aux = nodes[nodeQueue.back()];
			nodeQueue.pop();
			for (Edge &edge : aux.children){
				if (states[edge.nodeIndex] == State::kUnvisited){
					if (edge.nodeIndex == endIndex)
						return true;
					states[edge.nodeIndex] = State::kVisiting;
					nodeQueue.push(edge.nodeIndex);
				}
			}
			states[aux.id] = State::kVisited;
		}
		return false;
	}


	bool areNodesConnected(Node<T> *start, Node<T> *end){
		if (start == end)
			return true;

		std::vector<State> states(nodes.size(), State::kUnvisited);	
		std::queue<int> nodeQueue;
		states[start->id] = State::kVisiting;
		nodeQueue.push(start->id);
		while(!nodeQueue.empty()){
			Node<T> &aux = nodes[nodeQueue.back()];
			nodeQueue.pop();
			for (Edge &edge : aux.children){
				if (states[edge.nodeIndex] == State::kUnvisited){
					if (edge.nodeIndex == end->id)
						return true;
					states[edge.nodeIndex] = State::kVisiting;
					nodeQueue.push(edge.nodeIndex);
				}
			}
			states[aux.id] = State::kVisited;
		}
		return false;
	}

};