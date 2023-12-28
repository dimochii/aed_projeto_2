
#include <iostream>
#include <iomanip>
#include "Menu.h"
#include "Statistics.h"
#include "Filter.h"

using namespace std;

Menu::Menu() {}

Graph *Menu::getGraph() { return graph; }
HashTable *Menu::getHashTable() { return hashTable; }

void Menu::setAirlineFilter(bool airlineFilter) {this->airlineFilter = airlineFilter;}
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
    if (option == "2"){bestFlight();}
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
    if (option == "3") {
        Airport airport = askAirport(); Statistics::numFlightOutAir(graphAtual, airport); askContinue(); }
    if (option == "4") {
        }
    if (option == "5") {}
    if (option == "6") { }
        //Airport airport = askAirport(); string mode = askMode(); Statistics::numDestinationsAirport(graphAtual, airport, mode); askContinue(); }
    if (option == "7") {}
        //Airport airport = askAirport(); int x = askNumber(); Statistics::numDestinationsAirport(graphAtual, airport, x); askContinue(); }
    if (option == "8") { statistics(); }
}

/*
void Menu::statistics4() {
    cout << "How do you wish to search for the airport?" << endl;
    cout << "1.By the airport code\n" << "2.By the airport name\n";
    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "1"){ return " "; }
    if (option == "2"){ return " "; }
}
 */


string Menu::askMode() {
    cout << "How do you wish to search for the airport?" << endl;
    cout << "1.By the airport code\n" << "2.By the airport name\n";
    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "1"){ return " "; }
    if (option == "2"){ return " "; }
}

void Menu::statisticsOthers() {
    cout << "What do you want to see?" << endl;
    cout << "1.Flight trip(s) with the greatest number of stops\n"
            << "2.Top-k airport with the greatest number of flights (air traffic capacity)\n"
            << "3.Airports that are essential to the network’s circulation capability\n"
            << "4.Go back\n";
    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2" || option == "3" || option == "4")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "1"){}
    if (option == "2"){}
    if (option == "3"){}
    if (option == "4"){initialOptions();}
}

void Menu::bestFlight() {
// MARTA
}

void Menu::filter() {
    cout << "Filter search by airlines. ";
    if(getAirlineFilter()) cout<<"(ON) \n"; else cout<<"(OFF) \n";
    if(getAirlineFilter()) cout << "1.Change filter\n"; else cout << "1.Activate filter\n";
    cout << "2.Deactivate filter\n"
         << "3.Go back\n";

    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2"|| option == "3" )) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }
    cout << " " << endl;
    if (option == "1"){this->setAirlineFilter(true); activateFilter();}
    if (option == "2"){this->setAirlineFilter(false); graphAtual = graph; filter();}
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
    graphAtual = Filter::airlineFilterGraph(airlineCodes,graphAtual,hashTable);
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
