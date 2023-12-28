
#include "HashTable.h"

// Airport class
Airport::Airport(string code_): code(code_) {}

Airport::Airport(string code_, string name_, string city_, string country_, float latitude_, float longitude_):
        code(code_), name(name_), city(city_), country(country_), latitude(latitude_), longitude(longitude_) {}

bool Airport::operator==(const Airport& other) const {
    return (code == other.code) && (name == other.name) && (city == other.city)
           && (country == other.country) && (latitude == other.latitude) && (longitude == other.longitude);
}

string Airport::getCode() const { return code; }

string Airport::getName() const { return name; }

string Airport::getCity() const { return city; }

string Airport::getCountry() const { return country; }

float Airport::getLatitude() const { return latitude; }

float Airport::getLongitude() const { return longitude; }



// Airline class
Airline::Airline() {}

Airline::Airline(string code_): code(code_) {}

Airline::Airline(string code_, string name_, string callsign_, string country_):
                code(code_), name(name_), callsign(callsign_), country(country_) {}

string Airline::getCode() const { return code; }

string Airline::getName() const{ return name; }

string Airline::getCallsign() const { return callsign;}

string Airline::getCountry() const { return country;}

bool Airline::operator<( const Airline& air) const { return code<air.getCode(); }



// AirHashTable class
HashTable::HashTable() {}

void HashTable::addAirline (const Airline& airline) { airlines.insert(airline); }

const Airline* HashTable::findAirline (const string& code) {
    auto it = airlines.find(Airline(code));
    if (it != airlines.end()) return &(*it);
    return nullptr;
}

airTab HashTable::getAirlines() const { return airlines; }