
#ifndef AED_GRAPHS_MENU_H
#define AED_GRAPHS_MENU_H

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "LoadData.h"

using namespace std;

class Menu {
    LoadData data;
public:
    /**
     * Complexity: O(1)
     * Construtor da classe Menu.
     */
    explicit Menu();
    /**
     * Complexity: O(1)
     * Método void que apresenta o título do menu
     */
    static void printTitle();
    /**
     * Complexity: O(n)
     * Método normal que verifica se o input do utilizador é válido.
     * @param inputs vetor de inteiros
     * @return inteiro input do utilizador
     */
    static int getUserInput(vector<int> inputs);
    /**
     * Complexity: O(n)
     * Método normal que verifica se o input do utilizador é válido,
     * para um número indefinido de inputs possíveis.
     * @return string input do utilizador
     */
    static string getUserTextInput();
    /**
     * Complexity: O(n)
     * Método void que "limpa" o ecrã
     */
    static void clearScreen();
    /**
     * Complexity: O(n)
     * Método void utilizado para apresentar no ecrã as opções, relativas
     * a um conjunto de data definido por um membro LoadData, do menu inicial ao utilizador.
     */
    void MainMenu();
    void BestRouteMenu();

    void showBestRoute(Airports &a, string departure, string destination, dep, dest);
};


#endif //AED_GRAPHS_MENU_H
