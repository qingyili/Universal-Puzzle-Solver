#ifndef _AVLDICT_CPP
#define _AVLDICT_CPP

//AVLDict.cpp
#include "AVLDict.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>

// An implementation of a dictionary ADT as an unsorted linked list.
//
AVLDict::AVLDict() {
  root = NULL;

  // Initialize array of counters for depth statistics
  depth_stats = new int[MAX_STATS]();
}

void AVLDict::destructor_helper(node * x) {
  if (x == NULL) return; // Nothing to destroy.
  destructor_helper(x->left);
  destructor_helper(x->right);
  delete x->key;
  delete x;
}

AVLDict::~AVLDict() {
  // Clean up the tree.
  // This is most easily done recursively.
  destructor_helper(root);

  // It's not good style to put this into a destructor,
  // but it's convenient for this assignment...
  cout << "Depth Statistics for find():\n";
  for (int i=0; i<MAX_STATS; i++)
    cout << i << ": " << depth_stats[i] << endl;
  delete [] depth_stats;
}

bool AVLDict::find_helper(node *r, string keyID, PuzzleState *&pred, int depth) {
  if (r==NULL) {
    if (depth<MAX_STATS) depth_stats[depth]++;
    return false; // Didn't find it.
  }
  if (keyID == r->keyID) {
    if (depth<MAX_STATS) depth_stats[depth]++;
    pred = r->data; // Got it!  Get the result.
    return true;
  }
  if (keyID < r->keyID) return find_helper(r->left, keyID, pred, depth+1);
  else return find_helper(r->right, keyID, pred, depth+1);
}

bool AVLDict::find(PuzzleState *key, PuzzleState *&pred) {
  return find_helper(root, key->getUniqId(), pred, 0);
}


bool AVLDict::update_height( node * x ) {
  //
  // Recalculates the height of x from the height of its children.
  // Returns true iff the height of x changes.
  //
    cout << "height before: " << height(x)<< endl;
    if(x == NULL) return false;
    int m = std::max(height(x->left), height(x->right)) + 1;
    if(height(x) != m){
        x->height = m;
        cout << "Up height after: " << height(x)<< endl;
        return true;
    }
  // :TODO: Write this function!
    return false;
}

void AVLDict::rotate_left(node *& a ) {
  // "rotates" the subtree rooted at a to the left (counter-clockwise)

// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// We will use this code when marking to be able to watch what
// your program is doing, so if you change things, we'll mark it wrong.
#ifdef MARKING_TRACE
std::cout << "Rotate Left: " << a->keyID << std::endl;
#endif
// End of "DO NOT CHANGE" Block

    node* temp = a->right;
    a->right = temp->left;
    temp->left = a;
    update_height(a);
    update_height(temp);
    a = temp;
}
void AVLDict::double_rotate_left(node *&a){
    assert(a != NULL);
    rotate_right(a->right);
    rotate_left(a);
    
}
void AVLDict::rotate_right( node *& b ) {
  // "rotates" the subtree rooted at b to the right (clockwise)

// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// We will use this code when marking to be able to watch what
// your program is doing, so if you change things, we'll mark it wrong.
#ifdef MARKING_TRACE
cout << "Rotate Right: " << b->keyID << endl;
#endif
// End of "DO NOT CHANGE" Block
cout << "Rotate Right: " << b->keyID << endl;
    node * temp = b->left;
    b->left = b->right;
    temp->right = b;
    update_height(b);
    update_height(temp);
    b = temp;
}

void AVLDict::double_rotate_right(node *&a){
    assert(a != NULL);
    rotate_left(a->left);
    rotate_right(a);
    
}

void AVLDict::balance(node *& x ) {
    int left = height(x->left);
    int right = height(x->right);
    if(abs(left -right) >1)
        if(right>left){
            if(height(x->right)==1+height(x->right->left))
                double_rotate_left(x);

            else rotate_left(x);
        }else{
    
            if(right<left){
                if(height(x->left) ==1+ height(x->left->right))
                    double_rotate_right(x);

                else rotate_right(x);
            }
        update_height(x);
    }
}
// You may assume that no duplicate PuzzleState is ever added.
void AVLDict::add_helper(AVLDict::node *&r, node*& toAdd){
    //Base case
    if(root==NULL){
        root = toAdd;
        return;
    }if(toAdd->keyID <root->keyID){
        add_helper(root->left,toAdd);
    }else add_helper(root->right,toAdd);
    if(update_height(r)) balance(r);
}

void AVLDict::add(PuzzleState *key, PuzzleState *pred) {
    node* temp = new node();
    temp->key= key;
    temp->data= pred;
    temp->keyID = key->getUniqId();
    temp->height = 0;
    add_helper(root, temp);
    //after add update height
    if(update_height(root)) balance(root);
}

#endif 
