
#include <algorithm>
#include "HashTable.h"

Airline::Airline(string code_, string name_, string callsign_, string country_): code(code_),
                                        name(name_), callsign(callsign_), country(country_) {}

string Airline::getCode() const {return code; }
bool Airline::operator < ( const Airline& air) const {
    return code<air.getCode();
}

Airline::Airline() {}

HashTable::HashTable() {}

void HashTable::addAirline (const Airline& airline) { airlines.insert(airline); }

const Airline* HashTable::findAirline (const string& code) {
    auto it = airlines.find(Airline(code, "", "", ""));
    if (it != airlines.end()) return &(*it);
    return nullptr;
}

airTab HashTable::getAirlines() const { return airlines; }

