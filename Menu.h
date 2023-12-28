
#ifndef UNTITLED_MENU_H
#define UNTITLED_MENU_H


#include "Graph.h"

class Menu {
    Graph* graph = new Graph();
    Graph* graphAtual = graph;
    HashTable* hashTable = new HashTable();

public:
    Menu();
    Graph* getGraph();
    HashTable* getHashTable();

    void openMenu();
    int closeMenu();

    void initialOptions();
    void statistics();
    void bestFlight();
    void filter();

    void statisticsNumbers();
    void statisticsOthers();

    Airport* chooseAirportCode();
    Airport* chooseAirportName();
};


#endif //UNTITLED_MENU_H
