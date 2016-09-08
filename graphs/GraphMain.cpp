#include "TemplateGraph.h"
#include <iostream>

using namespace std;

int main(){
	Graph<int> g;
	g.addNode(1);
	g.addNode(2);
	g.addNode(3);
	g.addNode(4);
	g.addNode(5);
	g.addNode(6);

	g.addEdge(0, 1, 1);
	g.addEdge(2, 3, 3);
	g.addEdge(2, 4, 2);
	g.addEdge(4, 5, 4);

	cout << "Node " << g.nodes[5].id << " has value: " << g.nodes[5].value << endl;
	bool connected = g.areNodesConnected(5, 3);
	cout << "Are Nodes 6 and 4 connected? " << (connected ? "Yes" : "No") << endl; 


	return 0;
}
