#ifndef AED_SCHEDULE_MENU_H
#define AED_SCHEDULE_MENU_H

#include "Data.h"
#include <iostream>
#include <string>

/**
 * Represents the menu.
 */
class Menu {
private:
    Data data;
public:
    /**
     * Constructor of the Menu class.
     * @details Also creates a new Manager to execute every action needed.
     */
    Menu();
    /**
     * Complexity: O(1)
     * Método void que "limpa" o ecrã
     */
    static void clearScreen();
    /**
     * Complexity: O(1)
     * Método void que apresenta o título do menu
     */
    static void printTitle();
    /**
     * Initializes the main menu.
     */
    void init();
    /**
     * Initializes the search flights menu.
     * @details This menu is used to select which search method will be used to explore the air traffic.
     */
    void inputFlights() const;
    /**
     * Initializes the airport info menu.
     * @details This menu is used to give access to all information about a airport such as name,location,flights available,etc.
     */
    void airportInfo();
    /**
     * Initializes the airline info menu.
     * @details This menu is used to give all information about a airline such as name,call-sign,ect.
     */
    void airlineInfo() const;
    /**
     * Prints all airports reachable in all flights available in a single airport.
     * @details Time Complexity- O(|E| log(|V|)).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport's code
     */
    void flightsFromAirportInfo(const string& airport_code) const;
    /**
     * Prints all airlines available in a single airport.
     * @details Time Complexity- O(|E| log(|V|)).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport's code
     */
    void airlinesFromAirportInfo(const string& airport_code) const;
    /**
     * Prints all cities reachable within all of the flights available in a single airport.
     * @details Time Complexity- O(|E| log(|V|)).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport's code
     */
    void citiesFromAirportInfo(const string& airport_code) const;
    /**
     * Prints all counties reachable within all of the flights available in a single airport.
     * @details Time Complexity- O(|E| log(|V|)).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport's code
     */
    void countriesFromAirportInfo(const string& airport_code) const;
    /**
     * Opens the menu to help costumers view all places reachable within a wanted number of flights starting from a source airport.
     * @param airport_code Airport's code.
     */
    void reachInFlights(const string& airport_code);
    /**
     * Prints all airports reachable within a fixed number of flights starting from a source airport.
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport's code.
     * @param nr_flights  Number of flights desired.
     */
    void reachableAirportsInFlights(const string& airport_code, int nr_flights);
    /**
     * Prints all cities reachable within a fixed number of flights starting from a source airport.
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport's code.
     * @param nr_flights  Number of flights desired.
     */
    void reachableCitiesInFlights(const string& airport_code, int nr_flights);
    /**
     * Prints all countries reachable within a fixed number of flights starting from a source airport.
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport's code.
     * @param nr_flights  Number of flights desired.
     */
    void reachableCountriesInFlights(const string& airport_code, int nr_flights);
    /**
     * Opens the inputting menu for cities.
     * @details This menu is used to input the current city where the client is and the desired city the client wants to go.
     */
    void inputCity() const;
    /**
     * Prints all the traveled airports in a trip the client selected.
     * @details In case of impossible travels this menu also warns the client.
     * @param traveled_airports List of all the airports traveled.
     */
    static void pages(const list<list<pair<Airport, string>>>& traveled_airports) ;
    /**
     * Opens the inputting menu for gps coordinates of the airports.
     * @details This menu is used to input the current airport's coordinates where the client is and the desired airport's coordinates the client wants to go.
     * @param option Option to input the exact coordinates or not.
     * @details option=true means the client wants to input the exact coordinates of a airport and option=false means the client will just input coordinates close to the airport.
     */
    void inputCoordinates(bool option) const;
    /**
     * Opens the inputting menu for airports.
     * @details This menu is used to input the current airport where the client is and the desired airport the client wants to go.
     */
    void inputAirport() const;
    /**
     * Opens the menu with the global information
     * @details This menu is used to view top flights, all airports available, all airlines, ect.
     */
    void globalInfo();
};

#endif
