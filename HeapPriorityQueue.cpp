//HeapPriorityQueue.cpp
#ifndef _HEAPPRIORITYQUEUE_CPP
#define _HEAPPRIORITYQUEUE_CPP

#include "HeapPriorityQueue.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>

HeapPriorityQueue::HeapPriorityQueue() {
  // TODO
    //?nothing to do not dynamicall allocated
}

HeapPriorityQueue::~HeapPriorityQueue() {
  // TODO
    // nothing to clean because not dynamicall allocated
}

void HeapPriorityQueue::add(PuzzleState *elem) {
  // TODO
    heap.push_back(elem);
    int s = (int) heap.size() -1;
    swapup(s);
}

PuzzleState * HeapPriorityQueue::remove() {
  // TODO
    PuzzleState* temp = heap.front();
    heap[0]= heap.back();
    heap.pop_back();
    swapdown(0);
    return temp;
}


PuzzleState *HeapPriorityQueue::get_next() {
  // TODO
    return heap.front();
}

bool HeapPriorityQueue::is_empty() {
  // TODO
    return (heap.size()==0);
}

void HeapPriorityQueue::swapup(int ix){
    if (ix < 1) return;
    int parent = (ix - 1) / 2;
    if(heap[ix]->getBadness() < heap[parent]->getBadness()){
        PuzzleState *temp = heap[ix];
        heap[ix] = heap[parent];
        heap[parent] = temp;
        swapup(parent);
        
    }
    
}

void HeapPriorityQueue::swapdown(int ix){
    int leftChild = (2 * ix) + 1;
    int rightChild = (2 * ix) + 2;
    int min = ix;
    int size = (int) heap.size();
    if (leftChild < size && heap[leftChild]->getBadness() < heap[min]->getBadness())
        min = leftChild;
    if (rightChild < size && heap[rightChild]->getBadness() < heap[min]->getBadness())
        min = rightChild;
    if (min != ix) {
        
        PuzzleState *temp = heap[ix];
        heap[ix] = heap[min];
        heap[min] = temp;
        swapdown(min);
    }
}


#endif
