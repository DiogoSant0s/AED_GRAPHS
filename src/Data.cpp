#include "Data.h"

Data::Data() {
    this -> airports = new Graph(true);
    this -> how_to_fly = true;
    readData();
}

Data::~Data() {delete airports;}

int Data::size_aiports() const{return airports -> size_Nodes();}
int Data::size_airlines() const{return (int) airlines.size();}
int Data::size_flights() const{return airports -> size_Flights();}
int Data::diameter() const{return airports -> Diameter();}
Airport Data::getAirport(const string& airport_code) const {return airports -> getAirport(airport_code);}
Airline Data::getAirline(const string& airline_code) const {return airlines.at(airline_code);}
multiset<pair<string, int>, CompareDistance> Data::top_flights(int k) const {return airports -> top_flights(k);}

void Data::readData() {
    ifstream airlines_input("../dataset/airlines.csv");
    ifstream airports_input("../dataset/airports.csv");
    ifstream flights_input("../dataset/flights.csv");
    string line;

    getline(airlines_input, line);
    getline(airports_input, line);
    getline(flights_input, line);

    while(getline(airlines_input, line)) {
        stringstream ss(line);
        string code, name, callsign, country;

        getline(ss, code, ',');//n
        getline(ss, name, ',');
        getline(ss, callsign, ',');
        getline(ss, country, '\r');

        airlines.insert({code, Airline(code, name, callsign, country) });
    }
    while(getline(airports_input, line)) {
        stringstream ss(line);

        string code, name, city, country, latitude_string, longitude_string;

        getline(ss, code, ',');//n
        getline(ss, name, ',');
        getline(ss, city, ',');
        getline(ss, country, ',');
        getline(ss, latitude_string, ',');
        getline(ss, longitude_string, '\r');

        double latitude = std::stod(latitude_string);
        double longitude = std::stod(longitude_string);

        cities.insert(city);
        airports -> addNode(code, Airport(code, name, city, country, latitude, longitude));
    }
    while(getline(flights_input, line)) {
        std::stringstream ss(line);

        std::string source, target, airline;

        getline(ss, source, ',');
        getline(ss, target, ',');
        getline(ss, airline, '\r');

        airports -> addEdge(source, target, airline);
    }
}

list<list<pair<Airport, string>>> Data::getTraveledAirports(const string& source_airport, const string& target_airport) const {
    if (how_to_fly)
        return airports -> getTraveledAirports(source_airport, target_airport);
    return airports -> getTraveledAirportsByDistance(source_airport, target_airport);
}

list<list<pair<Airport, string>>>  Data::localCoordinates(double start_latitude, double start_longitude, double end_latitude, double end_longitude, int dist) const{
    list<list<pair<Airport, string>>> traveled,temp;
    list<string> start_airtports = airports -> findAirports(start_latitude, start_longitude, dist);
    list<string> end_airports = airports -> findAirports(end_latitude, end_longitude, dist);
    if (how_to_fly) {
        bool flag = true;
        for (const auto& i : start_airtports){
            for (const auto& j : end_airports){
                temp = airports -> getTraveledAirports(i, j);
                if (temp.front().size() < traveled.front().size() || flag) {
                    traveled = temp;
                    flag = false;
                }
                else if (temp.front().size() == traveled.front().size())
                    traveled.insert(traveled.end(),temp.begin(),temp.end());
            }
        }
        return traveled;
    }
    bool flag = true;
    double distance = INF;
    for (const auto& i : start_airtports){
        for (const auto& j : end_airports){
            temp = airports -> getTraveledAirportsByDistance(i, j);
            if (airports -> getShortestPath(temp.front().front().first.getCode(), temp.front().back().first.getCode()) < distance || flag) {
                traveled = temp;
                distance = airports -> getShortestPath(temp.front().front().first.getCode(), temp.front().back().first.getCode());
                flag = false;
            }
            else if (airports -> getShortestPath(temp.front().front().first.getCode(), temp.front().back().first.getCode()) == distance)
                traveled.insert(traveled.end(),temp.begin(),temp.end());
        }
    }
    return traveled;
}

list<list<pair<Airport, string>>> Data::localCity(const string& start, const string& end) const {
    list<list<pair<Airport, string>>> traveled, temp;
    list<string> start_airtports = airports -> findAirportByCity(start);
    list<string> end_airports = airports -> findAirportByCity(end);
    if (how_to_fly) {
        bool flag = true;
        for (const auto& i : start_airtports){
            for (const auto& j : end_airports){
                temp = airports -> getTraveledAirports(i, j);
                if (temp.front().size() < traveled.front().size() || flag) {
                    traveled = temp;
                    flag = false;
                }
                else if (temp.front().size() == traveled.front().size()) {
                    traveled.insert(traveled.end(),temp.begin(),temp.end());
                }
            }
        }
        return traveled;
    }
    bool flag = true;
    double distance = INF;
    for (const auto& i : start_airtports){
        for (const auto& j : end_airports){
            temp = airports -> getTraveledAirportsByDistance(i, j);
            if (airports -> getShortestPath(temp.front().front().first.getCode(), temp.front().back().first.getCode()) < distance || flag) {
                traveled = temp;
                distance = airports -> getShortestPath(temp.front().front().first.getCode(), temp.front().back().first.getCode());
                flag = false;
            }
            else if (airports -> getShortestPath(temp.front().front().first.getCode(), temp.front().back().first.getCode()) == distance)
                traveled.insert(traveled.end(),temp.begin(),temp.end());
        }
    }
    return traveled;
}

list<list<pair<Airport, string>>>  Data::localCoordinatesClosest(double start_latitude, double start_longitude, double end_latitude, double end_longitude) const {
    string start = airports -> findAirport(start_latitude, start_longitude);
    string end = airports -> findAirport(end_latitude, end_longitude);
    if (how_to_fly) {
        return airports -> getTraveledAirports(start, end);
    }
    return airports -> getTraveledAirportsByDistance(start, end);
}

list<Airline> Data::getAirlinesFromAirport(const string& airport_code) const {
    set<string> airlines_code = airports -> getAirlinesFromAirport(airport_code);
    list<Airline> airline;
    for (const string& it : airlines_code) {
        airline.push_back(airlines.find(it) -> second);
    }
    return airline;
}

list<Airport> Data::getAirportsReached(const string& source_airport, int k) {return airports -> getAirportsReached(source_airport, k);}
set<string> Data::getCitiesReached(const string& source_airport, int k) {return airports -> getCitiesReached(source_airport, k);}
set<string> Data::getCountriesReached(const string& source_airport, int k) {return airports -> getCountriesReached(source_airport, k);}
set<string> Data::getArrivalAirport(const string& airport_code) const {return airports -> getArrivalAirports(airport_code);}
set<string> Data::getArrivalCities(const string& airport_code) const {return airports -> getArrivalCities(airport_code);}
set<string> Data::getArrivalCountries(const string& airport_code) const {return airports -> getArrivalCountries(airport_code);}

bool Data::checkIfAirportExists(const string& airport_code) const {
    return airports -> checkIfAirportExists(airport_code);
}

bool Data::checkIfAirlineExists(const string &airline_code) const {
    return (airlines.find(airline_code) != airlines.end());
}
