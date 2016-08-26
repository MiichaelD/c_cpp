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
#include <iomanip>

using namespace std;

struct Node;

struct Edge{
	Node *node;
	int dist;
	Edge(Node *n, int d):node(n),dist(d){}
};

struct Node{
	int value;
	vector<Edge> children;
	Node(int val):value(val){}
};


struct Graph{
	vector<Node> nodes;
};

bool addEdge(Graph *g, int n1Index, int n2Index, int dist, bool bidirectional = true){
	if (n1Index < 0 || n1Index > g->nodes.size() || 
		n2Index < 0 || n2Index > g->nodes.size() )
		return false;

	g->nodes[n1Index].children.emplace_back(&g->nodes[n2Index], dist);
	if (bidirectional)
		g->nodes[n2Index].children.emplace_back(&g->nodes[n1Index], dist);
	return true;
}

enum class State { kUnvisited, kVisited, kVisiting };


bool areNodesConnectedRec(Node *start, Node *end, vector<State> &states){
	if (start == end)
		return true;

	states[start->value] = State::kVisiting;
	for (Edge &edge : start->children){
		if (states[edge.node->value] == State::kUnvisited){
			if (edge.node == end)
				return true;
			states[edge.node->value] = State::kVisiting;
			return areNodesConnectedRec(edge.node, end, states);
		}
	}
	return false;
}

bool areNodesConnectedRec(Graph *g, Node *start, Node *end){
	if (start == end)
		return true;

	vector<State> states(g->nodes.size(), State::kUnvisited);	
	return areNodesConnectedRec(start, end, states);
}

bool areNodesConnected(Graph *g, Node *start, Node *end){
	if (start == end)
		return true;

	vector<State> states(g->nodes.size(), State::kUnvisited);	
	queue<Node*> nodes;
	states[start->value] = State::kVisiting;
	nodes.push(start);
	while(!nodes.empty()){
		Node * aux = nodes.back();
		nodes.pop();
		for (Edge &edge : aux->children){
			if (states[edge.node->value] == State::kUnvisited){
				if (edge.node == end)
					return true;
				states[edge.node->value] = State::kVisiting;
				nodes.push(edge.node);
			}
		}
		states[aux->value] = State::kVisited;
	}
	return false;
}



int main(){
	Graph g;
	g.nodes.emplace_back(1);
	g.nodes.emplace_back(2);
	g.nodes.emplace_back(3);
	g.nodes.emplace_back(4);
	g.nodes.emplace_back(5);
	// g.nodes.emplace_back(6);

	addEdge(&g, 0, 1, 1);
	addEdge(&g, 2, 3, 3);
	addEdge(&g, 2, 4, 2);
	addEdge(&g, 4, 5, 4);

	bool connected = areNodesConnectedRec(&g, &g.nodes[5], &g.nodes[3]);
	cout << "Are Nodes 6 and 4 connected? " << (connected ? "Yes" : "No") << endl; 


	return 0;
}