#ifndef AED_SCHEDULE_LOADDATA_H
#define AED_SCHEDULE_LOADDATA_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include "Airline.h"
#include "Airport.h"
#include "Graph.h"

using namespace std;

/**
 * Classe LoadData
 * @details A classe é responsável pelo carregamento e armazenamento de dados.
 */

class LoadData {
    set<Airline> airlines;
    set<Airport> airport;
public:
    /**
     * Complexity: O(n)
     * Método void responsável por ler o ficheiro airlines.csv que contêm as informações sobre as companhias aéreas
     */
    void loadData_Airlines();
    /**
     * Complexity: O(n)
     * Método void responsável por ler o ficheiro airports.csv que contêm as informações sobre os aeroportos
     */
    void loadData_Airports();
    /**
     * Complexity: O(n)
     * @details Método void responsável por ler o ficheiro flights.csv que contêm as informações sobre as informações sobre os voos:
     * aeroporto de partida e de chegada e companhia aérea responsável pelo voo
     */
    void loadData_Flights();
};

#endif //AED_SCHEDULE_LOADDATA_H
