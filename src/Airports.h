#ifndef AED_GRAPHS_AIRPORTS_H
#define AED_GRAPHS_AIRPORTS_H

#include <string>

using namespace std;

class Airport {
private:
    string airport_code;
    string airport_name;
    string airport_city;
    string airport_country;
    double _latitude;
    double _longitude;
public:
    /**
     * Construtor da classe Airport
     * @param code Código do aeroporto
     * @param name Nome do aeroporto
     * @param city Cidade do aeroporto
     * @param country Pais do aeroporto
     * @param latitude Latitude do aeroporto
     * @param longitude Longitude do aeroporto
     */
    Airport(string code, string name, string city, string country, double latitude, double longitude);
    /**
     * Complexity: O(1)
     * Método normal que devolve o atributo code
     * @return string relativa ao código IATA do aeroporto
     */
    string getCode() const;
    /**
     * Complexity: O(1)
     * Método normal que devolve o atributo name
     * @return string relativa ao nome  do aeroporto
     */
    string getName() const;
    /**
     * Complexity: O(1)
     * Método normal que devolve o atributo city
     * @return string relativa à cidade onde se encontra o aeroporto
     */
    string getCity() const;
    /**
     * Complexity: O(1)
     * Método normal que devolve o atributo country
     * @return string relativa ao país onde está localizado o aeroporto
     */
    string getCountry() const;
    /**
     * Complexity: O(1)
     * Método normal que devolve o atributo latitude
     * @return string relativa à latitude da posição do aeroporto
     */
    double getLatitude() const;
    /**
     * Complexity: O(1)
     * Método normal que devolve o atributo longitude
     * @return string relativa à longitude da posição do aeroporto
     */
    double getLongitude() const;
};

#endif //AED_GRAPHS_AIRPORTS_H
