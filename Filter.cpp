
#include <set>
#include <cmath>
#include <iostream>
#include <sstream>
#include "Filter.h"
#include "AirTable.h"

vector<Airport> Filter::geographicalLocation(Graph *graph, double lat, double lon) {
    vector<Airport> res; double distance = 40000;
    for (Vertex* vertex: graph->getVertexSet()) {
        Airport airport = vertex->getAirport();
        double dist = harvesineDistance(lat, lon, airport.getLatitude(), airport.getLongitude());

        if (dist < distance) {
            vector<Airport> new_res; new_res.push_back(airport);
            res = new_res;
            distance = dist;
        } else if (dist == distance)
            res.push_back(airport);
    }
    return res;
}

float Filter::harvesineDistance(double lat1, double lon1, double lat2, double lon2) {
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

vector<Airport> Filter::AirportsCity(Graph *g, string city){
    vector<Airport> res;
    for(auto airport: g->getVertexSet()){
        if(airport->getAirport().getCity()==city){
            res.push_back(airport->getAirport());
        }
    }
    return res;
}

vector<Airport> Filter::AirportCode(Graph *g, string code){
    vector<Airport> res;
    for(auto vertex: g->getVertexSet()){
        if(vertex->getAirport().getCode()==code) {
            res.push_back(vertex->getAirport());
            return res;
        }
    }
    return res;
}

vector<Airport> Filter::AirportName(Graph *g, string name){
    vector<Airport> res;
    for(auto vertex: g->getVertexSet()){
        if(vertex->getAirport().getName()==name){
            res.push_back(vertex->getAirport());
            return res;
        }
    }
    return res;
}

void Filter::bestOptionNoFilters(Graph* g, vector<Airport> sourceV, vector<Airport> destV){
    vector<vector<pair<Airline, Vertex*>>> bestOptions;
    bestOptions= bestOptionMix(g, sourceV, destV);
    int i=0;
    for(auto vetor: bestOptions){
        bool first=true;
        string lastA;
        string lastC;
        i++;
        cout<<"Option "<<i<<":"<<endl;
        for(auto p: vetor){
            if(first){
                first=false;
            }
            else{
                cout<<lastA << "["<< lastC<<"]" " ----->" <<' '<<p.second->getAirport().getCode() << "["<<p.second->getAirport().getCity()<<"] "<< "Airline: "<< p.first.getCode()<<endl;
            }
            lastA=p.second->getAirport().getCode();
            lastC=p.second->getAirport().getCity();
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

        if(d>min)
            return res;
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
    return res;
}

vector<vector<pair<Airline, Vertex*>>> Filter::bestOptionMix(Graph* g, vector<Airport> sourceV, vector<Airport> destV){
    int min=100000;
    vector<vector<pair<Airline, Vertex*>>> bestOptions;
    for(auto airportS_: sourceV){
        for(auto airportD_: destV){
            Vertex* airportS = g->findVertex(airportS_);
            Vertex* airportD = g->findVertex(airportD_);
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

void Filter::minAirlines(Graph* g, vector<Airport> sourceV, vector<Airport> destV){
    vector<vector<pair<Airline, Vertex*>>> bestOptions;
    vector<vector<pair<Airline, Vertex*>>> filteredOptions;
    set<Airline> airlines;
    int min=10000;
    bestOptions= bestOptionMix(g, sourceV, destV);
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
        string lastA;
        string lastC;
        i++;
        cout<<"Option "<<i<<":"<<endl;
        for(auto p: vetor){
            if(first){
                first=false;
            }
            else{
                cout<<lastA << "["<< lastC<<"]" " ----->" <<' '<<p.second->getAirport().getCode() << "["<<p.second->getAirport().getCity()<<"] "<< "Airline: "<< p.first.getCode()<<endl;
            }
            lastA=p.second->getAirport().getCode();
            lastC=p.second->getAirport().getCity();
        }
        cout<<endl;
    }
    return;
}

vector<string> Filter::airlineFilter(string str, AirTable* airTable) {
    vector<string> airlineNames;
    vector<string> airlineCodes;
    istringstream iss(str);
    string airline;
    while (getline(iss, airline, ',')) {
        airlineNames.push_back(airline);
    }
    auto airlines = airTable->getAirlines();

    for (auto air: airlines) {
        auto it = find(airlineNames.begin(), airlineNames.end(), air.getName());
        if (it != airlineNames.end()) {
            airlineCodes.push_back(air.getCode());
        }
    }
    return airlineCodes;
}

Graph* Filter::airlineFilterGraph( vector<string> airlineCodes,Graph* graph, AirTable* airTable){
    Graph* graph1 = new Graph();

    queue<Vertex *> vQueue;
    for (auto vertex: graph->getVertexSet()) {
        for (auto edge: vertex->getFlights()) {
            auto it = find(airlineCodes.begin(),airlineCodes.end(),edge.getAirline().getCode());
            if (it!=airlineCodes.end()) {
                auto air = *it;
                auto it2 = airTable->findAirline(air);
                Airport* source =new Airport(vertex->getAirport());
                Airport* dest =new Airport(edge.getDestination()->getAirport());
                graph1->addVertex(*source);graph1->addVertex(*dest);
                auto vertSource = graph1->findVertex(*source);
                auto vertDest = graph1->findVertex(*dest);
                graph1->addEdge(vertSource, vertDest, it2);
            }
        }
    }
    return graph1;
}