
#ifndef UNTITLED_MENU_H
#define UNTITLED_MENU_H


#include "Graph.h"

class Menu {
    Graph* graph = new Graph();
    Graph* graphAtual = graph;
    AirTable* airTable = new AirTable();
    CityTable* cityTable = new CityTable();
    bool airlineFilter = false;

public:
    Menu();
    Graph* getGraph();
    AirTable* getAirTable();
    CityTable* getCityTable();

    void openMenu();
    int closeMenu();
    void initialOptions();

    void statistics();

    void statisticsNumbers();
    void statistics4();
    void statistics5();
    string askMode();
    int askX();

    void statisticsOthers();
    int askK();

    void destinationLocation(vector<Airport> airportsSource);
    void sourceLocation();

    void filter();
    void activateFilter();

    Airport askAirport();
    Airport askAirportCode();
    Airport askAirportName();

    Airline askAirline();
    Airline askAirlineCode();
    Airline askAirlineName();

    string askCity();

    void askContinue();
};


#endif //UNTITLED_MENU_H
