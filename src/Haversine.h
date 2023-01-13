#ifndef AED_GRAPHS_HAVERSINE_H
#define AED_GRAPHS_HAVERSINE_H

#include <utility>
#include <functional>
#include <cmath>
#include "Airport.h"

using namespace std;

    /**
     * Esta função retorna uma distância entre dois pontos, calculada com a formula de Haversine, dadas as suas coordenadas
     * @param lat1 Latitude do primeiro ponto
     * @param lon1 Longitude do primeiro ponto
     * @param lat2 Latitude do segundo ponto
     * @param lon2 Longitude do segundo ponto
     * @return A distância entre os dois pontos
     */
    double haversine(double lat1, double lon1, double lat2, double lon2);
    /**
     * Esta função retorna uma distância entre dois pontos, calculada com a fórmula de Haversine, dadas as suas coordenadas
     * @param p1 Par de coordenadas do primeiro ponto
     * @param p2 Par de coordenadas do segundo ponto
     * @return A distância entre os dois pontos
     */
    double haversine(const Airport& a, const Airport& b);
    /**
     * Helper function used in dijkstra algorithm.
     */
    struct Distance {
        bool operator()(pair<string, double> const &n1, pair<string, double> const &n2) {
            return n1.second > n2.second;
        }
    };

#endif //AED_GRAPHS_HAVERSINE_H
