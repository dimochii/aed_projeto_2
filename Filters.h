//
// Created by diana_9kbxrpt on 27/12/2023.
//

#ifndef UNTITLED_FILTERS_H
#define UNTITLED_FILTERS_H
#include "HashTable.h"
#include "Graph.h"

class Filters {



public:
    static HashTable* airlineFilterHash(vector<string> airlineCodes,HashTable* hashTable);
    static Graph* airlineFilterGraph( vector<string> airlineCodes, Graph* Graph, HashTable* hashTable);
    static vector<string> airlineFilter(string str, HashTable* hashTable);
};


#endif //UNTITLED_FILTERS_H
