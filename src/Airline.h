#ifndef AED_GRAPHS_AIRLINE_H
#define AED_GRAPHS_AIRLINE_H

#include <utility>
#include <string>

using namespace std;

/**
 * Classe que representa uma companhia aérea.
 * Esta classe representa uma companhia aérea, com o seu codigo, nome, call sign e o seu país de origem
 */

class Airline {
private:
    /// Codigo da companhia aérea
    string airline_code;
    /// Nome da companhia aérea
    string airline_name;
    /// Call sign da companhia aérea
    string airline_callsign;
    /// País de origem da companhia aérea
    string airline_country;
public:
    /**
     * @brief Construtor da classe Airline
     * @param code Código da companhia aérea
     * @param name Nome da companhia aérea
     * @param callSign Call sign da companhia aérea
     * @param country Pais de origem da companhia aérea
     */
    Airline(string code, string  name, string callsign, string country);
    /**
     * Complexity: O(1)
     * Método normal que devolve o atributo code
     * @return O código da companhia aérea
     */
    string getCode() const;
    /**
     * Complexity: O(1)
     * Método normal que devolve o atributo name
     * @return O nome da companhia aérea
     */
    string getName() const;
    /**
     * Complexity: O(1)
     * Método normal que devolve o atributo callSign
     * @return O call sign da companhia aérea
     */
    string getCallSign() const;
    /**
     * Complexity: O(1)
     * Método normal que devolve o atributo country
     * @return O país de origem da companhia aérea
     */
    string getCountry() const;
    /**
     * Complexity: O(1)
     * @brief Operador de inferioridade para dois membros da classe Airline.
     * @param airline Companhia aérea a comparar
     * @return True se o código da companhia aérea for menor que o codigo da companhia aérea airline
     */
    bool operator<(const Airline& airline)const;
};

#endif //AED_GRAPHS_AIRLINE_H
