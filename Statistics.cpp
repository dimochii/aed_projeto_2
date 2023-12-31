
#include <iostream>
#include <set>
#include "Statistics.h"

/**
 * @brief Calcula e exibe o número total de aeroportos no grafo.
 * @complexity O(1)
 *
 * @param graph - Ponteiro para o grafo contendo os aeroportos (vértices) e respetivas airlines (arestas).
 */
void Statistics::totalNumberAirports(Graph* graph) {
    cout << "Total number of airports: " << graph->getNumberVertex() << endl;
}

/**
 * @brief Calcula e exibe o número total de voos no grafo.
 * @complexity O(V)
 * @param graph - Ponteiro para o grafo contendo os aeroportos (vértices) e respetivas airlines (arestas).
 */
void Statistics::totalNumberFlights(Graph* graph) {
    int num = 0;
    for (Vertex* vertex: graph->getVertexSet())
        num += vertex->getNumberFlights();
    cout << "Total number of flights: " << num << endl;
}

/**
 * @brief Calcula e exibe o número de voos saindo de um aeroporto específico.
 * @complexity O(log N).
 *
 * @param graph - Ponteiro para o grafo contendo os aeroportos (vértices) e respetivas airlines (arestas).
 * @param airport - Aeroporto para o qual o número de voos saindo será calculado.
 */
void Statistics::numFlightOutAir(Graph* graph,Airport airport) {
    set<Airline> outAirlines;
    auto it = graph->findVertex(airport);
    int num = it->getFlights().size();

    for (auto e : it->getFlights())
        outAirlines.insert(e.getAirline());

    cout <<"Number of flights out of "<<airport.getCode()<<": "<<num<<endl;
    cout <<"Out of "<<outAirlines.size()<<" different airlines."<<endl;
}

/**
 * @brief Calcula e exibe o número de voos de uma cidade específica.
 * @complexity O(V).
 *
 * @param graph - Ponteiro para o grafo contendo os aeroportos (vértices) e respetivas airlines (arestas).
 * @param city - string com cidade para a qual será calculada o número de voos.
 */
void Statistics::flightsPerCity(Graph* g, string city) {
    int count=0;
    for (auto vertex: g->getVertexSet()) {
        if (vertex->getAirport().getCity()==city)
            count+=vertex->getFlights().size();
    }
    cout << "Number of flights on city " << city << ": " << count << endl;
}

/**
 * @brief Calcula e exibe o número de voos de uma airline específica.
 * @complexity O(V * E)
 *
 * @param graph - Ponteiro para o grafo contendo os aeroportos (vértices) e respetivas airlines (arestas).
 * @param airline - airline para a qual será calculada o número de voos.
 */
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

/**
 * @brief Calcula e exibe o número de países para os quais uma cidade específica tem voos..
 * @complexity O(V * E).
 *
 * @param graph - Ponteiro para o grafo contendo os aeroportos (vértices) e respetivas airlines (arestas).
 * @param city - string com cidade escolhida.
 */
void Statistics::countriesPerCity(Graph* g, string city) {
    set<string> countries;
    for (auto vertex: g->getVertexSet()) {
        if (vertex->getAirport().getCity() == city) {
            for (auto edge: vertex->getFlights()) {
                auto dest = edge.getDestination();
                string country = dest->getAirport().getCountry();
                countries.insert(country);
            }
        }
    }
    cout << "Number of countries that the city " << city << " flies to: " << countries.size() << endl;
}

/**
 * @brief Calcula e exibe o número de países para os quais um airport específico tem voos..
 * @complexity O(V + E).
 *
 * @param graph - Ponteiro para o grafo contendo os aeroportos (vértices) e respetivas airlines (arestas).
 * @param airport - airport escolhido.
 */
void Statistics::countriesPerAirport(Graph* g, Airport airport) {
    set<string> countries;
    for (auto vertex: g->getVertexSet()) {
        if (vertex->getAirport().getCode() == airport.getCode()) {
            for (auto edge: vertex->getFlights()) {
                auto dest = edge.getDestination();
                string country = dest->getAirport().getCountry();
                countries.insert(country);
            }
        }
    }
    cout << "Number of countries that the airport " << airport.getCode() << " flies to: " << countries.size() << endl;
}

