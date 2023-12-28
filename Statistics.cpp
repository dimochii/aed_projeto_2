
#include <iostream>
#include <set>
#include "Statistics.h"
void Statistics::totalNumberAirports(Graph* graph) {
    cout << "Total number of airports: " << graph->getNumberVertex() << endl;
}

void Statistics::totalNumberFlights(Graph* graph) {
    int num = 0;
    for (Vertex* vertex: graph->getVertexSet())
        num += vertex->getNumberFlights();
    cout << "Total number of flights: " << num << endl;
}


void Statistics::numFlightOutAir(Graph* graph,Airport airport) {
    set<Airline> outAirlines;
    auto it = graph->findVertex(airport);
    int num = it->getFlights().size();

    for (auto e : it->getFlights())
        outAirlines.insert(e.getAirline());

    cout <<"Number of flights out of "<<airport.getCode()<<": "<<num<<endl;
    cout <<"Out of "<<outAirlines.size()<<" different airlines."<<endl;
}


void Statistics::flightsPerCity(Graph* g, string city) {
    int count=0;
    for (auto vertex: g->getVertexSet()) {
        if (vertex->getAirport().getCity()==city)
            count+=vertex->getFlights().size();
    }
    cout << "Number of flights on city " << city << ": " << count << endl;
}

void Statistics::flightsPerAirline(Graph*g, Airline airline) {
    int count=0;
    for (auto vertex: g->getVertexSet()) {
        for (auto edge: vertex->getFlights()) {
            if (edge.getAirline().getCode()==airline.getCode())
                count++;
        }
    }
    cout << "Number of flights on airline " << airline.getCode() << ": " << count << endl;
}

void Statistics::countriesPerAirport(Graph* g, string airportCode) {
    int count=0;
    vector<string> countries;
    for(auto vertex: g->getVertexSet()){
        if(vertex->getAirport().getCode()==airportCode){
            for(auto edge: vertex->getFlights()){
                auto dest=edge.getDestination();
                string country=dest->getAirport().getCountry();
                auto it=find(countries.begin(), countries.end(), country);
                if (it==countries.end()){
                    count++;
                    countries.push_back(country);
                }
            }
        }
    }
    cout << count<< endl;
}

void Statistics::countriesPerCity(Graph* g, string city) {
    int count=0;
    vector<string> countries;
    for(auto vertex: g->getVertexSet()){
        if(vertex->getAirport().getCity()==city){
            for(auto edge: vertex->getFlights()){
                auto dest=edge.getDestination();
                string country=dest->getAirport().getCountry();
                auto it=find(countries.begin(), countries.end(), country);
                if (it==countries.end()){
                    count++;
                    countries.push_back(country);
                }
            }
        }
    }
    cout << count << endl;
}





vector<Vertex *> Statistics::reachableDestinations(Graph* graph, Airport source, int num) {
    vector<Vertex *> res;
    Vertex* vSource = graph->findVertex(source);

    if (vSource != NULL) {
        queue<Vertex *> vQueue;
        for (auto vertex : graph->getVertexSet())
            vertex->setVisited(false);

        vQueue.push(vSource);
        vSource->setVisited(true);

        while ((num != 0) && (!vQueue.empty())) {
            queue<Vertex *> vQueue2;

            while (!vQueue.empty()) {
                Vertex* vertex = vQueue.front(); vQueue.pop();
                res.push_back(vertex);

                for (Edge edge : vertex->getFlights()) {
                    Vertex* vertex2 = edge.getDestination();
                    if ( !vertex2->isVisited() ) {
                        vQueue2.push(vertex2);
                        vertex2->setVisited(true);
                    }
                }
            }

            vQueue = vQueue2;
            num--;
        }

        while (!vQueue.empty()) {
            Vertex* vertex = vQueue.front(); vQueue.pop();
            res.push_back(vertex);
        }
    }
    return res;
}


void Statistics::numberReachableAirports(Graph* graph, Airport source, int num) {
    cout << reachableDestinations(graph, source, num).size()
         << " airports reachable from airport " << source.getCode() << endl;
}

void Statistics::numberReachableCities(Graph *graph, Airport source, int num) {
    set<string> res;
    vector<Vertex *> reachableDest = reachableDestinations(graph, source, num);
    for (Vertex * vertex: reachableDest)
        res.insert(vertex->getAirport().getCity());
    cout << res.size()
         << " cities reachable from airport " << source.getCode() << endl;
}

void Statistics::numberReachableCountries(Graph* graph, Airport source, int num) {
    set<string> res;
    vector<Vertex *> reachableDest = reachableDestinations(graph, source, num);
    for (Vertex * vertex: reachableDest)
        res.insert(vertex->getAirport().getCountry());
    cout << res.size()
         << " countries reachable from airport " << source.getCode() << endl;
}

void Statistics::maxTrip(Graph* graph) {
    vector<pair<Airport,Airport>> pairsMax; int numMax = 0;
    for (Vertex* vertex: graph->getVertexSet())
        maxTripVertex(graph, vertex, pairsMax, numMax);

    cout << "The maximum trip has " << numMax << " stops." << endl;
    for (auto i: pairsMax)
        cout << "From " << i.first.getCode() << " to " << i.second.getCode() << endl;
}

