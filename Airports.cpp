//
// Created by ritav on 06/01/2023.
//
#include "Airports.h"
#include "string"
using namespace std;

Airport::Airport(
        string code,
        string name,
        string city,
        string country,

        double latitude,
        double longitude
): airport_code(code),
   airport_name(name),
   airport_city(city),
   airport_country(country),
   _latitude(latitude),
   _longitude(longitude) {}

std::string Airport::getCode() const {
    return airport_code;
}

std::string Airport::getName() const {
    return airport_name;
}

std::string Airport::getCity() const {
    return airport_city;
}

std::string Airport::getCountry() const {
    return airport_country;
}

double Airport::getLatitude() const {
    return _latitude;
}

double Airport::getLongitude() const {
    return _longitude;
}

bool Airport::operator==(const Airport &airport) const {
    return airport_code == airport.getCode();
}