#include <iostream>
#include "Script.h"
#include "Graph.h"
#include "HashTable.h"
#include "Statistics.h"

int main() {
    Graph* graph = new Graph();
    HashTable* hashTable = new HashTable();
    Script::infoCollection(graph, hashTable);

    return 0;
}
