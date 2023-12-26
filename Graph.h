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

    const Airport &getAirport() const;
    const vector<Edge> &getFlights() const;
    int getNumberFlights() const;
    int getNum() const;
    void setNum(int num);
    int getLow() const;
    void setLow(int low);
    bool operator <(const Vertex& other) const;
    /*
    Airport getInfo() const;
    void setInfo(Airport in);
    void setVisited(bool v);
    bool isProcessing() const;
    void setProcessing(bool p);
    const vector<Edge> &getAdj() const;
    void setAdj(const vector<Edge> &adj);

    int getIndegree() const;

    void setIndegree(int indegree);

    int getNum() const;

    void setNum(int num);

    int getLow() const;

    void setLow(int low);
     */

    friend class Graph;
};


class Edge {
    Vertex * destination;
    const Airline * airline;

public:
    Edge(Vertex * destination, const Airline * airline);
    /*
    Vertex<Airport> *getDest() const;
    void setDest(Vertex<Airport> *dest);
    double getWeight() const;
    void setWeight(double weight);
     */
    friend class Graph;
    friend class Vertex;

    Airline getAirline() const;
    Vertex* getDestination() const;

};


class Graph {
    vector<Vertex*> vertexSet;

    /*
    int index;
    stack<Vertex<Airport>> _stack_;           // auxiliary field
    list<list<Airport>> _list_sccs_;        // auxiliary field

    void dfsVisit(Vertex<Airpot> *v,  vector<Airport> & res) const;
    void dfsVisitS(Vertex<Airport> *v, stack<Airport> &s) const;
    bool dfsIsDAG(Vertex<Airport> *v) const;
     */

public:
    Vertex *findVertex(const Airport &airport) const;
    Vertex *findVertexAirport(const string code_) const;
    bool addVertex(const Airport & airport);
    bool removeVertex(const Airport & airport);
    bool addEdge(Vertex *sourc, Vertex* dest, const Airline* airline);
    bool removeEdge(Vertex* sourc, Vertex* dest);
    vector<Vertex *> getVertexSet() const;
    int getNumberVertex() const;
    /*
    vector<Airport> dfs() const;
    vector<Airport> dfs(const Airport & source) const;
    vector<Airport> bfs(const Airport &source) const;
    vector<Airport> topsort() const;
    bool isDAG() const;
     */
};
#endif //AIRPORTSPROJECT_GRAPH_H