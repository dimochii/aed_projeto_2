
#ifndef UNTITLED_FILTER_H
#define UNTITLED_FILTER_H


#include "Graph.h"
#include "HashTable.h"

class Filter {
public:
    static void geographicalLocation(Graph* graph, double lat, double lon);
    static float harvesineDistance(Graph* graph, double lat1, double lon1, double lat2, double lon2);

    static void bestOptionNoFilters(Graph* g, string source, string dest);
    static void minAirlines(Graph* g, string source, string dest);
    static vector<vector<pair<Airline, Vertex*>>> minPathAirports(Graph* g, Vertex* source, Vertex* dest);
    static vector<vector<pair<Airline, Vertex*>>> bestOptionMix(Graph* g, string source, string dest);

    static HashTable* airlineFilterHash(vector<string> airlineCodes,HashTable* hashTable);
    static Graph* airlineFilterGraph( vector<string> airlineCodes, Graph* Graph, HashTable* hashTable);
    static vector<string> airlineFilter(string str, HashTable* hashTable);
};


#endif //UNTITLED_FILTER_H
