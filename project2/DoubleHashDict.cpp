#ifndef _DOUBLEHASHDICT_CPP
#define _DOUBLEHASHDICT_CPP

//DoubleHashDict.cpp
#include "DoubleHashDict.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>

// An implementation of a dictionary ADT as hash table with double hashing
//

const int DoubleHashDict::primes[] = {53, 97, 193, 389, 769, 1543, 3079,
    6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869,
    3145739, 6291469, 12582917, 25165843, 50331653, 100663319,
    201326611, 402653189, 805306457, 1610612741, -1};
// List of good primes for hash table sizes from
// http://planetmath.org/goodhashtableprimes
// The -1 at the end is to guarantee an immediate crash if we run off
// the end of the array.

DoubleHashDict::DoubleHashDict() {
    size_index = 0;
    size = primes[size_index];
    table = new bucket[size](); // Parentheses force initialization to 0
    number = 0;
    
    // Initialize the array of counters for probe statistics
    probes_stats = new int[MAX_STATS]();
}

DoubleHashDict::~DoubleHashDict() {
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

int DoubleHashDict::hash1(string keyID) {
    int h=0;
    for (int i=keyID.length()-1; i>=0; i--) {
        h = (keyID[i] + 31*h) % size;
    }
    // 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
    
#ifdef MARKING_TRACE
    std::cout << "Hash 1:  " << keyID << " to " << h << std::endl;
#endif
    // End of "DO NOT CHANGE" Block
    return h;
}

int DoubleHashDict::hash2(string keyID) {
    int h=0;
    for (int i=keyID.length()-1; i>=0; i--) {
        h = (keyID[i] + 63*h) % size;
    }
    // Make sure second hash is never 0 or size
    h = h/2 + 1;
    
    // 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
    
#ifdef MARKING_TRACE
    std::cout << "Hash 2:  " << keyID << " to " << h << std::endl;
#endif
    // End of "DO NOT CHANGE" Block
    return h;
}

void DoubleHashDict::rehash() {
    // 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
    // And leave this at the beginning of the rehash() function.
#ifdef MARKING_TRACE
    std::cout << "*** REHASHING " << size;
#endif
    // End of "DO NOT CHANGE" Block
    
    
    // TODO:  Your code goes here...
    
    int newSize = primes[size_index];
    size_index++;
    size = newSize;
    int ha;
    //temp table to rehash to.
    bucket *temp = new bucket[newSize]();
    for(int i =0; i<size;i++){
        if(table[i].key != NULL){
            for(int j =0; j<size; j++){
                ha = (hash1(table[i].keyID)+ j*hash2(table[i].keyID))%size;
                if(temp[ha].key ==NULL){
                    temp[ha]= table[i];
                    break;
                }
            }
        }
    }
    table = temp;
    
    
    
    // 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
    // And leave this at the end of the rehash() function.
#ifdef MARKING_TRACE
    std::cout << " to " << size << " ***\n";
#endif
    // End of "DO NOT CHANGE" Block
}

bool DoubleHashDict::find(PuzzleState *key, PuzzleState *&pred) {
    // Returns true iff the key is found.
    // Returns the associated value in pred
    
    // Be sure not to keep calling getUniqId() over and over again
    int ha; //probe stats
    for (int i=0; i<size; i++) {
        ha = (hash1(key->getUniqId())+ i*hash2(key->getUniqId()))%size;
        if(table[ha].key == key){
            probes_stats[i+1]++;
            pred = table[ha].data;
            return  true;
        }
    }
    return false; // Stub:  Delete this line when you've implemented the function
}

// You may assume that no duplicate PuzzleState is ever added.
void DoubleHashDict::add(PuzzleState *key, PuzzleState *pred) {
    
    // TODO:  Your code goes here...
    if(number/size>0.5)
        rehash();
    int ha;
    //key==NULL means empty spot
    
    for(int i=0; i<size; i++){
        ha = (hash1(key->getUniqId())+ i*hash2(key->getUniqId()))%size;
        if(table[ha].key ==NULL){
            table[ha].key=key;
            table[ha].keyID= key->getUniqId();
            table[ha].data = pred;
            return;
        }
    }
    number++;
}

#endif 