void Statistics::maxTripVertex(Graph* graph, Vertex* vSource, vector<pair<Airport,Airport>>& pairsMax, int& numMax) {
    int num = 0;
    queue<Vertex *> vQueue;
    queue<Vertex *> vQueue2;
    queue<Vertex *> vQueue3;
    for (auto vertex: graph->getVertexSet())
        vertex->setVisited(false);

    vQueue.push(vSource);
    vSource->setVisited(true);

    bool first = true;
    while (first || !vQueue2.empty()) {
        if (first) first = false;
        else vQueue = vQueue2;
        queue<Vertex *> empty;
        swap(vQueue2, empty);
        vQueue3 = vQueue;

        while (!vQueue.empty()) {
            Vertex *vertex = vQueue.front();
            vQueue.pop();

            for (Edge edge: vertex->getFlights()) {
                Vertex *vertex2 = edge.getDestination();
                if (!vertex2->isVisited()) {
                    vQueue2.push(vertex2);
                    vertex2->setVisited(true);
                }
            }
        }
        num++;
    }
    num--;

    if (num > numMax) {
        vector<pair<Airport, Airport>> pairs;
        while (!vQueue3.empty()) {
            Vertex *vertex = vQueue3.front();
            vQueue3.pop();
            pairs.push_back(make_pair(vSource->getAirport(), vertex->getAirport()));
        }
        pairsMax = pairs;
        numMax = num;
    } else if (num == numMax) {
        while (!vQueue3.empty()) {
            Vertex *vertex = vQueue3.front();
            vQueue3.pop();
            pairsMax.push_back(make_pair(vSource->getAirport(), vertex->getAirport()));
        }
    }
}




void dfs_art(Graph *g, Vertex *v, unordered_set<string> &res, int &i);

void Statistics::airport_art(Graph *g) {
    unordered_set<string> art;
    int i=1;
    for(auto vertex: g->getVertexSet()){
        vertex->setNum(-1);
        vertex->setProcessing(false);
    }

    for(auto vertex: g->getVertexSet()){
        if(vertex->getNum()==-1){
            dfs_art(g, vertex, art, i);
        }
    }
    int count = 0;
    for(string airport: art){
        count++;
        //cout << airport << endl;
    }
    cout << count << endl;
}

void dfs_art(Graph*g, Vertex*v, unordered_set<string> &l, int &i) {
    v->setNum(i);
    v->setLow(i);
    v->setProcessing(true);
    i++;
    int trees=0;

    for(auto edge: v->getFlights()){
        auto destV=edge.getDestination();
        if (destV->getNum()==-1){
            trees++;
            dfs_art(g, destV, l, i);
            v->setLow(min(destV->getLow(), v->getLow()));
            if((destV->getLow()>=v->getNum() && v->getNum()!=1) || (v->getNum()==1 && trees>1) ){
                l.insert(v->getAirport().getCode());
            }
        }
        else if (v->isProcessing()) {
            v->setLow(min(destV->getNum(), v->getLow()));
        }
    }

    v->setProcessing(false);
}













void Statistics::numDestinationsAirport( Graph *graph, Airport source, string fOption) {
//vector<Vertex *> res;
    set<string> res;

    Vertex* vSource = graph->findVertex(source);
    if (vSource == nullptr) {
        cout << source.getCode() << " airport has " << res.size() <<" differet "<<fOption<< " destinations." << endl;
    }

    for (auto v : graph->getVertexSet())
        v->setVisited(false);

    numDestAirportVisit(vSource, res, fOption);
    cout << source.getCode() << " airport has " << res.size() <<" different "<<fOption<< " destinations." << endl;
}

void Statistics::numDestAirportVisit(Vertex *v, set<string> & res, string & fOption) {
    v->setVisited(true);
    if(fOption == "city") res.insert(v->getAirport().getCity());
    else if(fOption == "country") res.insert(v->getAirport().getCountry());
    else {res.insert(v->getAirport().getName()); fOption = "airport";}

    for (auto & e : v->getFlights()) {
        auto w = e.getDestination();
        if ( ! w->isVisited())
            numDestAirportVisit(w, res, fOption);
    }
}



struct CompareVertices {
    bool operator()(const Vertex* v1, const Vertex* v2) const {
        return v1->getNumberFlights() < v2->getNumberFlights();
    }
};

void Statistics::topKAirTraffic(Graph *graph, int k) {   // antes de chamar mos esta funçao confimar se o k <= 0 pq isso nao existe
    std::priority_queue<Vertex*, std::vector<Vertex*>, CompareVertices> airportPriorityQueue;
    Vertex* vSource;

        queue<Vertex *> vQueue;
        for (auto vertex : graph->getVertexSet()) {
            vertex->setVisited(false);
            vSource = vertex;
        }

        vQueue.push(vSource);
        vSource->setVisited(true);

        while (!vQueue.empty()) {
            Vertex* v = vQueue.front();
            vQueue.pop();
            airportPriorityQueue.push(v);

            for (Edge edge : v->getFlights()) {
                Vertex* w = edge.getDestination();
                    if ( !w->isVisited() ) {
                        vQueue.push(w);
                        w->setVisited(true);
                    }
                }
        }


    for(int i = 0; i <= k-1; i++){
        if(!airportPriorityQueue.empty())airportPriorityQueue.pop();
    }
    if(airportPriorityQueue.empty()) cout <<"Invalid.";
    else{
        auto trafficVert = airportPriorityQueue.top();
        cout<< "The airport is: "<<trafficVert->getAirport().getName()<<" ("<<trafficVert->getAirport().getCode()<<')'<<endl<<
        "with "<<trafficVert->getNumberFlights()<<" flights";
    }
}



