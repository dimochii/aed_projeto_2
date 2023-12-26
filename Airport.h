
#ifndef AIRPORTSPROJECT_AIRPORT_H
#define AIRPORTSPROJECT_AIRPORT_H

#include <string>
using namespace std;

class Airport {
    string code;
    string name;
    string city;
    string country;
    float latitude;
    float longitude;

public:
    Airport(string code, string name, string city, string country, float latitude, float longitude);

    bool operator==(const Airport& other) const;

    string getCode() const;
    string getName() const;
    string getCity() const;
    string getCountry() const;
    float getLatitude() const;
    float getLongitude() const;

};


#endif //AIRPORTSPROJECT_AIRPORT_H
