#include "Airport.h"
#include <utility>
#include "string"

using namespace std;

Airport::Airport(string code, string name, string city, string country, double latitude, double longitude) :
    airport_code(std::move(code)),
    airport_name(std::move(name)),
    airport_city(std::move(city)),
    airport_country(std::move(country)),
    _latitude(latitude),
    _longitude(longitude) {}

string Airport::getCode() const {return airport_code;}
string Airport::getName() const {return airport_name;}
string Airport::getCity() const {return airport_city;}
string Airport::getCountry() const {return airport_country;}
double Airport::getLatitude() const {return _latitude;}
double Airport::getLongitude() const {return _longitude;}

bool Airport::operator==(const Airport &airport) const {
    return airport_code == airport.getCode();
}