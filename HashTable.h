
#ifndef AIRPORTSPROJECT_HASHTABLE_H
#define AIRPORTSPROJECT_HASHTABLE_H

#include <string>
#include <unordered_set>
using namespace std;


class Airport {
    string code;
    string name;
    string city;
    string country;
    float latitude;
    float longitude;

public:
    Airport(string code);
    Airport(string code, string name, string city, string country, float latitude, float longitude);
    string getCode() const;
    string getName() const;
    string getCity() const;
    string getCountry() const;
    float getLatitude() const;
    float getLongitude() const;
    bool operator==(const Airport& other) const;
};


class Airline {
    string code;
    string name;
    string callsign;
    string country;

public:
    Airline();
    Airline(string code);
    Airline(string code, string name, string callsign, string country);
    string getCode() const;
    string getName() const;
    string getCallsign() const;
    string getCountry() const;
    bool operator<(const Airline& airline) const;
};


struct airHash
{
    // Hash function
    int operator() (const Airline& airline) const {
        string str = airline.getCode();
        int v = 0;
        for (unsigned int i = 0; i < str.size(); i++)
            v = 37*v + str[i];
        return v;
    }

    // Equality function
    bool operator() (const Airline& air1, const Airline& air2) const {
        return air1.getCode() == air2.getCode();
    }
};

typedef unordered_set<Airline, airHash, airHash> airTab;

class HashTable {
    airTab airlines;

public:
    HashTable();
    void addAirline (const Airline& airline);
    const Airline* findAirline (const string& code);
    airTab getAirlines() const;
};


#endif //AIRPORTSPROJECT_HASHTABLE_H