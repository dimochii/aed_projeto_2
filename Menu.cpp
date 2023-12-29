
#include <iostream>
#include <iomanip>
#include "Menu.h"
#include "Statistics.h"
#include "Filter.h"

using namespace std;

Menu::Menu() {}

Graph *Menu::getGraph() { return graph; }
HashTable *Menu::getHashTable() { return hashTable; }

bool Menu::getAirlineFilter() {return airlineFilter;}


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
    if (option == "1"){statistics();}
    if (option == "2"){sourceLocation();}
    if (option == "3"){filter();}
    if (option == "4"){closeMenu();}
}



void Menu::statistics() {
    cout << "What do you want to consult?" << endl;
    cout << "1.Numbers\n" << "2.Others\n" << "3.Go back\n";
    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2" || option == "3")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "1"){statisticsNumbers();}
    if (option == "2"){statisticsOthers();}
    if (option == "3"){initialOptions();}
}

void Menu::statisticsNumbers() {
    cout << "Which number do you want to see?" << endl;
    cout << "1.Total number of airports\n" << "2.Total number of flights\n" << "3.Number of flights and airlines out of an airport\n"
            << "4.Number of flights\n" << "5.Number of countries\n" << "6.Number of destinations for an airport\n"
            << "7.Number of destinations for an airport with X stops\n" << "8.Go back\n";
    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2" || option == "3" || option == "4" || option == "5" || option == "6" || option == "7" || option == "8")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "1") { Statistics::totalNumberAirports(graphAtual); askContinue(); }
    if (option == "2") { Statistics::totalNumberFlights(graphAtual); askContinue(); }
    if (option == "3") { Airport airport = askAirport(); Statistics::numFlightOutAir(graphAtual, airport); askContinue(); }
    if (option == "4") { statistics4(); }
    if (option == "5") { statistics5(); }
    if (option == "6") { Airport airport = askAirport(); string mode = askMode(); Statistics::numDestinationsAirport(graphAtual, airport, mode); askContinue(); }
    if (option == "7") { Airport airport = askAirport(); string mode = askMode(); int x = askX(); Statistics::numberReachable(graphAtual, airport, x, mode); askContinue(); }
    if (option == "8") { statistics(); }
}

void Menu::statistics4() {
    cout << "Per what?" << endl;
    cout << "1.Per city\n" << "2.Per airline\n";
    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "1"){ string city = askCity(); Statistics::flightsPerCity(graphAtual, city); askContinue();}
    if (option == "2"){ Airline airline = askAirline(); Statistics::flightsPerAirline(graphAtual, airline); askContinue();}
}

void Menu::statistics5() {
    cout << "1.That a given airport flies to\n" << "2.That a given city flies to\n";
    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "1") { Airport airport = askAirport(); Statistics::countriesPerAirport(graphAtual, airport); askContinue(); }
    if (option == "2") { string city = askCity(); Statistics::countriesPerCity(graphAtual, city); askContinue(); }
}

string Menu::askMode() {
    cout << "Which destinations?" << endl;
    cout << "1.Airports\n" << "2.Cities\n" << "3.Countries\n";
    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2" || option == "3")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "1") { return "airport"; }
    if (option == "2") { return "city"; }
    if (option == "3") { return "country"; }
    return " ";
}

bool isInteger(const std::string& s) {
    std::istringstream iss(s);
    int num;
    iss >> num;
    return iss.eof() && !iss.fail();
}

bool isDouble(const std::string &s) {
    try {
        std::stod(s);
        return true;
    } catch (...){
        return false;
    }
}


int Menu::askX() {
    cout << "Number of maximum stops: ";
    string n; cin >> n;

    while (!isInteger(n)) {
        cout << "Invalid, try again. Number of maximum stops: ";
        cin >> n;
    }

    cout << " " << endl;
    return stoi(n);
}


void Menu::statisticsOthers() {
    cout << "What do you want to see?" << endl;
    cout << "1.Flight trip(s) with the greatest number of stops\n"
         << "2.Top-k airport with the greatest number of flights (air traffic capacity)\n"
         << "3.Airports that are essential to the networks circulation capability\n"
         << "4.Go back\n";
    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2" || option == "3" || option == "4")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "1"){ Statistics::maxTrip(graphAtual); askContinue(); }
    if (option == "2"){ int k = askK(); Statistics::topKAirTraffic(graphAtual,k-1); askContinue(); }
    if (option == "3"){ Statistics::airport_art(graphAtual); askContinue(); }
    if (option == "4"){ initialOptions(); }
    cout << " " << endl;
}

