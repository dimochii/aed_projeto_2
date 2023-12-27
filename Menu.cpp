
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
    cout << "1.Schedule\n" << "2.Students\n" << "3.Numbers\n" << "4.Student\n" << "5.Go back\n";
    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2" || option == "3" || option == "4" || option == "5")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "1"){consultSchedule();}
    if (option == "2"){consultStudents();}
    if (option == "3"){consultNumbers();}
    if (option == "4"){consultStudent();}
    if (option == "5"){initialOptions();}
}