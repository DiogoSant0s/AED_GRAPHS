
#ifndef AED_GRAPHS_AIRPORTS_H
#define AED_GRAPHS_AIRPORTS_H

#include "string"

using namespace std;

class Airport{
private:
    string airport_code;
    string airport_name;
    string airport_city;
    string airport_country;

    double _latitude;
    double _longitude;


public:
    Airport(){};
    Airport(
            string code,
            string name,
            string city,
            string country,
            double latitude,
            double longitude
            );

    string getCode() const;
    string getName() const;
    string getCity() const;
    string getCountry() const;

    double getLatitude() const;
    double getLongitude() const;

    bool operator==(const Airport &airport) const;
};
#endif //AED_GRAPHS_AIRPORTS_H
