#include <iostream>
#include "Script.h"
#include "Graph.h"
#include "AirTable.h"
#include "Menu.h"

int main() {
    Menu menu = Menu();
    Graph* graph = menu.getGraph();
    AirTable* airTable = menu.getAirTable();
    CityTable* cityTable = menu.getCityTable();

    Script::infoCollection(graph, airTable, cityTable);
    menu.openMenu();

    return 0;
}
