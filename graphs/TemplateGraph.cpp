/*
	Description:	4.1 Route Between Nodes: Given a directed graph, design an
					algoritm to find out whether there is a route between 2 nodes.
					
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
};

template<typename T>
bool addEdge(Graph<T> *g, int n1Index, int n2Index, int dist, bool bidirectional = true){
	if (n1Index < 0 || n1Index > g->nodes.size() || 
		n2Index < 0 || n2Index > g->nodes.size() ) 
		return false;

	g->nodes[n1Index].children.emplace_back(n2Index, dist);
	if (bidirectional)
		g->nodes[n2Index].children.emplace_back(n1Index, dist);
	return true;
}

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
	Graph<int> g;
	g.addNode(1);
	g.addNode(2);
	g.addNode(3);
	g.addNode(4);
	g.addNode(5);
	g.addNode(6);

	addEdge(&g, 0, 1, 1);
	addEdge(&g, 2, 3, 3);
	addEdge(&g, 2, 4, 2);
	addEdge(&g, 4, 5, 4);

	cout << g.nodes[5].id << endl;
	bool connected = areNodesConnected(&g, &g.nodes[5], &g.nodes[3]);
	cout << "Are Nodes 6 and 4 connected? " << (connected ? "Yes" : "No") << endl; 


	return 0;
}
