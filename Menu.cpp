
#include <iostream>
#include <iomanip>
#include "Menu.h"
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
    if (option == "1"){}
    if (option == "2"){}
    if (option == "3"){}
    if (option == "4"){}
    if (option == "5"){}
    if (option == "6"){}
    if (option == "7"){}
    if (option == "8"){initialOptions();}
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

/*
Vertex* Menu::chooseAirportCode() {
    cout << "Aiport code: ";
    string code; cin >> code;

    auto itCode = graph->findVertexAirport(code);
    while ( ) {
        cout << "Invalid, try again. Aiport code: ";
        cin >> code;
        itCode = graph->findVertexAirport(code);
    }
    return " ";
}

Vertex* Menu::chooseAirportName() {
    return "";
}

 */
