
#ifndef UNTITLED_FILTERS_H
#define UNTITLED_FILTERS_H


#include "Graph.h"

class Filters {
public:
    static void geographicalLocation(Graph* graph, double lat, double lon);
    static float harvesineDistance(Graph* graph, double lat1, double lon1, double lat2, double lon2);
};


#endif //UNTITLED_FILTERS_H
