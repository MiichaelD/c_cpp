/*
	Description:	8.6 Towers of Hanoi: In teh classic problem of Towers of Hanoi, you have
					3 towers and N disks of different sizes which can slide onto any tower.
					The puzzle starts with disks sorted in ascending order of size from top
					to bottom (i.e., each disk sits on top of an even larger one). You have 
					the following constraints:

					1) Only one disk can be moved at a time.
					2) A disk is slid off the top of one tower onto another tower.
					3) A disk cannot be placed on top of a smaller disk.

					Write a program to move the disks from the first tower to the last using
					stacks.

	Programmer:		Michael Duarte

	Date:			Sep 8, 2016.	
*/

#include <iostream>
#include <deque>
#include <memory>

using namespace std;

const int TOTAL_STACKS = 3;
deque<int> stacks[TOTAL_STACKS];

void printStacks(){
	for (int i = 0 ; i < TOTAL_STACKS; ++i){
		cout << i+1 << ": [";
		deque<int>::iterator it = stacks[i].begin();
		if (it != stacks[i].end()){
			cout << *it;
			while (++it != stacks[i].end()){
				cout << ", "<< *it;
			}
		}
		cout << "]" << endl;
	}
	cout << endl;
}

bool addValueToStack(int val, deque<int> &to){
	if (to.empty() || to.back() > val){
		to.push_back(val);
		return true;
	}
	return false;
}

bool addValueToStack(int val, int stack){
	return addValueToStack(val, stacks[stack]);
}

bool moveTopFromTo(deque<int> &from, deque<int> &to){
	if (from.size()){
		int aux = from.back();
		if (addValueToStack(aux, to)){
			from.pop_back();
			return true;
		}
	}
	return false;
}

bool moveTopFromTo(int source, int dest){
	return moveTopFromTo(stacks[source], stacks[dest]);
}

void moveDisksIt(){
	int origin = 0;
	int buffer = stacks[0].size() % 2 ? 1 : 2;
	int dest = stacks[0].size() % 2 ? 2 : 1;
	int totalDisks = stacks[0].size();
	int moves = (1 << totalDisks) - 1; // (2 ^ disks) -1
	for (int i = 0 ; i < moves; ++i){
		switch(i % TOTAL_STACKS){
			case 0:
				//any legal move between origin and destination
				if (!moveTopFromTo(origin, dest))
					moveTopFromTo(dest, origin);
				break;
			case 1:
				//any legal move between origin and buffer
				if (!moveTopFromTo(origin, buffer))
					moveTopFromTo(buffer, origin);
				break;
			case 2:
				//any legal move between destination and buffer
				if (!moveTopFromTo(dest, buffer))
					moveTopFromTo(buffer, dest);
		}
		printStacks();
	}
}

void moveDisksRec(int disks = stacks[0].size(), int source = 0, int dest = 2, int buffer = 1){
	if (disks){
		// move from origin to buffer, using destination as a buffer.
		moveDisksRec(disks-1, source, buffer, dest);
		// move from origin to destination.
		moveTopFromTo(source, dest);
		printStacks();	
		// move from buffer to destination, using origin as buffer.
		moveDisksRec(disks-1, buffer, dest, source);
	}
}

int main(){
	stacks[0] = {6,5,4,3,2,1,0};
	// stacks[0] = {3, 2, 1};
	printStacks();
	moveDisksRec();
	// printStacks();	
	return 0;
}