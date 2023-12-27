
#include "Graph.h"

//VERTEX
Vertex::Vertex(Airport airport_): airport(airport_) {}

void Vertex::addEdge(Vertex *dest, const Airline* airline) {
    flights.push_back(Edge(dest, airline));
}

bool Vertex::removeEdgeTo(Vertex *dest) {
    for (auto it = flights.begin(); it != flights.end(); it++) {
        if (it->destination == dest) {
            flights.erase(it);
            return true;
        }
    }
    return false;
}

void Vertex::setVisited(bool cond) { visited = cond; }

bool Vertex::isVisited() const { return visited; }

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
    for (auto vertex : vertexSet)
        if (vertex->airport == airport)
            return vertex;
    return NULL;
}

Vertex*  Graph::findVertexAirport(const string code_) const {
    for (auto v : vertexSet)
        if (v->airport.getCode() == code_)
            return v;
    return NULL;
}

bool Graph::addVertex(const Airport &airport) {
    if (findVertex(airport) != NULL)
        return false;

    vertexSet.push_back(new Vertex(airport));
    return true;
}

bool Graph::removeVertex(const Airport &airport) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
        if ((*it)->airport  == airport) {
            Vertex* vertex = *it;
            vertexSet.erase(it);

            for (auto vertex2 : vertexSet)
                vertex2->removeEdgeTo(vertex);
            delete vertex;

            return true;
        }
    return false;
}

bool Graph::addEdge(Vertex *sourc, Vertex* dest, const Airline* airline) {
    sourc->addEdge(dest, airline);
    return true;
}



bool Graph::removeEdge(Vertex* sourc, Vertex* dest) {
    return sourc->removeEdgeTo(dest);
}

vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

int Graph::getNumberVertex() const {
    return vertexSet.size();
}
