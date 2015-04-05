#ifndef _LINEARHASHDICT_CPP
#define _LINEARHASHDICT_CPP

//LinearHashDict.cpp
#include "LinearHashDict.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>

// An implementation of the dictionary ADT as a hash table with linear probing
//

const int LinearHashDict::primes[] = {53, 97, 193, 389, 769, 1543, 3079,
      6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869,
      3145739, 6291469, 12582917, 25165843, 50331653, 100663319,
      201326611, 402653189, 805306457, 1610612741, -1};
// List of good primes for hash table sizes from
// http://planetmath.org/goodhashtableprimes
// The -1 at the end is to guarantee an immediate crash if we run off
// the end of the array.

LinearHashDict::LinearHashDict() {
  size_index = 0;
  size = primes[size_index];
  table = new bucket[size](); // Parentheses force initialization to 0
  number = 0;

  // Initialize the array of counters for probe statistics
  probes_stats = new int[MAX_STATS]();
}

LinearHashDict::~LinearHashDict() {
  // Delete all table entries...
  for (int i=0; i<size; i++) {
    if (table[i].key!=NULL) {
      delete table[i].key;
      // Don't delete data here, to avoid double deletions.
    }
  }
  // Delete the table itself
  delete [] table;

  // It's not good style to put this into a destructor,
  // but it's convenient for this assignment...
  cout << "Probe Statistics for find():\n";
  for (int i=0; i<MAX_STATS; i++)
    cout << i << ": " << probes_stats[i] << endl;
  delete [] probes_stats;
}

int LinearHashDict::hash(string keyID) {
  int h=0;
  for (int i=keyID.length()-1; i>=0; i--) {
    h = (keyID[i] + 31*h) % size;
  }
// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
#ifdef MARKING_TRACE
std::cout << "Hashing " << keyID << " to " << h << std::endl;
#endif
// End of "DO NOT CHANGE" Block
  return h;
}

void LinearHashDict::rehash() {
// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// And leave this at the beginning of the rehash() function.
#ifdef MARKING_TRACE
std::cout << "*** REHASHING " << size;
#endif
// End of "DO NOT CHANGE" Block
    
    int newSize = primes[size_index];
    size_index++;
    
    //temp table to rehash to.
    bucket *temp = new bucket[newSize]();
    for(int i =0; i<size;i++){
        int ha= hash(table[i].keyID);
        //linear hash take cares of linea collisons.
        for(int j = 0; j<newSize;j++){
            if(table[ha].key!=NULL){
                ha = (ha +j)%newSize;
            }else break;
        }
        temp[ha]= table[i];
    }
    size = newSize;
    table = temp;
    
  // TODO:  Your code goes here...


// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// And leave this at the end of the rehash() function.
#ifdef MARKING_TRACE
std::cout << " to " << size << " ***\n";
#endif
// End of "DO NOT CHANGE" Block
}

bool LinearHashDict::find(PuzzleState *key, PuzzleState *&pred) {
  // Returns true iff the key is found.
  // Returns the associated value in pred

  // Be sure not to keep calling getUniqId() over and over again!
    int ha = hash(key->getUniqId());
    int ix =0;// numer of probes so far
    bool rt = false;
    for(int i=0; i<size;i++){
        if(table[(ha+i)%size].key== key){
            pred =table[(ha+i)%size].data;
            ix++;
            rt= true;
            break;
        }
    }
    if(ix<MAX_STATS){
        probes_stats[ix]++;
    
    }
    return rt;
}

// You may assume that no duplicate PuzzleState is ever added.
void LinearHashDict::add(PuzzleState *key, PuzzleState *pred) {
    if(number/size>0.5){
        rehash();
    }
  // TODO:  Your code goes here...
    int ha;
    for(int i =0;i<size;i++){
        ha = (hash(key->getUniqId())+i)%size;
        if(table[i].key==NULL){
            table[ha].key=key;
            table[ha].keyID= key->getUniqId();
            table[ha].data = pred;
            return;

        }
    }
    number++;
}

#endif 