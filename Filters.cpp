//
// Created by marta on 26/12/2023.
//

#include "Filters.h"
#include "Graph.h"
#include "Airport.h"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

void Filters::bestOptionCities(Graph* g, string source, string dest) {
    vector<Airport> citiesS;
    vector<Airport> citiesD;
    for(auto airport: g->getVertexSet()){
        if(airport->getAirport().getCity()==source){
            citiesS.push_back(airport->getAirport());
        }
        else if(airport->getAirport().getCity()==dest){
            citiesD.push_back(airport->getAirport());
        }
    }

}

void Filters::besOptionAirports(Graph* g, string source, string dest){
    vector<vector<Vertex*>> res;
    for(auto vertex: g->getVertexSet()){
        vertex->setVisited(false);
    }
    //vector<Vertex*> res;
    Vertex* vSource = g->findVertexAirport(source);
    vSource->setVisited(true);
    Vertex* vDest = g->findVertexAirport(dest);
    queue<pair<vector<Vertex*>, int >> q;
    vector<Vertex*> v;
    v.push_back(vSource);
    q.push(make_pair(v, 0));
    int min=1000000;
    while(!q.empty()){
        auto vertex = q.front().first;
        int d = q.front().second;
        q.pop();

        if(d>min){
            for(auto vetor: res){
                for(auto ve: vetor){
                    cout<< ve->getAirport().getCode() << ' ';
                }
                cout<<endl;
            }
            return;
        }

        else if (vertex.back() == vDest) {
            if (d <= min) {
                min = d;
                res.push_back(vertex);
            }
        }
        else {
            for (auto edge: vertex.back()->getFlights()) {
                auto destV = edge.getDestination();
                if(!destV->isVisited()){
                    destV->setVisited(true);
                    vertex.push_back(destV);
                    q.emplace(vertex, d + 1);
                }

            }
        }
    }
    //for(auto vetor: res){
        /*for(auto vertex: res){
            cout<<vertex->getAirport().getCode()<<' ';
        }
        cout<<endl;*/
    //}
}