/**
 * @brief Visita recursivamente os aeroportos de destino a partir de um vértice específico.
 *
 * Esta função visita os aeroportos de destino a partir de um vértice dado e coleta informações
 * dependendo da opção fornecida.
 *
 * @complexity O(V + E).
 *
 * @param v - vértice a partir do qual iniciar a visita.
 * @param res - set para armazenar as informações coletadas (cidades, países ou nomes de aeroportos).
 * @param fOption - opção que determina o tipo de informação a ser coletada ("city", "country" ou "airport").
 */
void Statistics::numDestAirportVisit(Vertex *v, set<string> & res, string & fOption) {
    v->setVisited(true);
    if (fOption == "city") res.insert(v->getAirport().getCity());
    else if (fOption == "country") res.insert(v->getAirport().getCountry());
    else if (fOption == "airport") res.insert(v->getAirport().getName());

    for (auto & e : v->getFlights()) {
        auto w = e.getDestination();
        if ( ! w->isVisited())
            numDestAirportVisit(w, res, fOption);
    }
}

/**
 * @brief Calcula e exibe o número de destinos distintos que um airport específico tem voos..
 *
 * Esta função calcula o número de destinos distintos que um airport tem voos, dependendo da opção fornecida.
 *
 * @complexity O(V + E).
 *
 * @param graph - Ponteiro para o grafo contendo os aeroportos (vértices) e respetivas airlines (arestas).
 * @param source - airport para qual vai ser calculado o número de voos.
 * @param fOption - opção que determina o tipo de destino ("city", "country" ou "airport").
 */
void Statistics::numDestinationsAirport( Graph *graph, Airport source, string fOption) {
    set<string> res;
    Vertex* vSource = graph->findVertex(source);

    for (auto v : graph->getVertexSet())
        v->setVisited(false);

    numDestAirportVisit(vSource, res, fOption);
    cout << "The airport " << source.getCode() << " has " << res.size() <<" different "<< fOption << " destinations." << endl;
}

/**
 * @brief Calcula os destinos alcançáveis a partir de um aeroporto com um número máximo de paragens.
 *
 * @complexity O(V + E).
 *
 * @param graph - Ponteiro para o grafo contendo os aeroportos (vértices) e respetivas airlines (arestas).
 * @param source - airport de partida.
 * @param num - número máximo de paradas.
 * @return vector - Retorna vetor com pointer para vértices (airports) que um airport consegue alcançar no número máximo de paragens.
 */
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

/**
 * @brief Calcula e exibe o número de destinos alcançáveis a partir de um aeroporto com um número máximo de paragens.
 *
 * @complexity O(V + E).
 *
 * @param graph - Ponteiro para o grafo contendo os aeroportos (vértices) e respetivas airlines (arestas).
 * @param source - airport de partida.
 * @param num - número máximo de paradas.
 * @param mode - modo de cálculo (aeroporto, cidade ou país).
 */
void Statistics::numberReachable(Graph* graph, Airport source, int num, string mode) {
    set<string> res;
    vector<Vertex *> reachableDest = reachableDestinations(graph, source, num);

    if (mode == "airport") {
        cout << "The airport " << source.getCode() << " has " << reachableDest.size() <<" different "<< mode
        << " destinations with " << num << " stops." << endl;

    }
    else if (mode == "city") {
        for (Vertex * vertex: reachableDest)
            res.insert(vertex->getAirport().getCity());
        cout << "The airport " << source.getCode() << " has " << res.size() <<" different "<< mode
             << " destinations with " << num << " stops." << endl;
    }
    else if (mode == "country") {
        for (Vertex * vertex: reachableDest)
            res.insert(vertex->getAirport().getCountry());
        cout << "The airport " << source.getCode() << " has " << res.size() <<" different "<< mode
             << " destinations with " << num << " stops." << endl;
    }
}

/**
 * @brief Encontra o maior número de paragens possíveis em uma viagem a partir de um aeroporto.
 *
 * @complexity O(V + E).
 *
 * @param graph - Ponteiro para o grafo contendo os aeroportos (vértices) e respetivas airlines (arestas).
 */
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

