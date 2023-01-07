//
// Created by ritav on 06/01/2023.
//
#include "Airports.h"
string Airport::getCode() const {
    return airport_code;
}
string Airport::getName() const {
    return airport_name;
}
string Airport::getCity() const {
    return airport_city;
}
string Airport::getCountry() const {
    return airport_country;
}
double Airport::getLatitude() const {
    return latitude;
}
double Airport::getLongitude() const {
    return longitude;
}
Airport::Airport(string code,
                 string name,
                 string city,
                 string country,
                 double latitude,
                 double longitude) :
        airport_code(code), airport_name(name),
        airport_city(city), airport_country(country),
        latitude(latitude), longitude(longitude) {}