int Menu::askK(){
    cout << "By what k-airport do you wish to search for?" << endl;
    cout << "Number: ";
    string option; cin >> option;

    while (!isInteger(option) || (stoi(option) <= 0)) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    return stoi(option);
}

void Menu::filter() {
    cout << "Filter search by airlines. ";
    if(airlineFilter) cout<<"(ON) \n"; else cout<<"(OFF) \n";
    if(airlineFilter) cout << "1.Change filter\n"; else cout << "1.Activate filter\n";
    cout << "2.Deactivate filter\n"
         << "3.Go back\n";

    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2"|| option == "3" )) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }
    cout << " " << endl;
    if (option == "1"){airlineFilter = true; activateFilter();}
    if (option == "2"){airlineFilter = false; graphAtual = graph; filter();}
    if (option == "3"){initialOptions();}
}

void Menu::activateFilter() {
    cout << "Which airlines do you wish to travel with? "<<"(ex: Ryanair,TAP Air Portugal)\n";
    cout << "Airlines: ";
    string names; getline(cin,names);
    getline(cin, names);
    istringstream iss(names);
    string airline;
    while (getline(iss, airline, ',')) {
        while (hashTable->findAirlineByName(airline) == nullptr) {
            cout << "Invalid input. "<< "Airlines: ";
            getline(cin, names);
            istringstream newIss(names);
            getline(newIss, airline, ',');
        }
    }
    auto airlineCodes = Filter::airlineFilter(names,hashTable);
    graphAtual = Filter::airlineFilterGraph(airlineCodes,graph,hashTable);
    cout << " " << endl;
    filter();
}


Airport Menu::askAirport() {
    cout << "How do you wish to search for the airport?" << endl;
    cout << "1.By the airport code\n" << "2.By the airport name\n";
    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "1"){ return askAirportCode(); }
    if (option == "2"){ return askAirportName(); }
    return Airport("DSM");
}

Airport Menu::askAirportCode() {
    cout << "Airport code: ";
    string code; cin >> code;

    auto itCode = graph->findVertexCode(code);
    while (itCode == nullptr) {
        cout << "Invalid, try again. Airport code: ";
        cin >> code;
        itCode = graph->findVertexCode(code);
    }
    cout << " " << endl;
    return itCode->getAirport();
}

Airport Menu::askAirportName() {
    bool first = true;
    string name; getline(cin, name);

    auto itName = graph->findVertexName(name);
    while (itName == nullptr) {
        if (first) { cout << "Airport name: "; first = false; }
        else cout << "Invalid, try again. Airport name:  ";
        getline(cin, name);
        itName = graph->findVertexName(name);
    }
    cout << " " << endl;
    return itName->getAirport();
}


Airline Menu::askAirline() {
    cout << "How do you wish to search for the airline?" << endl;
    cout << "1.By the airline code\n" << "2.By the airline name\n";
    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "1"){ return askAirlineCode(); }
    if (option == "2"){ return askAirlineName(); }
    return Airline();
}

Airline Menu::askAirlineCode() {
    cout << "Airline code: ";
    string code; cin >> code;

    auto itCode = hashTable->findAirline(code);
    while (itCode == nullptr) {
        cout << "Invalid, try again. Airline code: ";
        cin >> code;
        itCode = hashTable->findAirline(code);
    }
    cout << " " << endl;
    return *itCode;
}

Airline Menu::askAirlineName() {
    bool first = true;
    string name; getline(cin, name);

    auto itName = hashTable->findAirlineByName(name);
    while (itName == nullptr) {
        if (first) { cout << "Airline name: "; first = false; }
        else cout << "Invalid, try again. Airline name:  ";
        getline(cin, name);
        itName = hashTable->findAirlineByName(name);
    }
    cout << " " << endl;
    return *itName;
}


