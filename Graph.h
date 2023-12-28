#ifndef AIRPORTSPROJECT_GRAPH_H
#define AIRPORTSPROJECT_GRAPH_H


#include <cstddef>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>
#include "Airport.h"
#include "HashTable.h"

using namespace std;

class Edge;
class Graph;
class Vertex;

class Vertex {
    Airport airport;
    vector<Edge> flights;

    bool visited;
    bool processing;
    int num;
    int low;

    void addEdge(Vertex *dest, const Airline *airline);
    bool removeEdgeTo(Vertex *dest);

public:
    Vertex(Airport airport);
    void setVisited(bool cond);
    bool isVisited() const;
    void setProcessing(bool cond);
    bool isProcessing() const;

    const Airport &getAirport() const;
    const vector<Edge> &getFlights() const;
    int getNumberFlights() const;
    int getNum() const;
    void setNum(int num);
    int getLow() const;
    void setLow(int low);
    bool operator <(const Vertex& other) const;

    friend class Graph;
};


class Edge {
    Vertex * destination;
    const Airline * airline;

public:
    Edge(Vertex * destination, const Airline * airline);

    Airline getAirline() const;
    Vertex* getDestination() const;

    friend class Graph;
    friend class Vertex;
};


class Graph {
    vector<Vertex*> vertexSet;

public:
    Vertex *findVertex(const Airport &airport) const;
    Vertex *findVertexAirport(const string code_) const;
    bool addVertex(const Airport & airport);
    bool removeVertex(const Airport & airport);
    bool addEdge(Vertex *sourc, Vertex* dest, const Airline* airline);
    bool removeEdge(Vertex* sourc, Vertex* dest);
    vector<Vertex *> getVertexSet() const;
    int getNumberVertex() const;
};
#endif //AIRPORTSPROJECT_GRAPH_H