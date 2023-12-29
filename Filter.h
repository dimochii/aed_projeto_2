
#ifndef UNTITLED_FILTER_H
#define UNTITLED_FILTER_H


#include "Graph.h"
#include "HashTable.h"

class Filter {
public:
    static vector<Airport> geographicalLocation(Graph* graph, double lat, double lon);
    static float harvesineDistance(Graph* graph, double lat1, double lon1, double lat2, double lon2);
    static vector<Airport> AirportCode(Graph *g, string code);
    static vector<Airport> AirportName(Graph *g, string name);
    static vector<Airport> AirportsCity(Graph *g, string city);

    static vector<vector<pair<Airline, Vertex*>>> minPathAirports(Graph* g, Vertex* source, Vertex* dest);
    static vector<vector<pair<Airline, Vertex *>>> bestOptionMix(Graph *g, vector<Airport> sourceV, vector<Airport> destV);
    static void bestOptionNoFilters(Graph *g, vector<Airport> sourceV, vector<Airport> destV);
    static void minAirlines(Graph *g, vector<Airport> sourceV, vector<Airport> destV);


    static HashTable* airlineFilterHash(vector<string> airlineCodes,HashTable* hashTable);
    static Graph* airlineFilterGraph( vector<string> airlineCodes, Graph* Graph, HashTable* hashTable);
    static vector<string> airlineFilter(string str, HashTable* hashTable);
};


#endif //UNTITLED_FILTER_H
