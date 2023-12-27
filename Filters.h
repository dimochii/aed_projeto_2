//
// Created by marta on 26/12/2023.
//

#ifndef AED_PROJETO_2_FILTER_H
#define AED_PROJETO_2_FILTER_H
#include <string>
#include "Graph.h"
using namespace std;


class Filters {
public:
    static void bestOptionCities(Graph* g, string source, string dest);

    static void besOptionAirports(Graph *g, string source, string dest);

};


#endif //AED_PROJETO_2_FILTER_H
