#ifndef AED_GRAPHS_GRAPH_H
#define AED_GRAPHS_GRAPH_H

#include "Airport.h"
#include "Airline.h"
#include "Haversine.h"
#include <list>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <iostream>
#include <queue>

using namespace std;

#define INF numeric_limits<double>::max()

/**
 * Represents a Graph.
 */
class Graph {
private:
    /**
     * Represents the edges of the graph.
     */
    struct Edge {
        /**
         * Destination Node
         */
        string dest;
        /**
         *  Airline in charge of the flight
         */
        string airline;
        /**
         *  Distance between two nodes.
         */
        double distance;
    };
    /**
     * Represents the content of each node.
     */
    struct Node {
        /**
         *  Airport
         */
        Airport airport;
        /**
         *  List of outgoing edges, to adjacent nodes.
         */
        list<Edge> adj;
        /**
         *  Verifies if the node has been visited on a previous search.
         * @details This variable set to True means that the node has been visited and False otherwise.
         */
        bool visited;
        /**
         *  Distance to the source node.
         * @details This can be used to find the shortest path to node.
         */
        double src_distance;
        /**
         *  A list that stores another list with all the airports and airlines from the source all the way to the target node.
         */
        list<list<pair<Airport, string>>> travel_from_src;
    };
    /**
     *  Variable that sets the Graph to be directed or undirected.
     * @details This variable set to True means the Graph is directed and False otherwise.
     */
    bool has_dir;
    /**
     *  A hash table.
     * @details When searching the Time Complexity is O(1).
     */
    unordered_map<string, Node> nodes;
    /**
     *  Set of airlines favoured by the client.
     * @details Can be empty.
     */
    unordered_set<string> wanted_airlines;
    /**
     * Find the shortest path using Dijkstra Algorithm.
     * @details Time Complexity - O(|E| log(|V|)).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Code of the target Airport.
     */
    void shortestPath(const string& airport_code);
public:
    /**
     * Creates a new Graph.
     * @details The Graph is undirected by default.
     * @details To change it use Graph(true) in initialization.
     * @details Constructor of the Graph class.
     * @param dir
     */
    explicit Graph(bool dir = false);
    /**
     * Add a node to the Graph using the airport code as a key and the whole airport class as the value.
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport's code
     * @param airport All of the airport information.
     */
    void addNode(const string &airport_code, const Airport &airport);
    /**
     * Add an edge from a source airport to a target airport using their distance as the weight.
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param source_airport The source airport.
     * @param target_airport The target airport.
     * @param airline Distance between the two airports.
     */
    void addEdge(const string& source_airport, const string& target_airport, const string& airline);
    /**
     * This function sets all the nodes to unvisited state.
     * @details Time Complexity - O(V).
     * @details V is the number of vertices/nodes.
     */
    void setUnvisited();
    /**
     * Function used to do a Depth-First Search (aka DFS).
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport code to be searched.
     */
    void dfs(const string &airport_code);
    /**
     * Function used to do a Breadth-First Search (aka BFS).
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport code to be searched.
     */
    void bfs(const string &airport_code);
    /**
     * Gets the Airport class.
     * @details Time Complexity - O(1).
     * @param airport_code Airport's code.
     * @return All of the airport information.
     */
    Airport getAirport(const string &airport_code) const;
    /**
     * Gets a list of every traveled airport in a trip from a source airport to a target airport.
     * @details Time Complexity - O(|V| + |E|).
     * @details Uses the minimum amount of flights as a criteria.
     * @param source_airport Source airport's code.
     * @param target_airport Target airport's code.
     * @return List of all airports the client can travel through in a trip.
     */
    list<list<pair<Airport, string>>> getTraveledAirports(const string &source_airport, const string &target_airport);
    /**
     * Search the airport located in fixed GPS coordinates.
     * @details Time Complexity - O(V log(n)).
     * @details V is the number of vertices/nodes.
     * @param latitude Latitude of the airport.
     * @param longitude Longitude of the airport.
     * @return Airport's code.
     */
    string findAirport(double latitude, double longitude);
    /**
     * Search all the airports located in a city.
     * @details Time Complexity - O(V).
     * @details V is the number of vertices/nodes.
     * @param city City where the airports are located.
     * @return List of all the airports located within the city.
     */
    list<string> findAirportByCity(const string &city);
    /**
     * Search the airport located within a certain distance from fixed GPS coordinates.
     * @details Time Complexity - O(V log(n)).
     * @details V is the number of vertices/nodes.
     * @param latitude Latitude of the airport.
     * @param longitude Longitude of the airport.
     * @param dist Distance where airports can be.
     * @return All of the airport information.
     */
    list<string> findAirports(double latitude, double longitude, int dist);
    /**
     * Gets the number of kilometers traveled in a straight line from a source airport to a target airport.
     * @details Time Complexity- O(|E| log(|V|)).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param target_airport Target airport's code.
     * @return Number of kilometers traveled in a straight line between two airports.
     */
    double getShortestPath(const string &target_airport);
    /**
     * Gets the list of airports and airlines traveled through in a trip between 2 airports.
     * @details Time Complexity- O(|E| log(|V|)).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param source_airport Source airport's code.
     * @param target_airport Target airport's code.
     * @return A list that stores another list with all the airports and airlines traveled from the source airport all the way to the target airport.
     */
    list<list<pair<Airport, string>>> getTraveledAirportsByDistance(const string &source_airport, const string &target_airport);
    /**
     * Gets all of the airlines connected to an airport.
     * @details Time Complexity- O(|E| log(|V|)).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport's code.
     * @return Set with all airlines(airline's code) connected to a certain airport.
     */
    set<string> getAirlinesFromAirport(const string &airport_code) const;
    /**
     * Gets all airports that can be reached from a source airport in a fixed number of flights.
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param source_airport Source airport's code.
     * @param k Number of flights.
     * @return List of airports reachable within a "k" number of flights.
     */
    list<Airport> getAirportsReached(const string &source_airport, int k);
    /**
     * Gets all cities that can be reached from a source airport in a fixed number of flights.
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param source_airport Source airport's code.
     * @param k Number of flights.
     * @return List of cities reachable within a "k" number of flights.
     */
    set<string> getCitiesReached(const string &source_airport, int k);
    /**
     * Gets all countries that can be reached from a source airport in a fixed number of flights.
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param source_airport Source airport's code.
     * @param k Number of flights.
     * @return List of countries reachable within a "k" number of flights.
     */
    set<string> getCountriesReached(const string &source_airport, int k);
    /**
     * Gets all airports that can be reached with 1 flight from a source airport.
     * @details Time Complexity- O(|E| log(|V|)).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport's code.
     * @return List of airports reachable within 1 flight.
     */
    set<string> getArrivalAirports(const string &airport_code) const;
    /**
     * Gets all cities that can be reached with 1 flight from a source airport.
     * @details Time Complexity- O(|E| log(|V|)).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport's code.
     * @return List of cities reachable within 1 flight.
     */
    set<string> getArrivalCities(const string &airport_code) const;
    /**
     * Gets all countries that can be reached with 1 flight from a source airport.
     * @details Time Complexity- O(|E| log(|V|)).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport's code.
     * @return List of countries reachable within 1 flight.
     */
    set<string> getArrivalCountries(const string &airport_code) const;
    /**
     * Checks if airport exists in nodes hash table.
     * @details Time Complexity- O(V).
     * @details V is the number of vertices/nodes.
     * @param airport_code Airport's code.
     * @return True-If the airport exists.
     * @return False-If the airport doesn't exist.
     */
    bool checkIfAirportExists(const string &airport_code) const;
    /**
     * Gives the size of the Graph nodes.
     * @details The number of nodes is equal to the number of airports.
     * @details Time Complexity- O(1).
     * @return Total number of nodes in the Graph.
     */
    int size_Nodes();
    /**
     * Gives the size of the Graph edges.
     * @details The number of edges is equal to the number of flights.
     * @details Time Complexity- O(V).
     * @details V is the number of vertices/nodes.
     * @return Total number of edges in the Graph.
     */
    int size_Flights();
    /**
     * Function used to help calculate the diameter of the graph.
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport code to be searched.
     */
    void bfs_diameter(const string &airport_code);
    /**
     * Gets the diameter from every flight.
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @return Diameter.
     */
    int Diameter();
    /**
     * Gets de top "k" of flights by distance traveled.
     * @param k Number of flights to be ranked.
     * @return Set of the longest flights.
     */
    multiset<pair<string, int>, Distance> top_flights(int k);
};

#endif //AED_GRAPHS_GRAPH_H
