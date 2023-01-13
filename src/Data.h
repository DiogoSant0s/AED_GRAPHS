#ifndef AED_SCHEDULE_LOADDATA_H
#define AED_SCHEDULE_LOADDATA_H

#include "Graph.h"
#include <list>
#include <set>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

using namespace std;

/**
 * Represents the Manager of the air traffic.
 */
class Data {
private:
    ///Graph with all the information of the air traffic, airports and flights.
    Graph* airports;
    ///Stores all the airlines, connecting them to their code.
    unordered_map<string, Airline> airlines;
    ///A set used to fill with all the cities with airports.
    unordered_set<string> cities;
    /**
     * Variable used to determine all of the flights in a trip
     * @details True means the flights will be determined by the less number of kilometers possible.
     * @detail False means the flights will be determined by the less number of flights possible.
     */
    bool how_to_fly;
    /**
     * Reads all the data saved in the files and stores them in the correct structures.
     * @details Time Complexity - O(n^3).
     */
    void readData();
public:
    /**
     * Creates a new data.
     * @details Constructor of the AirManager class.
     * @details Creates a new directed Graph and reads all the data from the files.
     */
    Data();
    /**
     * Deletes the current data.
     * @details Destructor of the AirManager class.
     * @details Deletion of the current airports and flights Graph.
     */
    ~Data();
    /**
     * Gets the Airport class.
     * @details Time Complexity - O(1).
     * @param airport_code Airport's code.
     * @return All of the airport information.
     */
    Airport getAirport(const string& airport_code) const;
    /**
     * Gets the Airline class.
     * @details Time Complexity - O(1).
     * @param airport_code Airport's code.
     * @return All of the airline information.
     */
    Airline getAirline(const string& airline_code) const;
    /**
     * Gets a list of every traveled airport in a trip from a source airport to a target airport.
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param source_airport Source airport's code.
     * @param target_airport Target airport's code.
     * @return List of all airports the client can travel through in a trip.
     */
    list<list<pair<Airport, string>>> getTraveledAirports(const string& source_airport, const string& target_airport) const;
    /**
     * Gets a list of every traveled airport in a trip from a source airport to a target airport using local GPS coordinates as a reference.
     * @details Time Complexity - O(n^2 (|V|+|E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param start_longitude Source airport's longitude.
     * @param start_latitude Source airport's latitude.
     * @param end_longitude Target airport's longitude.
     * @param end_latitude Target airport's latitude.
     * @param dist Max distance from this coordinates to search an airport for.
     * @return List of all airports the client can travel through in a trip.
     */
    list<list<pair<Airport, string>>> getTraveledAirportsCoordinates(double start_latitude, double start_longitude,
                                                                     double end_latitude, double end_longitude, int dist) const;
    /**
     * Gets a list of every traveled airport in a trip from a source airport to a target airport using both the host cities as reference.
     * @details Time Complexity - O(n^2 (|V|+|E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param start Source airport's city.
     * @param end Target airport's city.
     * @return List of all airports the client can travel through in a trip.
     */
    list<list<pair<Airport, string>>> getTraveledAirportsCity(const string& start, const string& end) const;
    /**
     * Gets a list of every traveled airport in a trip from a source airport to a target airport using inputted GPS coordinates as reference.
     * @details Because inputting coordinates can be too exact, this function helps the user finding the closest airports to both coordinates.
     * @details Time Complexity - O(V log(n)).
     * @param start_longitude Longitude selected by the client.
     * @param start_latitude Latitude selected by the client.
     * @param end_longitude Longitude selected by the client.
     * @param end_latitude Latitude selected by the client.
     * @return List of all airports the client can travel through in a trip.
     */
    list<list<pair<Airport, string>>> getTraveledAirportsCoordinatesClosest(double start_latitude, double start_longitude,
                                                                            double end_latitude, double end_longitude) const;
    /**
     * Gets all of the airlines connected to an airport.
     * @details Time Complexity- O(|E| log(|V|)).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport's code.
     * @return Set with all airlines connected to a certain airport.
     */
    list<Airline> getAirlinesFromAirport(const string& airport_code) const;
    /**
     * Gets all airports that can be reached from a source airport in a fixed number of flights.
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param source_airport Source airport's code.
     * @param k Number of flights.
     * @return List of airports reachable within a "k" number of flights.
     */
    list<Airport> getAirportsReached(const string& source_airport, int k);
    /**
    * Gets all cities that can be reached from a source airport in a fixed number of flights.
    * @details Time Complexity - O(|V| + |E|).
    * @details V is the number of vertices/nodes and E is the number of edges/links.
    * @param source_airport Source airport's code.
    * @param k Number of flights.
    * @return List of cities reachable within a "k" number of flights.
    */
    set<string> getCitiesReached(const string& source_airport, int k);
    /**
    * Gets all countries that can be reached from a source airport in a fixed number of flights.
    * @details Time Complexity - O(|V| + |E|).
    * @details V is the number of vertices/nodes and E is the number of edges/links.
    * @param source_airport Source airport's code.
    * @param k Number of flights.
    * @return List of countries reachable within a "k" number of flights.
    */
    set<string> getCountriesReached(const string& source_airport, int k);
    /**
     * Gets all airports that can be reached with 1 flight from a source airport.
     * @details Time Complexity- O(|E| log(|V|)).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport's code.
     * @return List of airports reachable within 1 flight.
     */
    set<string> getArrivalAirport(const string& airport_code) const;
    /**
     * Gets all cities that can be reached with 1 flight from a source airport.
     * @details Time Complexity- O(|E| log(|V|)).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport's code.
     * @return List of cities reachable within 1 flight.
     */
    set<string> getArrivalCities(const string& airport_code) const;
    /**
     * Gets all countries that can be reached with 1 flight from a source airport.
     * @details Time Complexity- O(|E| log(|V|)).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport's code.
     * @return List of countries reachable within 1 flight.
     */
    set<string> getArrivalCountries(const string& airport_code) const;
    /**
     * Checks if airport exists in nodes hash table.
     * @details Time Complexity- O(V).
     * @details V is the number of vertices/nodes.
     * @param airport_code Airport's code.
     * @return True-If the airport exists.
     * @return False-If the airport doesn't exist.
     */
    bool checkIfAirportExists(const string& airport_code) const;
    /**
     * Checks if airline exists in nodes hash table.
     * @details Time Complexity- O(V).
     * @details V is the number of vertices/nodes.
     * @param airport_code Airline's code.
     * @return True-If the airline exists.
     * @return False-If the airline doesn't exist.
     */
    bool checkIfAirlineExists(const string& airline_code) const;
    /**
     * Gives the size of the Graph.
     * @details The number of nodes is equal to the number of airports.
     * @details Time Complexity- O(1).
     * @return Number of airports.
     */
    int size_aiports() const;
    /**
     * Gets the total number of airlines in the dataset
     * @details Time Complexity- O(1).
     * @return Number of airlines.
     */
    int size_airlines() const;
    /**
     * Gives the size of the Graph edges.
     * @details The number of edges is equal to the number of flights.
     * @details Time Complexity- O(V).
     * @return Number of flights.
     */
    int size_flights() const;
    /**
     * Gets the diameter from every flight.
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @return Diameter.
     */
    int diameter() const;
    /**
     * Gets de top "k" of flights by distance traveled.
     * @param k Number of flights to be ranked.
     * @return Set of the longest flights.
     */
    multiset<pair<string, int>, Distance> top_flights(int k) const;
};

#endif //AED_SCHEDULE_LOADDATA_H
