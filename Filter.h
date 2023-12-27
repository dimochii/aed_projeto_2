
#ifndef UNTITLED_FILTER_H
#define UNTITLED_FILTER_H


#include "Graph.h"

class Filter {
public:
    static void geographicalLocation(Graph* graph, double lat, double lon);
    static float harvesineDistance(Graph* graph, double lat1, double lon1, double lat2, double lon2);

    static void bestOptionNoFilters(Graph* g, string source, string dest);
    static void minAirlines(Graph* g, string source, string dest);

};


#endif //UNTITLED_FILTER_H
