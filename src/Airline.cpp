#include "Airline.h"

using namespace std;

Airline::Airline(string code, string name, string callsign, string country) :
        airline_code(std::move(code)),
        airline_name(std::move(name)),
        airline_callsign(std::move(callsign)),
        airline_country(std::move(country)) {}

string Airline::getCode() const{return airline_name;}
string Airline::getName() const {return airline_name;}
string Airline::getCallSign() const {return airline_callsign;}
string Airline::getCountry() const {return airline_country;}

bool Airline::operator<(const Airline& airline) const {
    return airline_code < airline.getCode();
}