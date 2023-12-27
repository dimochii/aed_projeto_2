
#include <cmath>
#include <iostream>
#include <sstream>
#include <set>
#include "Filter.h"
#include "HashTable.h"

void Filter::geographicalLocation(Graph *graph, double lat, double lon) {
    vector<Airport> res; double distance = 40000;
    for (Vertex* vertex: graph->getVertexSet()) {
        Airport airport = vertex->getAirport();
        double dist = harvesineDistance(graph, lat, lon, airport.getLatitude(), airport.getLongitude());

        if (dist < distance) {
            vector<Airport> new_res; new_res.push_back(airport);
            res = new_res;
            distance = dist;
        } else if (dist == distance)
            res.push_back(airport);
    }

    cout << res.size() << endl;
    for (Airport airport: res)
        cout << airport.getCode() << endl;

}

float Filter::harvesineDistance(Graph *graph, double lat1, double lon1, double lat2, double lon2) {
    const double radiusEarth = 6371.0;

    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;
    double dLat1 = lat1 * M_PI / 180.0;
    double dLat2 = lat2 * M_PI / 180.0;

    double a = sin(dLat / 2.0) * sin(dLat / 2.0) +
               cos(dLat1) * cos(dLat2) *
               sin(dLon / 2.0) * sin(dLon / 2.0);

    double c = 2.0 * asin(sqrt(a));

    return radiusEarth * c;
}


void Filter::minAirlines(Graph* g, string source, string dest){
    vector<vector<pair<Airline, Vertex*>>> bestOptions;
    vector<vector<pair<Airline, Vertex*>>> filteredOptions;
    set<Airline> airlines;
    int min=10000;
    bestOptions= bestOptionMix(g, source, dest);
    for(auto option: bestOptions){
        airlines.clear();
        for(auto p: option){
            airlines.insert(p.first);
        }

        if(airlines.size()<min){
            min=airlines.size();
            filteredOptions.clear();
            filteredOptions.push_back(option);
        }
        else if(airlines.size()==min){
            filteredOptions.push_back(option);
        }
    }

    int i=0;
    for(auto vetor: filteredOptions){
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

void Filter::bestOptionNoFilters(Graph* g, string source, string dest){
    vector<vector<pair<Airline, Vertex*>>> bestOptions;
    bestOptions= bestOptionMix(g, source, dest);
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

vector<vector<pair<Airline, Vertex*>>> Filter::minPathAirports(Graph* g, Vertex* source, Vertex* dest){
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
            vector<Vertex*> dests;
            for (auto edge: vertex.back().second->getFlights()) {
                auto destV = edge.getDestination();
                auto vertexC=vertex;
                if(!destV->isVisited()){
                    dests.push_back(destV);


                    vertexC.push_back(make_pair(edge.getAirline(), destV));
                    q.emplace(vertexC, d + 1);
                }
            }
            for(auto v_: dests){
                v_->setVisited(true);
            }
        }
    }
}

vector<vector<pair<Airline, Vertex*>>> Filter::bestOptionMix(Graph* g, string source, string dest){
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
    return bestOptions;
}

vector<string> Filter::airlineFilter(string str, HashTable* hashTable) {
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

HashTable* Filter::airlineFilterHash(vector<string> airlineCodes, HashTable* hashTable){

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

Graph* Filter::airlineFilterGraph( vector<string> airlineCodes,Graph* graph, HashTable* hashTable){
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

