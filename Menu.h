
#ifndef UNTITLED_MENU_H
#define UNTITLED_MENU_H

#include <iostream>
#include "Script.h"
#include "Graph.h"
#include "HashTable.h"
#include "Menu.h"

#include "Graph.h"

class Menu {
    Graph* graph = new Graph();

    Graph* graphFilter;
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


    void sourceLocation();


    void destinationLocation(vector<Airport> airportsSource);

    void askContinue();
};


#endif //UNTITLED_MENU_H
