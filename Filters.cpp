//
// Created by diana_9kbxrpt on 27/12/2023.
//


#include "Filters.h"
#include "HashTable.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>

using namespace std;



vector<string> Filters::airlineFilter(string str, HashTable* hashTable) {
    vector<string> airlineNames;
    vector<string> airlineCodes;
    istringstream iss(str);
    string airline;
    while (getline(iss, airline, ',')) {
        airlineNames.push_back(airline);
    }
    auto airlines = hashTable->getAirlines();

    for (auto air: airlines) {
        auto it = find(airlineNames.begin(), airlineNames.end(), air.getName());
        if (it != airlineNames.end()) {
            airlineCodes.push_back(air.getCode());
        }
    }
    return airlineCodes;
}

HashTable* Filters::airlineFilterHash(vector<string> airlineCodes, HashTable* hashTable){

    auto airlines = hashTable->getAirlines();
    HashTable* newHashTable = new HashTable();

    for (auto air : airlines) {
        auto it = find(airlineCodes.begin(),airlineCodes.end(),air.getCode());
        if(it!=airlineCodes.end()){
            std::cout<<air.getName();
            newHashTable->addAirline(air);
        }

    }
    return newHashTable;

}

Graph* Filters::airlineFilterGraph( vector<string> airlineCodes,Graph* graph, HashTable* hashTable){
    Graph* graph1 = new Graph();

    Vertex* vSource = graph->getVertexSet()[0];

    queue<Vertex *> vQueue;
    for (auto vertex : graph->getVertexSet())
        vertex->setVisited(false);

    vQueue.push(vSource);
    vSource->setVisited(true);

    while (!vQueue.empty()) {
        Vertex* v = vQueue.front();
        vQueue.pop();

        for (Edge edge : v->getFlights()) {
            Vertex* w = edge.getDestination();

            auto it = find(airlineCodes.begin(),airlineCodes.end(),edge.getAirline().getCode());
            if(it!=airlineCodes.end()){
                auto air = *it;
                auto it2 = hashTable->findAirline(air);
                Airport* source =new Airport(v->getAirport());
                Airport* dest =new Airport(edge.getDestination()->getAirport());
                graph1->addVertex(*source);graph1->addVertex(*dest);
                auto vertSource = graph1->findVertex(*source);
                auto vertDest = graph1->findVertex(*dest);
                graph1->addEdge(vertSource, vertDest, it2);
            }

            if ( !w->isVisited() ) {
                vQueue.push(w);
                w->setVisited(true);
            }
        }
    }
    return graph1;
}