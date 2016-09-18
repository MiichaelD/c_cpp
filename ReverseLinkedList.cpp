/*
	Description:	Given a linked list, write a function to reverse it.

	Programmer:		Michael Duarte

	Date:			Mid Oct, 2014.	
*/

#include <iostream>

using namespace std;

struct Node {
  int val;
  Node* next;
  Node(int v):val(v){}
};


void print(const Node *head){
	const Node *aux = head;
	if (aux){
		cout << aux->val;
		aux = aux->next;
		while (aux != nullptr){
			cout << " -> " <<aux->val;
			aux = aux->next;
		}
	}
	cout << endl;
}


Node* reverse(Node* head) {
    Node* oldHead = head;
    Node* newHead = head;
    
    while( oldHead->next != NULL){
        Node* nextNode = oldHead->next;
        oldHead->next = nextNode->next;
        nextNode->next = newHead;
        newHead = nextNode;
        print(newHead);
    }
    return newHead;
}

int main(){
	Node *head = new Node(1);
	Node *aux = head;
	for (int i = 2; i < 6; ++i){
		aux->next = new Node(i);
		aux = aux->next;
	}
	print(head);
	head = reverse(head);
}