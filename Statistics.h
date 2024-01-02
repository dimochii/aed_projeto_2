
#ifndef AIRPORTSPROJECT_STATISTICS_H
#define AIRPORTSPROJECT_STATISTICS_H


#include "Graph.h"
#include <set>

class Statistics {
public:
    static void totalNumberAirports(Graph* graph);
    static void totalNumberFlights(Graph* graph);

    static void numFlightOutAir(Graph* graph, Airport airport);

    static void flightsPerCity(Graph* g, string city);
    static void flightsPerAirline(Graph* g, Airline airline);

    static void countriesPerCity(Graph* g, string city);
    static void countriesPerAirport(Graph* g, Airport airport);

    static void numDestAirportVisit(Vertex* v, set<string> & res, string & fOption);
    static void numDestinationsAirport( Graph *graph, Airport source, string fOption);

    static vector<Vertex *> reachableDestinations(Graph* graph, Airport source, int num);
    static void numberReachable(Graph* graph, Airport source, int num, string mode);


    static void maxTripVertex(Graph* graph, Vertex* vertex, vector<pair<Airport,Airport>>& pairsMax, int& numMax);
    static void maxTrip (Graph* graph);

    static void topKAirTraffic(Graph *graph,int k);

    static void dfs_art(Graph *g, Vertex *v, unordered_set<string> &res, int &i);
    static void airport_art(Graph* g, AirTable* hashTable);
};


#endif //AIRPORTSPROJECT_STATISTICS_H
