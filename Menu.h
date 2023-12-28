
#ifndef UNTITLED_MENU_H
#define UNTITLED_MENU_H


#include "Graph.h"

class Menu {
    Graph* graph = new Graph();
    Graph* graphAtual = graph;
    HashTable* hashTable = new HashTable();
    bool airlineFilter = false;

public:
    Menu();
    Graph* getGraph();
    HashTable* getHashTable();
    void setAirlineFilter(bool airlineFilter);
    bool getAirlineFilter();

    void openMenu();
    int closeMenu();
    void initialOptions();

    void statistics();

    void bestFlight();

    void filter();
    void activateFilter();

    void statisticsNumbers();
    void statistics4();
    string askMode();

    void statisticsOthers();

    Airport askAirport();
    Airport askAirportCode();
    Airport askAirportName();

    Airline askAirline();
    Airline askAirlineCode();
    Airline askAirlineName();

    void askContinue();
};


#endif //UNTITLED_MENU_H
