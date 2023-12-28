#include <iostream>
#include "Script.h"
#include "Graph.h"
#include "HashTable.h"
#include "Menu.h"
#include "Statistics.h"
#include "Filter.h"

int main() {
    Menu menu = Menu();

    Graph* graph = menu.getGraph();
    HashTable* hashTable = menu.getHashTable();

    Script::infoCollection(graph, hashTable);
    menu.openMenu();

    return 0;
}
