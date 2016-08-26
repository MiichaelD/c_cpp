/*
	Description:	4.7 Build Order: You are given a list of projects and a list of dependencies
					(which is a list of pairs of projects, where the second project is dependent
					on the first project). All of a project's dependencies must be built before
					the project is. Find a build order that will allow the project to be built.
					If there is no valid build order, return an error.

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

struct Edge{
	int nodeIndex;
	int dist;
	Edge(int index, int d):nodeIndex(index),dist(d){}
};

template<typename T = int>
struct Node{
	T value;
	vector<Edge> children;
	vector<Edge> childFrom;
	int id;
	Node(const T &val, int ind):value(val),id(ind){}
};

template<typename T = int>
class Graph{
	private:
	int index = -1;

	public: 
	vector<Node<T>> nodes;

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
		nodes[n2Index].childFrom.emplace_back(n1Index, dist);
		if (bidirectional){
			nodes[n2Index].children.emplace_back(n1Index, dist);
			nodes[n1Index].childFrom.emplace_back(n2Index, dist);
		}
		
		return true;
	}

	size_t size() const { return nodes.size();}
};


enum class State { kUnvisited, kVisited, kVisiting };


template<typename T>
bool areNodesConnected(Graph<T> *g, Node<T> *start, Node<T> *end){
	if (start == end)
		return true;

	vector<State> states(g->nodes.size(), State::kUnvisited);	
	queue<int> nodes;
	states[start->id] = State::kVisiting;
	nodes.push(start->id);
	while(!nodes.empty()){
		Node<T> &aux = g->nodes[nodes.back()];
		nodes.pop();
		for (Edge &edge : aux.children){
			if (states[edge.nodeIndex] == State::kUnvisited){
				if (edge.nodeIndex == end->id)
					return true;
				states[edge.nodeIndex] = State::kVisiting;
				nodes.push(edge.nodeIndex);
			}
		}
		states[aux.id] = State::kVisited;
	}
	return false;
}



int main(){
	Graph<char> g;
	g.addNode('A'); //0
	g.addNode('B');
	g.addNode('C');
	g.addNode('D');
	g.addNode('E');
	g.addNode('F'); //5
	g.addNode('G');

	g.addEdge(5, 2, 1, false);
	g.addEdge(5, 1, 1, false);
	g.addEdge(5, 0, 1, false);
	g.addEdge(2, 0, 1, false);
	g.addEdge(1, 0, 1, false);
	g.addEdge(1, 4, 1, false);
	g.addEdge(0, 4, 1, false);

	g.addEdge(3, 6, 1, false);

	vector<int> buildOrder(g.size());
	// bool connected = areNodesConnected(&g, &g.nodes[5], &g.nodes[4]);
	// cout << "Are Nodes 6 and 4 connected? " << (connected ? "Yes" : "No") << endl; 

	return 0;
}