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
const int TOTAL_NODES = 4;
int matrix[TOTAL_NODES][TOTAL_NODES] = {0};

void addEdge(int i, int j, int weight, bool undirected = true){
	matrix[i][j] = weight;
	if (undirected)
		matrix[j][i] = weight;
}

int findMinPath(int node1, int node2, bool *visited){
	visited[node1] = true;
	for (int j = 0 ; j < TOTAL_NODES; ++j){
		if (visited[j] == false && matrix[node1][j]){
			if (j == node2)
				return matrix[node1][node2];
			int minPath = findMinPath(j, node2, visited);
			if (minPath != -1)
				return matrix[node1][j] + minPath;
		}
	}
	return -1;
}

int findMinPath(int node1, int node2){
	bool visited[TOTAL_NODES] = {false};
	return findMinPath(node1, node2, visited);
}

int sumOfAllPaths(){
	int sum = 0;
	for (int i = 0; i < TOTAL_NODES; ++i){
		for(int j = i+1; j < TOTAL_NODES; ++j){
			sum += findMinPath(i,j);
		}
	}
	return sum;
}

void printMatrix(){
	for(int i = 0 ; i < TOTAL_NODES; ++i){
		for(int j = 0 ; j < TOTAL_NODES; ++j){
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main(){
	printMatrix();
	addEdge(0, 1, 1);
	// addEdge(0, 2, 3);
	// addEdge(0, 3, 4);
	addEdge(1, 2, 2);
	addEdge(1, 3, 3);
	// addEdge(2, 3, 5);

	printMatrix();
	int c_d = findMinPath(2, 3);
	int a_d = findMinPath(0, 3);
	cout << "shortest path from C to D: "<< c_d << endl;
	cout << "shortest path from A to D: "<< a_d << endl; 
	cout << "sum of all paths in the graph: "<< sumOfAllPaths() << endl; 
	return 0;
}