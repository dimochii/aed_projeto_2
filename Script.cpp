
#include <fstream>
#include <sstream>
#include <iostream>
#include "Script.h"

using namespace std;

void Script::infoCollection(Graph* graph, HashTable* hashTable) {
    ifstream File1("../dataset/airports.csv");
    if (File1.is_open()){
        string line;
        getline(File1, line);

        while(getline(File1, line)){
            istringstream iss(line);
            string code, name, city, country, latitudeS, longitudeS;

            getline(iss, code, ',');
            getline(iss, name, ',');
            getline(iss, city, ',');
            getline(iss, country, ',');
            getline(iss, latitudeS, ',');
            getline(iss, longitudeS);

            float latitude = stof(latitudeS);
            float longitude = stof(longitudeS);

            Airport airport = Airport(code, name, city, country, latitude, longitude);
            graph->addVertex(airport);
        }
    }
    File1.close();


    ifstream File2("../dataset/airlines.csv");
    if(File2.is_open()){
        string line;
        getline(File2, line);

        while(getline(File2, line)){
            istringstream iss(line);
            string code, name, callsign, country;

            getline(iss, code, ',');
            getline(iss, name, ',');
            getline(iss, callsign, ',');
            getline(iss, country);

            Airline airline = Airline(code, name, callsign, country);
            hashTable->addAirline(airline);
        }
    }
    File2.close();


    ifstream File3("../dataset/flights.csv");
    if(File3.is_open()){
        string line;
        getline(File3, line);
        while(getline(File3, line)){
            istringstream iss(line);
            string sourc, dest, code;

            getline(iss, sourc, ',');
            getline(iss, dest, ',');
            getline(iss, code);

            const Airline* airline = hashTable->findAirline(code);
            Vertex* source = graph->findVertexCode(sourc);
            Vertex* destination = graph->findVertexCode(dest);
            graph->addEdge(source, destination, airline);
        }
    }
    File3.close();
}