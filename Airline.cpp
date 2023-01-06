

#include "Airline.h"
#include "string"

using namespace std;

Airline::Airline(
        string code,
        string name,
        string callsign,
        string country
):
        airline_code(code),
        airline_name(name),
        airline_callsign(callsign),
        airline_country(country){}

string Airline::getCode() const{
    return airline_name;
}
string Airline::getName() const {
    return airline_name;
}

string Airline::getCallSign() const {
    return airline_callsign;
}

string Airline::getCountry() const {
    return airline_country;
}
bool Airline::operator==(const Airline &airline) const {
    return airline_code == airline.getCode();
}