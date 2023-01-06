#ifndef AED_GRAPHS_AIRLINE_H
#define AED_GRAPHS_AIRLINE_H
#include "string"
using namespace std;

class Airline{
private:
    string airline_code;
    string airline_name;
    string airline_callsign;
    string airline_country;

public:
    Airline(string code, string  name,
            string callsign, string country);

    string getCode() const;
    string getName() const;
    string getCallSign() const;
    string getCountry() const;

    bool operator == (const Airline &airline)const;
};

#endif //AED_GRAPHS_AIRLINE_H
