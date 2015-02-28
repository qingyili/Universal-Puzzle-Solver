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
    int i=0;
    while(heap.at(i)<elem)
        i++;
    heap.insert(heap.begin()+i, elem);
}

PuzzleState * HeapPriorityQueue::remove() {
  // TODO
    PuzzleState* temp = heap.front();
    heap.erase(heap.begin());
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


#endif
