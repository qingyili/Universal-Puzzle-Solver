//LinkedListQueue.cpp
#ifndef _LINKEDLISTQUEUE_CPP
#define _LINKEDLISTQUEUE_CPP

#include "LinkedListQueue.hpp"
#include <cstdlib> //for NULL
#include <cassert>
#include <iostream>
LinkedListQueue::LinkedListQueue()
{
    head = NULL;
    tail =NULL;
    size = 0;
}

void LinkedListQueue::add(PuzzleState *elem)
{
    //first element
    if(is_empty()){
        head->data= elem;
        tail =head;
        size =1;
    }else{
        //not first element
        node * temp = new node();
        temp->data = elem;
        tail ->next = temp;
        tail = tail->next;
    }
}

PuzzleState *LinkedListQueue::remove()
{
    assert(!is_empty());
    node * temp;
    PuzzleState * return_data;
    return_data = head->data;
    temp=head;
    head = head->next;
    delete temp;
    return return_data;
    
}

bool LinkedListQueue::is_empty()
{
    return (head == NULL);
}

LinkedListQueue::~LinkedListQueue()
{
  // TODO
}

#endif

