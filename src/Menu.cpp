#include "Menu.h"

Menu::Menu() {
    data.loadData_Airlines();
    data.loadData_Airports();
    data.loadData_Flights();
}

void Menu::clearScreen() {
    for (int i = 0; i < 40; i++) {
        cout << "\n";
    }
}

void Menu::printTitle() {
    cout << R"(
____ _ ____ ___  ____ ____ ___    _  _ ____ _  _ ____ ____ ____ _  _ ____ _  _ ___
|__| | |__/ |__] |  | |__/  |     |\/| |__| |\ | |__| | __ |___ |\/| |___ |\ |  |
|  | | |  \ |    |__| |  \  |     |  | |  | | \| |  | |__] |___ |  | |___ | \|  |
    )" << "\n";
}

void Menu::MainMenu() {
    printTitle();

    cout << "\n";
    cout << "\tMain Menu\n";
    cout << "(1) Best Route\n";
    cout << "(2) Flight Network Statistics\n";
    cout << "(3) \n";
    cout << "(0) Exit\n";
    cout << " > ";

    int input;
    cin >> input;

    switch (input) {
        case 1:
            clearScreen();
            BestRouteMenu();
            break;
        case 2:
            clearScreen();
            FlightNetworkMenu();
            break;
        case 3:
            clearScreen();
            break;
        case 0:
            exit(0);
        default:
            cout << "Not a valid option\n";
            break;
    }
}

void Menu::BestRouteMenu(){
    int dep , dest;
    string departure, destination;

    cout << "Insert the following details\n\n";
    cout << "Choose the option that suits you" << "\n";
    cout << "Departure:" << "\n";
    cout << "a) City\n";
    cout << "b) Airport\n";
    cout << "c) Coordinates\n";
    char option1;
    cin >> option1;
    switch (option1) {
        case ('a'): {
            cout << "Insert Airport Code\n";
            cin >> departure;
            dep = 1;
            break;
        }
        case ('b'): {
            cout << "Insert City Name\n";
            cin >> departure;
            dep = 2;
            break;
        }
        case ('c'): {
            cout << "Insert the Coordinates(ex: 12.345,67.890)\n";
            cin >> departure;
            dep = 3;
            break;
        }
    }

    cout << "Destination:" << "\n";
    cout << "Choose the option that suits you" << "\n";
    cout << "a) City\n";
    cout << "b) Airport\n";
    cout << "c) Coordinates\n";
    char option2;
    cin >> option2;
    switch (option2) {
        case ('a'): {
            cout << "Insert Airport Code \n";
            cin >> destination;
            dest = 1;
            break;
        }
        case ('b'): {
            cout << "Insert City Name\n";
            cin >> destination;
            dest = 2;
            break;
        }
        case ('c'): {
            cout << "Insert the Coordinates(ex: 12.345,67.890)\n";
            cin >> destination;
            dest = 3;
            break;
        }
    }
    list<list<pair<Airport,string>>> airports = data.getTraveledAirports(departure, destination);
    pages(airports);

}

void Menu::showBestRoute(string departure, string destination){
    vector<string> res = least_flights(const vector<int>& sources, const vector<int>& destination);

    cout << "----------------------------------------------------------\n";

    cout << "The best route available from" << departure << "to" << destination << "is:\n";

    for(auto e: res){
        cout << " ->" << s << "airport\n";
    }

    cout << "-----------------------------------------------------------\n";

}

void Menu::showFlightNetworkStatistics(Graph a) {
    int flights = a.getGlobalNumFlights();
    int airlines = a.getAirlines().size();
    int airports = a.getAirports().size();

    printTitle();
    cout<<"Total Number of Flights ---> "<<flights<< "\n";
    cout<<"Total Number of Airlines---> "<<airlines<< "\n";
    cout<<"Total Number of Airports ---> "<<airports<< "\n";

}

void Menu::pages(const std::list<std::list<std::pair<Airport, std::string>>> &traveled_airports) const {
if (traveled_airports.empty()) {
cout << "There is no way to travel!\n";
cout << "\nPress <Enter> to go to search menu...";
/* wait for enter to be pressed */
cin.ignore(); // ignore characters in buffer
while(cin.get() != '\n')
continue;
return;
}
int page = 1;
string tmp;
stringstream ss;
auto path = traveled_airports.begin();
while(true) {
clearScreen();

cout << "--------------------------------------------------------\n";
cout << "|                    Flight Info                       |\n";
cout << "|                                                      |\n";

for(const auto &traveled_airport: *path) {
if(traveled_airport.second != "") {
tmp = "| (" + traveled_airport.second + ")";
cout << tmp;
for (int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
cout << "|\n";
}

tmp = "| Airport - " + traveled_airport.first.getCode() /* + " - " + traveled_airport.getName() */;
cout << tmp;
for (int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
cout << "|\n";
}
cout << "|                                                      |\n";

ss.str("");
ss << "| You traveled by " << path->size() << " airports.";
tmp = ss.str();
cout << tmp;
for (int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
cout << "|\n";
cout << "|                                                      |\n";

ss.str("");
ss << "| Page " << page << "/" << traveled_airports.size();
tmp = ss.str();
cout << tmp;
for (int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
cout << "|\n";
cout << "--------------------------------------------------------\n";

cout << "\nPress n(ext)/p(rev)/e(xit): ";

char opt;
while (true) {
cin >> opt;
if (opt == 'n') {
page++;
if (page > traveled_airports.size()) {
page = 1;
path = traveled_airports.begin();
} else
++path;
break;
} else if (opt == 'p') {
page--;
if (page < 1) {
page = traveled_airports.size();
path = traveled_airports.end(); --path;
} else
--path;
break;
} else if (opt == 'e') {
return;
}
}
}
}


