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

vector<vector<pair<Airline, Vertex*>>> minPathAirports(Graph* g, Vertex* source, Vertex* dest);

void Filters::bestOptionMix(Graph* g, string source, string dest){
    vector<Vertex*> AirportS;
    vector<Vertex*> AirportD;
    if(isupper(source.back())){
        Vertex* vSource = g->findVertexAirport(source);
        AirportS.push_back(vSource);
    }
    else{
        for(auto airport: g->getVertexSet()){
            if(airport->getAirport().getCity()==source){
                AirportS.push_back(airport);
            }
        }
    }

    if(isupper(dest.back())){
        Vertex* vDest = g->findVertexAirport(dest);
        AirportD.push_back(vDest);
    }
    else{
        for(auto airport: g->getVertexSet()){
            if(airport->getAirport().getCity()==dest){
                AirportD.push_back(airport);
            }
        }
    }

    int min=100000;
    vector<vector<pair<Airline, Vertex*>>> bestOptions;
    for(auto airportS: AirportS){
        for(auto airportD: AirportD){
            vector<vector<pair<Airline, Vertex*>>> current=minPathAirports(g, airportS, airportD);
            if(current[0].size()<min){
                min=current[0].size();
                bestOptions.clear();
                bestOptions=current;
            }
            else if(current[0].size()==min){
                for(auto option: current){
                    bestOptions.push_back(option);
                }
            }
        }
    }
    int i=0;
    for(auto vetor: bestOptions){
        bool first=true;
        string last;
        i++;
        cout<<"Option "<<i<<":"<<endl;
        for(auto p: vetor){
            if(first){
                first=false;
            }
            else{
                cout<<last <<' '<< p.first.getCode()<<' '<<p.second->getAirport().getCode()<<endl;
            }
            last=p.second->getAirport().getCode();
        }
        cout<<endl;
    }
    return;

}

vector<vector<pair<Airline, Vertex*>>> minPathAirports(Graph* g, Vertex* source, Vertex* dest){
    vector<vector<pair<Airline, Vertex*>>> res;
    for(auto vertex: g->getVertexSet()){
        vertex->setVisited(false);
    }


    source->setVisited(true);

    queue<pair<vector<pair<Airline, Vertex*>>, int >> q;
    vector<pair<Airline, Vertex*>> v;


    v.push_back(make_pair(Airline(), source));
    q.push(make_pair(v, 0));
    int min=1000000;
    while(!q.empty()){
        auto vertex = q.front().first;
        int d = q.front().second;
        q.pop();

        if(d>min){
            return res;
        }

        else if (vertex.back().second == dest) {
            if (d <= min) {
                min = d;
                res.push_back(vertex);
            }
        }
        else {
            for (auto edge: vertex.back().second->getFlights()) {
                auto destV = edge.getDestination();
                if(!destV->isVisited()){
                    destV->setVisited(true);

                    vertex.push_back(make_pair(edge.getAirline(), destV));
                    q.emplace(vertex, d + 1);
                }

            }
        }
    }
}