#include <iostream>
#include "Script.h"
#include "Graph.h"
#include "HashTable.h"
#include "Statistics.h"
#include "Filters.h"

int main() {
    Graph* graph = new Graph();
    HashTable* hashTable = new HashTable();
    Script::infoCollection(graph, hashTable);
    vector<string> airlineCodes = Filters::airlineFilter( "Ryanair,Qatar Airways", hashTable);
    HashTable* hashTable2 = Filters::airlineFilterHash(airlineCodes,hashTable);
    Graph* graph2 = Filters::airlineFilterGraph(airlineCodes,graph,hashTable2);

    Airport opo = Airport("OPO", "Porto","Porto","Portugal", 41.248055, -8.681389);

    //Statistics::numFlightOutAir(graph,opo);
    //Statistics::numDestinationsAirport(graph2,opo,"country");
    //Statistics::numberReachableAirports(graph2,opo,2);
    //Statistics::totalNumberFlights(graph2);
    Statistics::topKAirTraffic(graph2,1);
    return 0;
}
