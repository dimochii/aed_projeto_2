#ifndef AIRPORTSPROJECT_GRAPH_H
#define AIRPORTSPROJECT_GRAPH_H


#include <algorithm>
#include <cstddef>
#include <vector>
#include <queue>
#include <stack>
#include <list>
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

public:
    Vertex(Airport airport);

    void setVisited(bool cond);
    bool isVisited() const;
    void setProcessing(bool cond);
    bool isProcessing() const;

    void setNum(int num);
    int getNum() const;
    void setLow(int low);
    int getLow() const;

    const Airport &getAirport() const;
    const vector<Edge> &getFlights() const;
    int getNumberFlights() const;

    bool operator<(const Vertex& other) const;

    friend class Graph;
};


class Edge {
    const Airline * airline;
    Vertex * destination;

public:
    Edge(Vertex * destination, const Airline * airline);

    Airline getAirline() const;
    Vertex* getDestination() const;

    friend class Graph;
    friend class Vertex;
};



struct vertexHash
{
    // Hash function
    int operator() (Vertex* vertex) const {
        string str = vertex->getAirport().getCode();
        int v = 0;
        for (unsigned int i = 0; i < str.size(); i++)
            v = 37*v + str[i];
        return v;
    }

    // Equality function
    bool operator() (Vertex* vert1, Vertex* vert2) const {
        return vert1->getAirport().getCode() == vert2->getAirport().getCode();
    }
};

typedef unordered_set<Vertex*, vertexHash, vertexHash> vertexTab;

class Graph {
    vertexTab vertexSet;

public:
    Vertex* findVertex(const Airport &airport) const;
    Vertex* findVertexCode(const string code) const;
    Vertex* findVertexName(const string name) const;
    bool addVertex(const Airport & airport);
    bool addEdge(Vertex *sourc, Vertex* dest, const Airline* airline);
    vertexTab getVertexSet() const;
    int getNumberVertex() const;
};
#endif //AIRPORTSPROJECT_GRAPH_H