/**
 * @brief Encontra o maior número de paragens possíveis em uma viagem a partir de um aeroporto.
 *
 * @complexity O(V + E).
 *
 * @param graph - Ponteiro para o grafo contendo os aeroportos (vértices) e respetivas airlines (arestas).
 */
void Statistics::maxTrip(Graph* graph) {
    vector<pair<Airport,Airport>> pairsMax; int numMax = 0;
    for (Vertex* vertex: graph->getVertexSet())
        maxTripVertex(graph, vertex, pairsMax, numMax);

    cout << "The maximum trip has " << numMax << " stops." << endl;
    for (auto i: pairsMax)
        cout << "- From " << i.first.getCode() << " to " << i.second.getCode() << endl;
}


struct CompareVertices {
    bool operator()(const Vertex* v1, const Vertex* v2) const {
        return (v1->getNumberFlights() + v1->getIndegree()) < (v2->getNumberFlights() + v2->getIndegree());
    }
};

/**
 * @brief Calcula e exibe os aeroportos com o tráfego mais alto, considerando o número de voos e o grau de entrada.
 *
 * @complexity O(V * LOG(V) + E).
 *
 * @param graph - Ponteiro para o grafo contendo os aeroportos (vértices) e respetivas airlines (arestas).
 * @param k - número máximo de aeroportos a serem exibidos.
 */
void Statistics::topKAirTraffic(Graph *graph, int k) {
    std::priority_queue<Vertex*, std::vector<Vertex*>, CompareVertices> airportPriorityQueue;
    queue<Vertex *> vQueue;

    for (auto vertex : graph->getVertexSet()) {
        for (auto edge: vertex->getFlights()) {
            auto w = edge.getDestination();
            w->setIndegree(w->getIndegree()+1);
        }
    }
    for (auto vertex : graph->getVertexSet()) {
        airportPriorityQueue.push(vertex);
    }

    for(int i = 0; i <= min(k,3018); i++){
        auto trafficVert = airportPriorityQueue.top();
        cout<< i+1<<": " << trafficVert->getAirport().getName() <<" ("<<trafficVert->getAirport().getCode()<<')'<<endl;
        if(!airportPriorityQueue.empty())airportPriorityQueue.pop();
    }

}

/**
 * @brief Função auxiliar para o algoritmo de identificação de pontos de articulação.
 *
 * @complexity O(V + E).
 *
 * @param g - Ponteiro para o grafo contendo os aeroportos (vértices) e respetivas airlines (arestas).
 * @param v - Vértice atual durante a travessia DFS.
 * @param l - Conjunto para armazenar os pontos de articulação encontrados.
 * @param i - ordem do vértice.
 */
void Statistics::dfs_art(Graph*g, Vertex*v, unordered_set<string> &l, int &i) {
    v->setNum(i); v->setLow(i);
    v->setProcessing(true); i++;
    int trees=0;

    for(auto edge: v->getFlights()){
        auto destV=edge.getDestination();
        if (destV->getNum()==-1) {
            trees++;
            dfs_art(g, destV, l, i);
            v->setLow(min(destV->getLow(), v->getLow()));

            if ((destV->getLow()>=v->getNum() && v->getNum()!=1) || (v->getNum()==1 && trees>1))
                l.insert(v->getAirport().getCode());
        }
        else if (v->isProcessing())
            v->setLow(min(destV->getNum(), v->getLow()));
    }

    v->setProcessing(false);
}

/**
 * @brief Identifica e exibe os aeroportos essenciais (pontos de articulação) no grafo.
 *
 * @complexity O(V + E).
 *
 * @param g - Ponteiro para o grafo contendo os aeroportos (vértices) e respetivas airlines (arestas).
 */
void Statistics::airport_art(Graph *g) {
    unordered_set<string> art;
    int i = 1;

    for(auto vertex: g->getVertexSet()){
        vertex->setNum(-1);
        vertex->setProcessing(false);
    }

    for(auto vertex: g->getVertexSet()){
        if(vertex->getNum()==-1)
            dfs_art(g, vertex, art, i);
    }

    cout << "There are " << art.size() << " airports that are essential. Airports:" << endl;

    int line = -1;
    for(string airport: art) {
        line++;
        if (line == 17) {cout << endl; line = 0;}
        cout << airport << " | " ;
    }
    cout << endl;
}
