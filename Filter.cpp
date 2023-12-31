
#include <set>
#include <cmath>
#include <iostream>
#include <sstream>
#include "Filter.h"
#include "AirTable.h"

/**
 * @brief Verifica quais são os airports mais perto das coordenadas dadas.
 *
 * Esta função retorna um vetor de aeroportos com base na proximidade geográfica
 * de um ponto de referência representado por uma latitude e longitude.
 *
 * @complexity O(V).
 *
 * @param graph - Ponteiro para o grafo contendo os aeroportos (vértices) e respetivas airlines (arestas).
 * @param lat - latitude dada.
 * @param lon - longitude dada.
 * @return vector - Retorna vetor com os airports mais próximos das coordenadas dadas.
*/
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

/**
 * @brief Calcula a distância entre dois pontos na Terra usando a fórmula de Haversine.
 *
 * Esta função calcula a distância entre dois pontos na Terra dadas suas latitudes e longitudes.
 * A fórmula de Haversine é usada para este cálculo.
 *
 * @param lat1 - Latitude do primeiro ponto em graus.
 * @param lon1 - Longitude do primeiro ponto em graus.
 * @param lat2 - Latitude do segundo ponto em graus.
 * @param lon2 - Longitude do segundo ponto em graus.
 * @return float - Retorna a distância entre os dois pontos.
 */
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

/**
 * @brief Verifica quais são os airports numa dada cidade.
 *
 * Esta função percorre o conjunto de vértices do graph e coleta todos os aeroportos que pertencem à cidade especifica.
 *
 * @complexity O(V).
 *
 * @param graph - Ponteiro para o grafo contendo os aeroportos (vértices) e respetivas airlines (arestas).
 * @param city - cidade dada.
 * @return vector - Retorna vetor com os airports da cidade dada.
*/
vector<Airport> Filter::AirportsCity(Graph *g, string city){
    vector<Airport> res;
    for(auto airport: g->getVertexSet()){
        if(airport->getAirport().getCity()==city){
            res.push_back(airport->getAirport());
        }
    }
    return res;
}

/**
 * @brief Verifica e exibe quais são as opcções com menos paragens entre os airports de origem e destino.
 *
 * Esta função determina as melhores opções para a viagem com base nas combinações de aeroportos de origem e destino fornecidos.
 * A função imprime as opções disponíveis e suas respetivas informações de voo.
 *
 * @complexity O(V + E).
 *
 * @param graph - Ponteiro para o grafo contendo os aeroportos (vértices) e respetivas airlines (arestas).
 * @param sourceV - vetor com airports de origem.
 * @param destV - vetor com airports de destino.
 * @return true se houver pelo menos uma opção, else false.
*/
bool Filter::bestOptionNoFilters(Graph* g, vector<Airport> sourceV, vector<Airport> destV){
    bool available=true;
    vector<vector<pair<Airline, Vertex*>>> bestOptions;
    bestOptions= bestOptionMix(g, sourceV, destV);
    int i=0;
    if(bestOptions.empty()){
        cout << "No available options"<<endl;
        available=false;
    }
    for (auto vetor: bestOptions) {
        if(vetor.size()==1){
            cout<<"No available options"<<endl;
            available=false;
            break;
        }
        else {
            bool first = true;
            string lastA;
            string lastC;
            i++;
            cout << "Option " << i << ":" << endl;
            for (auto p: vetor) {
                if (first) {
                    first = false;
                } else {
                    cout << lastA << "[" << lastC << "]" " ----->" << ' ' << p.second->getAirport().getCode() << "["
                    << p.second->getAirport().getCity() << "] " << "Airline: " << p.first.getCode() << endl;
                }
                lastA = p.second->getAirport().getCode();
                lastC = p.second->getAirport().getCity();
            }
            cout << endl;
        }
    }
    return available;
}

/**
 * @brief Verifica qual é o caminho com menos paragens entre dois vértices do graph.
 *
 * Esta função utiliza uma abordagem de busca em largura (BFS) para encontrar o caminho mínimo entre dois vértices em um graph.
 * O caminho é representado como uma lista de pares contendo a airline e o vértice (airport) associado.
 *
 * @complexity O(V + E).
 *
 * @param source - vértice de origem.
 * @param dest - vértice de destino.
 * @return vector - Retorna vetor de vetores de pares com airline de uma aresta e restivo vértice de destino dessa aresta.
*/
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
    if(res.size()==0){
        return vector<vector<pair<Airline, Vertex*>>>();
    }
    return res;
}

/**
 * @brief Verifica qual é o caminho com menos paragens entre airports de origem e destino.
 *
 * Esta função calcula as melhores opções de rotas entre aeroportos de origem e destino.
 * A função utiliza a função minPathAirports para determinar os caminhos mínimos entre cada par de aeroportos de origem e destino.
 *
 * @complexity O((V+E)×n×m+k) -> n: number of elements of sourceV; m: number of elements of destV; k: number of elements in filtered options;
 *
 * @param sourceV - vector com airports de origem.
 * @param destV - vector com airports de destino.
 * @return vector - Retorna vetor de vetores de pares com airline de uma aresta e restivo vértice de destino dessa aresta.
*/
vector<vector<pair<Airline, Vertex*>>> Filter::bestOptionMix(Graph* g, vector<Airport> sourceV, vector<Airport> destV){
    int min=100000;
    vector<vector<pair<Airline, Vertex*>>> bestOptions;
    for(auto airportS_: sourceV){
        for(auto airportD_: destV){
            Vertex* airportS = g->findVertex(airportS_);
            Vertex* airportD = g->findVertex(airportD_);
            vector<vector<pair<Airline, Vertex*>>> current=minPathAirports(g, airportS, airportD);

            if(current.size()!=0 && current[0].size()<min){
                min=current[0].size();
                bestOptions.clear();
                bestOptions=current;
            }
            else if(current.size()!=0 && current[0].size()==min){
                for(auto option: current){
                    bestOptions.push_back(option);
                }
            }
        }
    }
    return bestOptions;
}

/**
 * @brief Verifica qual é o caminho com menos paragens entre dois vértices do graph e que minimiza o número de airlines diferentes.
 *
 * Esta função avalia as opções de rotas previamente determinadas pela função bestOptionMix,
 * e filtra aquelas que envolvem o menor número de airlines distintas.
 *
 * @complexity O((V+E)×n×m+k) -> n: number of elements of sourceV; m: number of elements of destV; k: number of elements in filtered options;
 *
 * @param sourceV - vector com airports de origem.
 * @param destV - vector com airports de destino.
*/
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

/**
 * @brief Verifica quais as airlines filtradas.
 *
 * Esta função recebe uma string contendo nomes de airlines.
 * Procura na hash table de airlines as airlines especificadas e obtem os códigos correspondentes
 * e retorna um vetor contendo esses códigos.
 *
 * @param str - string com airlines escolhidas.
 * @param airTable - hash table com airlines.
 * @return vector - Retorna vetor com códigos das airlines filtradas.
*/
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

/**
 * @brief Filtra as airlines de acordo com as airlines escolhidas.
 *
 * Esta função cria um novo graph que contém apenas vértices e arestas associados às companhias aéreas fornecidas.
 *
 * @complexity O(n+m) + O(V⋅E+E⋅m)  (onde n é o nome da companhia e m é o número total de companhias aéreas)
 *
 * @param airlineCodes - vector com códigos das airlines escolhidas.
 * @param graph - graph.
 * @param airTable - hash table com airlines.
 * @return Graph* - Retorna graph filtrado de acordo com as airlines escolhidas.
*/
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