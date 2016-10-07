#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <ctime>
#include <unordered_map>

using namespace std;

template<class T>
class Heap{
protected:
    vector<T> items;
    int size = 0;
    
    virtual bool heapDownComp(T itemA, T itemB) = 0;
    virtual bool heapUpComp(T itemA, T itemB) = 0;
    virtual ~Heap(){};
    
    int getLeftChildIndex(int parentIndex) {
        return 2 * parentIndex + 1;
    }
    
    int getRightChildIndex(int parentIndex) {
        return 2 * parentIndex + 2;
    }
    
    int getParentIndex(int childIndex) {
        return (childIndex - 1) / 2;
    }
    
    bool hasLeftChild(int index) {
        return getLeftChildIndex(index) < size;
    }
    
    bool hasRightChild(int index) {
        return getRightChildIndex(index) < size;
    }
    
    bool hasParent(int index) {
        return getParentIndex(index) >= 0;
    }
    
    T leftChild(int index) {
        return items[getLeftChildIndex(index)];
    }
    
    T rightChild(int index) {
        return items[getRightChildIndex(index)];
    }
    
    T parent(int index) {
        return items[getParentIndex(index)];
    }
    
    void swap(T indexOne, T indexTwo) {
        T temp = items[indexOne];
        items[indexOne] = items[indexTwo];
        items[indexTwo] = temp;
    }    
    
    void heapifyDown() {
        int index = 0;
        while(hasLeftChild(index)) {
            int smallerChildIndex = (hasRightChild(index) 
                && heapDownComp(rightChild(index), leftChild(index)) )
                ? getRightChildIndex(index)
                : getLeftChildIndex(index);
            
            
            if(heapDownComp(items[index], items[smallerChildIndex])) {
                break;
            } else{
                swap(index, smallerChildIndex);
            }
            index = smallerChildIndex;
        }
    }
    
    void heapifyUp() {
        int index = size - 1;
        while(hasParent(index) &&  heapUpComp(parent(index),items[index]) ) {
            swap(getParentIndex(index), index);
            index = getParentIndex(index);
        }
    }    
    
    void forceNotEmpty(const string &methodName) const {
        if(isEmpty()) {
            throw std::underflow_error (
                "You cannot perform '" + methodName + "' on an empty Heap."
            );
        }
    }

public:
    int getSize() const { return size; }

    bool isEmpty() const { return size == 0; }
    
    T peek() {
        forceNotEmpty("peek");
        return items[0];
    }
    
    T poll() {
        // Throws an exception if empty.
        forceNotEmpty("poll");
        // Else, not empty
        int item = items[0];
        items[0] = items[--size];

        heapifyDown();
        return item;
    }
    
    void add(T item) {        
        // Insert value at the next open location in heap
        if (size < items.size()){
            items[size] = item;
        } else{
            items.push_back(item);
        }
        ++size;
        // Correct order property
        heapifyUp();
    }
    
};

template<class T = int>
class MinHeap : public Heap<T>{
    virtual bool heapDownComp(T itemA, T itemB) override{
        return itemA < itemB; //minHeap
    }
    
    virtual bool heapUpComp(T itemA, T itemB) override{
        return itemA > itemB;// minHeap
    }
};

template <class T = int>
class MaxHeap : public Heap<T>{
    virtual bool heapDownComp(T itemA, T itemB) override{
        return itemA > itemB;
    }
    
    virtual bool heapUpComp(T itemA, T itemB) override{
        return itemA < itemB;
    }
};



// Function implementing algorithm to find median so far.
template <class T = int>
double getRunningMedian(T e, double &m, Heap<T> &l, Heap<T> &r){
    // Are heaps balanced? If yes, sig will be 0
    int sig = signum(l.getSize(), r.getSize());
    // cout << "\tSignum: " << sig << endl;
    switch(sig){
    case 1: // There are more elements in left (max) heap
        if( e < m ){ // current element fits in left (max) heap
            // Remore top element from left heap and
            // insert into right heap
            r.add(l.poll());
            // current element fits in left (max) heap
            l.add(e);
        } else {
            // current element fits in right (min) heap
            r.add(e);
        }
 
        // Both heaps are balanced
        m = average(l.peek(), r.peek());
        break;
 
    case 0: // The left and right heaps contain same number of elements
        if( e < m ){ // current element fits in left (max) heap
            l.add(e);
            m = l.peek();
        } else {
            // current element fits in right (min) heap
            r.add(e);
            m = r.peek();
        }
        break;
 
    case -1: // There are more elements in right (min) heap
        if( e < m ){ // current element fits in left (max) heap
            l.add(e);
        } else {
            // Remove top element from right heap and
            // insert into left heap
            l.add(r.poll());
            // current element fits in right (min) heap
            r.add(e);
        }
        // Both heaps are balanced
        m = average(l.peek(), r.peek());
        break;
    }
    // No need to return, m already updated
    return m;
}



int main(){
    srand(time(NULL));
    int range = 6;
    // Insert random values into heaps:
    MinHeap<int> minHeap;
    MaxHeap<int> maxHeap;
    for(int i = 0; i < range; i++) {
        int value = rand() % 100;
        minHeap.add(value);
        maxHeap.add(value);
        cout << value << " ";
    }
    
    // Remove values from heaps:
    cout << "\n\nPoll Values:\n------------\nMinHeap MaxHeap" << endl;
    for(int i = 0; i < range; i++) {
        printf("  %-12d", minHeap.poll());
        printf("%-6d\n", maxHeap.poll());
    }
    return 0;
}