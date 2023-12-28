
#include "Graph.h"

//VERTEX
Vertex::Vertex(Airport airport_): airport(airport_) {}

void Vertex::addEdge(Vertex *dest, const Airline* airline) {
    flights.push_back(Edge(dest, airline));
}

void Vertex::setVisited(bool cond) { visited = cond; }

bool Vertex::isVisited() const { return visited; }

void Vertex::setProcessing(bool cond) {processing = cond; }

bool Vertex::isProcessing () const { return processing; }


const Airport &Vertex::getAirport() const { return airport; }

const vector<Edge> &Vertex::getFlights() const { return flights; }

int Vertex::getNumberFlights() const { return flights.size(); }

bool Vertex::operator < (const Vertex& other) const{
    return flights.size() < other.getNumberFlights();
}
int Vertex::getNum() const { return num;}

void Vertex::setNum(int num) { this->num=num;}

int Vertex::getLow() const { return low;}

void Vertex::setLow(int low) { this->low=low;}



//EDGE
Edge::Edge(Vertex* destination_, const Airline* airline_):
            destination(destination_), airline(airline_) {}

Airline Edge::getAirline() const {
    return *airline;
}

Vertex * Edge::getDestination() const {
    return destination;
}


//GRAPH
Vertex *Graph::findVertex(const Airport &airport) const {
    Vertex *vertex = new Vertex(airport);
    auto it = vertexSet.find(vertex);
    if (it != vertexSet.end()) return *it;
    return nullptr;
}

Vertex*  Graph::findVertexCode(const string code) const {
    Vertex *vertex = new Vertex(Airport(code));
    auto it = vertexSet.find(vertex);
    if (it != vertexSet.end()) return *it;
    return nullptr;
}

Vertex* Graph::findVertexName(const string name) const {
    for (Vertex* vertex : vertexSet)
        if (vertex->airport.getName() == name)
            return vertex;
    return nullptr;
}

bool Graph::addVertex(const Airport &airport) {
    if (findVertex(airport) != nullptr)
        return false;

    vertexSet.insert(new Vertex(airport));
    return true;
}

bool Graph::addEdge(Vertex *sourc, Vertex* dest, const Airline* airline) {
    sourc->addEdge(dest, airline);
    return true;
}

vertexTab Graph::getVertexSet() const { return vertexSet; }

int Graph::getNumberVertex() const { return vertexSet.size(); }
