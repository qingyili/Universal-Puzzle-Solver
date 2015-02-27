#ifndef _ARRAYQUEUE_CPP
#define _ARRAYQUEUE_CPP

//ArrayQueue.cpp

#include "ArrayQueue.hpp"
#include <cstdlib> //for NULL
#include <cassert>
#include <iostream>
using namespace std;

// 221 STUDENTS:
//
// This skeleton file (along with the .hpp) is
// here to help get you started, but you are
// free to change function signatures, etc.
// as long as ArrayQueue is some subtype
// of BagOfPuzzleStates
ArrayQueue::ArrayQueue()
{
  // Constructor: initialize member variables
  //              and do any other initialization
  //              needed (if any)
  // TODO: implement constructor
    head = 0;
    tail = 0;
    capacity = 1000;
    array= new PuzzleState*[capacity];
}
void ArrayQueue::add(PuzzleState *elem)
{
  // TODO: uncomment parameter name (commented out so you don't get a warning)
  // TODO: implement add method
    ensure_capacity(size);
    //if empty
    if(is_empty()){
        array[head]= elem;
        tail= head;
    }else{
        array[tail] = elem;
        tail= (tail+1) % size;
    }
}

PuzzleState *ArrayQueue::remove()
{
    PuzzleState * r;
    r = array[head];
    head = (head +1)% size;
    return r;
  // TODO: implement remove method
}

bool ArrayQueue::is_empty()
{
    return head == tail;
  // TODO: implement is_empty method
}

// TODO: implement ensure_capacity (but leave this to last.. just start with lots of capacity!)
void ArrayQueue::ensure_capacity(int n)
{
  if (!is_empty()) {
    // Make plenty of room.
    int target_capacity = (n > 2*capacity+1) ? n : (2*capacity+1); /* TODO: the larger of n and twice the current capacity */;

    // TODO: Set the current array aside and make room for the new one.
      PuzzleState **oldarray =array;
      array = new PuzzleState*[target_capacity];
      
    // TODO: Copy each element of the old array over.
      for(int i =0; i<size; i++){
          array[i]= oldarray[i];
      }
      
    // Update front carefully as you go!  Can you just use front++?

    // TODO: Fix front and back and capacity so they correspond to the new array.
      capacity= target_capacity;

    // TODO: Delete the old array.
      delete [] oldarray;
  }
}


ArrayQueue::~ArrayQueue()
{
  // TODO: implement the destructor
    delete [] array;

  // do any cleanup like deallocating
  // any dynamically allocated memory
}

#endif