string Menu::askCity() {
    return " ";
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
        string code;

        bool valid=false;
        while(!valid) {
            cout << "Airport Code: ";
            cin >> code;
            for (auto airport: graph->getVertexSet()) {
                if (airport->getAirport().getCode() == code) {
                    valid=true;
                }
            }
            if(!valid){
                cout << "Invalid input. ";
            }
        }

        airportsSource = Filter::AirportCode(graph, code);

    }
    if (option == "2"){
        string name;

        bool valid=false;
        while(!valid) {
            cout << "Airport Name: ";
            cin >> name;
            for (auto airport: graph->getVertexSet()) {
                if (airport->getAirport().getName() == name) {
                    valid=true;
                }
            }
            if(!valid){
                cout << "Invalid input. ";
            }
        }

        airportsSource = Filter::AirportName(graph, name);

    }
    if (option == "3"){
        string city;

        bool valid=false;
        while(!valid) {
            cout << "City: ";
            cin >> city;
            for (auto airport: graph->getVertexSet()) {
                if (airport->getAirport().getCity() == city) {
                    valid=true;
                }
            }
            if(!valid){
                cout << "Invalid input. ";
            }
        }

        airportsSource = Filter::AirportsCity(graph, city);

    }
    if (option == "4"){
        cout << "Latitude: ";
        string latitude; cin >> latitude;

        while (!isDouble(latitude) || (stod(latitude) <= 0)) {
            cout << "Invalid input. Latitude: ";
            cin >> latitude;
        }

        cout << " " << endl;
        double lat = stod(latitude);

        cout << "Longitude: ";
        string longitude; cin >> longitude;

        while (!isDouble(longitude) || (stod(longitude) <= 0)) {
            cout << "Invalid input. Longitude: ";
            cin >> longitude;
        }

        cout << " " << endl;
        double lon = stod(longitude);

        airportsSource = Filter::geographicalLocation(graph, lat, lon);

        cout << "Closest Airport:"<<endl;
        for(auto air: airportsSource){
            cout<<air.getCode()<<endl;
        }
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
        string code;

        bool valid=false;
        while(!valid) {
            cout << "Airport Code: ";
            cin >> code;
            for (auto airport: graph->getVertexSet()) {
                if (airport->getAirport().getCode() == code) {
                    valid=true;
                }
            }
            if(!valid){
                cout << "Invalid input. ";
            }
        }

        airportsDest = Filter::AirportCode(graph, code);

    }
    if (option == "2"){
        string name;

        bool valid=false;
        while(!valid) {
            cout << "Airport Name: ";
            cin >> name;
            for (auto airport: graph->getVertexSet()) {
                if (airport->getAirport().getName() == name) {
                    valid=true;
                }
            }
            if(!valid){
                cout << "Invalid input. ";
            }
        }

        airportsDest = Filter::AirportName(graph, name);

    }
    if (option == "3"){
        string city;

        bool valid=false;
        while(!valid) {
            cout << "City: ";
            cin >> city;
            for (auto airport: graph->getVertexSet()) {
                if (airport->getAirport().getCity() == city) {
                    valid=true;
                }
            }
            if(!valid){
                cout << "Invalid input. ";
            }
        }
        airportsDest = Filter::AirportsCity(graph, city);

    }
    if (option == "4"){
        cout << "Latitude: ";
        string latitude; cin >> latitude;

        while (!isDouble(latitude) || (stod(latitude) <= 0)) {
            cout << "Invalid input. Latitude: ";
            cin >> latitude;
        }

        cout << " " << endl;
        double lat = stod(latitude);

        cout << "Longitude: ";
        string longitude; cin >> longitude;

        while (!isDouble(longitude) || (stod(longitude) <= 0)) {
            cout << "Invalid input. Longitude: ";
            cin >> longitude;
        }

        cout << " " << endl;
        double lon = stod(longitude);

        airportsDest = Filter::geographicalLocation(graph, lat, lon);

        cout << "Closest Airports:"<<endl;
        for(auto air: airportsDest){
            cout<<air.getCode()<<endl;
        }
    }
    if (option == "5"){sourceLocation();}
    cout << " " << endl;

    Filter::bestOptionNoFilters(graph, airportsSource, airportsDest);
    cout << " " << endl;
    cout << "Do you want to filter your options by minimum number of different airlines?" << endl;
    cout << "Yes\n" << "No\n" ;
    cout << "Answer: ";
    string op; cin >> op;

    while (!(op == "Yes" || op == "No" || op == "yes" || op == "no")) {
        cout << "Invalid input. Answer: ";
        cin >> option;
    }

    cout << " " << endl;

    if(op=="Yes" || op=="yes"){
        Filter::minAirlines(graph, airportsSource, airportsDest);
    }

    askContinue();
}

void Menu::askContinue() {
    cout << " " << endl;
    cout << "---------------------------------\n";
    cout << "Do you want to do something else?\n";
    cout << "Yes\n" << "No\n" ;
    cout << "Answer: ";
    string option; cin >> option;

    while (!(option == "Yes" || option == "No" || option == "yes" || option == "no")) {
        cout << "Invalid input. Answer: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "Yes" || option == "yes") { initialOptions(); }
    if (option == "No" || option == "no") { closeMenu(); }
}
