#ifndef AED_GRAPHS_RECTANGLE_H
#define AED_GRAPHS_RECTANGLE_H

#include <utility>
#include <queue>
#include <functional>
#include <cmath>

using namespace std;

/**
 * Classe que representa um retângulo entre duas latitudes e duas longitudes
 */
class Rectangle {
public:
    /// Latitude inferior
    double lat1;
    /// Latitude superior
    double lat2;
    /// Longitude inferior
    double lon1;
    /// Longitude superior
    double lon2;
    /**
     * Construtor da classe
     * @param lat1 Latitude inferior
     * @param lat2 Latitude superior
     * @param lon1 Longitude inferior
     * @param lon2 Longitude superior
     */
    Rectangle(double lat1, double lat2, double lon1, double lon2);
    /**
     * Retorna o retângulo resultante de cortar o retângulo atual pela esquerda, no eixo cd, no ponto data
     * @param cd Coordenada a cortar (0 - latitude, 1 - longitude)
     * @param data Valor da coordenada a cortar
     * @return O retângulo resultante de cortar o retângulo atual pela esquerda
     */
    Rectangle trimLeft(int cd, double data) const;
    /**
     * Retorna o retângulo resultante de cortar o retângulo atual pela direita, no eixo cd, no ponto data
     * @param cd Coordenada a cortar (0 - latitude, 1 - longitude)
     * @param data Valor da coordenada a cortar
     * @return O retângulo resultante de cortar o retângulo atual pela direita
     */
    Rectangle trimRight(int cd, double data) const;
};
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
    double haversine(pair<double, double> p1, pair<double, double> p2);
    /**
     * Função que retorna a distância do ponto Q ao retângulo rectangle
     * @param point Ponto a ser considerado
     * @param rectangle Retângulo a ser considerado
     * @return Distância entre o ponto Q e o ponto do retângulo rectangle mais próximo de point
     */
    double distance(pair<double, double> point, Rectangle rectangle);

#endif //AED_GRAPHS_RECTANGLE_H
