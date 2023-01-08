
#ifndef AED_GRAPHS_MENU_H
#define AED_GRAPHS_MENU_H

#include <iostream>

using namespace std;

class Menu {

    Aiports airport;

public:

    Menu(Airports a);

    void clearScreen();

    void printTitle();

    void MainMenu();

    int getUserInput(vector<int> inputs);

    string getUserTextInput();

    void BestRouteMenu();

    void showBestRoute(Airports &a, string departure, string destination, dep, dest);


};


#endif //AED_GRAPHS_MENU_H
