
#include <iostream>
#include <iomanip>
#include "Menu.h"
#include "Statistics.h"

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
// DIANA
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
