
#ifndef AIRPORTSPROJECT_STATISTICS_H
#define AIRPORTSPROJECT_STATISTICS_H


#include "Graph.h"
#include <set>

class Statistics {
public:
    static void totalNumberAirports(Graph* graph);
    static void totalNumberFlights(Graph* graph);

    static vector<Vertex *> reachableDestinations(Graph* graph, Airport source, int num);
    static void numberReachableAirports (Graph* graph, Airport source, int num);
    static void numberReachableCities (Graph* graph, Airport source, int num);
    static void numberReachableCountries (Graph* graph, Airport source, int num);

    static void maxTrip (Graph* graph);
    static void maxTripVertex(Graph* graph, Vertex* vertex, vector<pair<Airport,Airport>>& pairsMax, int& numMax);

    static void flightsPerCity(Graph* g, string city);
    static void flightsPerAirline(Graph* g, string airlineCode);
    static void countriesPerAirport(Graph* g, string airportCode);
    static void countriesPerCity(Graph* g, string city);
    static void airport_art(Graph* g);

    static void numFlightOutAir(Graph* graph,Airport airport);
    static void numDestinationsAirport( Graph *graph, Airport source, string fOption);
    static void numDestAirportVisit(Vertex* v, set<string> & res, string & fOption);
    static void topKAirTraffic(Graph *graph,int k);

};


#endif //AIRPORTSPROJECT_STATISTICS_H
