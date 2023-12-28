
#include <iostream>
#include <iomanip>
#include "Menu.h"
#include "Filter.h"
#include "Script.h"
#include "HashTable.h"
#include "Graph.h"
using namespace std;

Menu::Menu() {}

Graph *Menu::getGraph() { return graph; }
HashTable *Menu::getHashTable() { return hashTable; }

void Menu::openMenu() {
    cout << setw(25) << "Welcome!" << endl;
    initialOptions();
}

int Menu::closeMenu() {
    return 0;
}


void Menu::initialOptions() {
    cout << "What do you want to do?" << endl;
    cout << "1. Statistics\n" << "2. Best flight option\n" << "3. Filter\n" << "4. Quit\n";
    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2" || option == "3" || option == "4")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "1"){}
    if (option == "2"){sourceLocation();}
    if (option == "3"){}
    if (option == "4"){closeMenu();}
}



void Menu::sourceLocation() {
    cout << "How do you want to specify your source location?" << endl;
    cout << "1.Airport code\n" << "2.Airport name\n" << "3.City\n" << "4.Geographical coordinates\n" << "5.Go back\n";
    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2" || option == "3" || option == "4" || option == "5")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }
    cout << " " << endl;
    vector<Airport> airportsSource;
    if (option == "1"){
        cout << "Airport Code: ";
        string code; cin >> code;

        airportsSource = Filter::AirportCode(graph, code);

    }
    if (option == "2"){
        cout << "Airport Name: ";
        string name; cin >> name;

        airportsSource = Filter::AirportName(graph, name);

    }
    if (option == "3"){
        cout << "City: ";
        string city; cin >> city;

        airportsSource = Filter::AirportsCity(graph, city);

    }
    if (option == "4"){
        cout << "Latitude: ";
        double latitude; cin >> latitude;

        cout << "Longitude: ";
        double longitude; cin >> longitude;

        airportsSource = Filter::geographicalLocation(graph, latitude, longitude);

    }
    if (option == "5"){initialOptions();}

    cout << " " << endl;
    destinationLocation(airportsSource);
}

void Menu::destinationLocation(vector<Airport> airportsSource){
    cout << "How do you want to specify your destination location?" << endl;
    cout << "1.Airport code\n" << "2.Airport name\n" << "3.City\n" << "4.Geographical coordinates\n" << "5.Go back\n";
    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2" || option == "3" || option == "4" || option == "5")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }
    cout << " " << endl;
    vector<Airport> airportsDest;
    if (option == "1"){
        cout << "Airport Code: ";
        string code; cin >> code;

        airportsDest = Filter::AirportCode(graph, code);

    }
    if (option == "2"){
        cout << "Airport Name: ";
        string name; cin >> name;

        airportsDest = Filter::AirportName(graph, name);

    }
    if (option == "3"){
        cout << "City: ";
        string city; cin >> city;

        airportsDest = Filter::AirportsCity(graph, city);

    }
    if (option == "4"){
        cout << "Latitude: ";
        double latitude; cin >> latitude;

        cout << "Longitude: ";
        double longitude; cin >> longitude;

        airportsDest = Filter::geographicalLocation(graph, latitude, longitude);

    }
    if (option == "5"){sourceLocation();}

    /*cout << " " << endl;
    for(auto i: airportsSource){
        cout<<i.getCode()<< ' ';
    }
    cout<<endl;
    for (auto d: airportsDest){
        cout<<d.getCode()<<' ';
    }
    cout<<"ola";*/
    cout << " " << endl;
    Filter::bestOptionNoFilters(graph, airportsSource, airportsDest);
    askContinue();
}

void Menu::askContinue() {
    cout << "\nDo you want to do something else?" << endl;
    cout << "Yes\n" << "No\n" ;
    cout << "Answer: ";
    string option; cin >> option;

    while (!(option == "Yes" || option == "No")) {
        cout << "Invalid input. Answer: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "Yes") { initialOptions(); }
    if (option == "No") { closeMenu(); }
}