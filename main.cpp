#include <iostream>
#include "Script.h"
#include "Graph.h"
#include "HashTable.h"
#include "Statistics.h"
#include "Filters.h"
#include <iostream>
using namespace std;

int main() {
    Graph* graph = new Graph();
    HashTable* hashTable = new HashTable();
    Script::infoCollection(graph, hashTable);
    /*for(auto v: Filters::besOptionAirports(graph, "CDG", "KEF")){
        cout<<v->getAirport().getCode() << ' ';
    }*/
    Filters::bestOptionMix(graph, "Paris", "Keflavik");
    return 0;
}
