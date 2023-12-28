#include <iostream>
#include "Script.h"
#include "Graph.h"
#include "HashTable.h"
#include "Menu.h"
#include "Statistics.h"

int main() {
    Menu menu = Menu();

    Graph* graph = menu.getGraph();
    HashTable* hashTable = menu.getHashTable();

    //menu.openMenu();
    Script::infoCollection(graph, hashTable);

    return 0;
}
