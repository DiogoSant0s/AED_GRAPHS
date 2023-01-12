#include "Menu.h"

#include <sstream>

Menu::Menu() : data(Data()) {}

void Menu::printTitle() {
    cout << R"(
____ _ ____ ___  ____ ____ ___    _  _ ____ _  _ ____ ____ ____ _  _ ____ _  _ ___
|__| | |__/ |__] |  | |__/  |     |\/| |__| |\ | |__| | __ |___ |\/| |___ |\ |  |
|  | | |  \ |    |__| |  \  |     |  | |  | | \| |  | |__] |___ |  | |___ | \|  |
    )" << "\n";
}

void Menu::clearScreen() {
    for (int i = 0; i < 20; i++) {
        cout << "\n";
    }
}

void Menu::init() {
    while (true) {
        clearScreen();
        printTitle();
        cout << "--------------------------------------------------------\n";
        cout << "|                                                      |\n";
        cout << "| 1 - Best route                                       |\n";
        cout << "| 2 - Airport Information                              |\n";
        cout << "| 3 - Airline Information                              |\n";
        cout << "| 4 - Global Statistics                                |\n";
        cout << "|                                                      |\n";
        cout << "| 0 - Exit                                             |\n";
        cout << "--------------------------------------------------------\n";

        char opt;
        while (true) {
            cout << "\nOption: ";
            cin >> opt;
            if (opt <= '4' && opt >= '0' || opt == '9')
                break;
            cout << "Not a valid option, please choose another.\n";
        }

        switch (opt) {
            case '1':
                inputFlights();
                break;
            case '2':
                airportInfo();
                break;
            case '3':
                airlineInfo();
                break;
            case '4':
                globalInfo();
                break;
            default:
                clearScreen();
                return;
        }
    }
}

void Menu::inputFlights() const {
    while (true) {
        clearScreen();
        cout << "--------------------------------------------------------\n";
        cout << "|           How do you pretend to search?              |\n";
        cout << "|                                                      |\n";
        cout << "| 1 - Airport Code                                     |\n";
        cout << "| 2 - City                                             |\n";
        cout << "| 3 - Coordinates                                      |\n";
        cout << "| 4 - Coordinates (closest airport)                    |\n";
        cout << "|                                                      |\n";
        cout << "| 0 - Return to Main Menu                              |\n";
        cout << "--------------------------------------------------------\n";

        char opt;
        while (true) {
            cout << "\nOption: ";
            cin >> opt;
            if(opt <= '4' && opt >= '0')
                break;
            cout << "Not a valid option, please choose another.\n";
        }

        switch (opt) {
            case '1':
                inputAirport();
                break;
            case '2':
                inputCity();
                break;
            case '3':
                inputCoordinates(true);
                break;
            case '4':
                inputCoordinates(false);
                break;
            default:
                clearScreen();
                return;
        }
    }
}

void Menu::inputAirport() const {
    std::string source, target, tmp;
    std::stringstream ss;
    Airport airport;
    char opt;

    clearScreen();
    while (true) {
        cout << "Please enter source airport code: ";
        cin >> source;

        if (data.checkIfAirportExists(source)) {
            airport = data.getAirport(source);
            cout << '\n';
            cout << "--------------------------------------------------------\n";
            cout << "|                    Airport Info                      |\n";

            tmp = "| Code: " + airport.getCode();
            cout << tmp;
            for (int i = 0; i < 55 - tmp.length(); i++) {
                cout << " ";
            }
            cout << "|\n";
            tmp = "| Name : " + airport.getName();
            cout << tmp;
            for (int i = 0; i < 55 - tmp.length(); i++) {
                cout << " ";
            }
            cout << "|\n";
            tmp = "| City : " + airport.getCity();
            cout << tmp;
            for (int i = 0; i < 55 - tmp.length(); i++) {
                cout << " ";
            }
            cout << "|\n";
            tmp = "| Country : " + airport.getCountry();
            cout << tmp;
            for (int i = 0; i < 55 - tmp.length(); i++) {
                cout << " ";
            }
            cout << "|\n";
            cout << "--------------------------------------------------------\n";
            cout << "\nConfirm [y/n/e(xit)]: ";
            cin >> opt;
            if (opt == 'y') {
                break;
            }
            else if (opt == 'e') {
                return;
            }

            clearScreen();
        } else {
            cout << "Airport doesn't exists\n\n";
        }
    }

    clearScreen();
    while (true) {
        cout << "Please enter target airport code: ";
        cin >> target;

        if (data.checkIfAirportExists(target)) {
            airport = data.getAirport(target);
            cout << '\n';

            cout << "--------------------------------------------------------\n";
            cout << "|                    Airport Info                      |\n";

            tmp = "| Code: " + airport.getCode();
            cout << tmp;
            for (int i = 0; i < 55 - tmp.length(); i++) {
                cout << " ";
            }
            cout << "|\n";
            tmp = "| Name : " + airport.getName();
            cout << tmp;
            for (int i = 0; i < 55 - tmp.length(); i++) {
                cout << " ";
            }
            cout << "|\n";
            tmp = "| City : " + airport.getCity();
            cout << tmp;
            for (int i = 0; i < 55 - tmp.length(); i++) {
                cout << " ";
            }
            cout << "|\n";
            tmp = "| Country : " + airport.getCountry();
            cout << tmp;
            for (int i = 0; i < 55 - tmp.length(); i++) {
                cout << " ";
            }
            cout << "|\n";
            cout << "--------------------------------------------------------\n";
            cout << "\nConfirm [y/n/e(xit)]: ";
            cin >> opt;
            if (opt == 'y') {
                break;
            }
            else if (opt == 'e') {
                return;
            }

            clearScreen();
        } else {
            cout << "Airport doesn't exists\n\n";
        }
    }

    list<list<pair<Airport,string>>> traveled_airports = data.getTraveledAirports(source, target);
    pages(traveled_airports);
}

void Menu::inputCity() const {
    string source, target;
    Airport airport;
    char opt;
    clearScreen();
    while (true) {
        cout << "Please enter the source city: ";
        cin.ignore();
        getline(cin,source);
        cout << "\nConfirm [y/n/e(xit)]: ";
        cin >> opt;
        if (opt == 'y') {
            break;
        }
        else if (opt == 'e') {
            return;
        }
        clearScreen();
    }
    clearScreen();
    while (true) {
        cout << "Please enter the target city: ";
        cin.ignore();
        getline(cin,target);
        cout << "\nConfirm [y/n/e(xit)]: ";
        cin >> opt;
        if (opt == 'y') {
            break;
        }
        else if (opt == 'e') {
            return;
        }
        clearScreen();
    }
    list<list<pair<Airport, string>>> traveled_airports = data.localCity(source, target);
    pages(traveled_airports);
}

void Menu::inputCoordinates(bool option) const {
    double source_latitude, source_longitude, target_latitude, target_longitude;
    stringstream ss;
    Airport airport;
    list<string> source, target;
    char opt;
    clearScreen();
    while (true) {
        cout << "Please enter the source latitude: ";
        cin >> source_latitude;
        cout << "\nPlease enter the source longitude: ";
        cin >> source_longitude;
        cout << "\n\nConfirm [y/n/e(xit)]: ";
        cin >> opt;
        if (opt == 'y') {
            break;
        }
        else if (opt == 'e') {
            return;
        }
        clearScreen();
    }
    clearScreen();
    while(true) {
        cout << "Please enter the target latitude: ";
        cin >> target_latitude;
        cout << "\nPlease enter the target longitude: ";
        cin >> target_longitude;
        cout << "\n\nConfirm [y/n/e(xit)]: ";
        cin >> opt;
        if (opt == 'y') {
            break;
        }
        else if (opt == 'e') {
            return;
        }
        clearScreen();
    }
    list<list<pair<Airport, string>>> traveled_airports;
    if (option) {
        int dist;
        cout << "Insert desired radius: ";
        cin >> dist;
        traveled_airports = data.localCoordinates(source_latitude,source_longitude,target_latitude,target_longitude, dist);
    }
    else
        traveled_airports = data.localCoordinatesClosest(source_latitude,source_longitude,target_latitude,target_longitude);
    pages(traveled_airports);
}

void Menu::pages(const list<list<pair<Airport, string>>> &traveled_airports) {
    if (traveled_airports.empty()) {
        cout << "There is no way to travel!\n";
        cout << "\nPress <Enter> to go to search menu...";
        cin.ignore();
        while (cin.get() != '\n') {}
        return;
    }
    int page = 1;
    string tmp;
    stringstream ss;
    auto path = traveled_airports.begin();
    while (true) {
        clearScreen();

        cout << "--------------------------------------------------------\n";
        cout << "|                    Flight Info                       |\n";
        cout << "|                                                      |\n";

        for (const auto &traveled_airport: *path) {
            if (!traveled_airport.second.empty()) {
                tmp = "| (" + traveled_airport.second + ")";
                cout << tmp;
                for (int i = 0; i < 55 - tmp.length(); i++) {
                    cout << " ";
                }
                cout << "|\n";
            }

            tmp = "| Airport - " + traveled_airport.first.getCode();
            cout << tmp;
            for (int i = 0; i < 55 - tmp.length(); i++) {
                cout << " ";
            }
            cout << "|\n";
        }
        cout << "|                                                      |\n";
        ss.str("");
        ss << "| You traveled by " << path->size() << " airports.";
        tmp = ss.str();
        cout << tmp;
        for (int i = 0; i < 55 - tmp.length(); i++) {
            cout << " ";
        }
        cout << "|\n";
        cout << "|                                                      |\n";
        ss.str("");
        ss << "| Page " << page << "/" << traveled_airports.size();
        tmp = ss.str();
        cout << tmp;
        for (int i = 0; i < 55 - tmp.length(); i++) {
            cout << " ";
        }
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
                } else {
                    ++path;
                }
                break;
            } else if (opt == 'p') {
                page--;
                if (page < 1) {
                    page = (int) traveled_airports.size();
                    path = traveled_airports.end(); --path;
                } else {
                    --path;
                }
                break;
            } else if (opt == 'e') {
                return;
            }
        }
    }
}

void Menu::globalInfo() {
    clearScreen();

    int k;
    cout << "\nInsert limit of the top: ";
    cin >> k;
    clearScreen();
    cout << "Number of Aiports: " << data.size_aiports();
    cout << "\nNumber of Airlines: " << data.size_airlines();
    cout << "\nNumber of Flights: " << data.size_flights();
    cout << "\nDiameter: " << data.diameter();
    cout << "\n\nTop " << k << " Aiports with most flights:\n";
    for (const auto& i : data.top_flights(k)) {
        cout << i.first << " -> " << i.second << "\n";
    }
    cout << "\nPress <Enter> to go to main menu...";
    cin.ignore();
    while(cin.get() != '\n') {}
}

void Menu::airportInfo() {
    string airport_code;
    Airport airport;
    clearScreen();
    while (true) {
        cout << "Please enter the airport code: ";
        cin >> airport_code;
        if (data.checkIfAirportExists(airport_code)) {
            airport = data.getAirport(airport_code);
            break;
        }
        else {
            cout << "Airport doesn't exists\n\n";
        }
    }
    clearScreen();
    string tmp;
    cout << "--------------------------------------------------------\n";
    cout << "|                    Airport Info                      |\n";
    tmp = "| Code: " + airport.getCode();
    cout << tmp;
    for (int i = 0; i < 55 - tmp.length(); i++) {
        cout << " ";
    }
    cout << "|\n";
    tmp = "| Name : " + airport.getName();
    cout << tmp;
    for (int i = 0; i < 55 - tmp.length(); i++) {
        cout << " ";
    }
    cout << "|\n";
    tmp = "| City : " + airport.getCity();
    cout << tmp;
    for (int i = 0; i < 55 - tmp.length(); i++) {
        cout << " ";
    }
    cout << "|\n";
    tmp = "| Country : " + airport.getCountry();
    cout << tmp;
    for (int i = 0; i < 55 - tmp.length(); i++) {
        cout << " ";
    }
    cout << "|\n";
    cout << "|                                                      |\n";
    cout << "| 1 - Flighs                                           |\n";
    cout << "| 2 - Airlines                                         |\n";
    cout << "| 3 - Destination Cities                               |\n";
    cout << "| 4 - Destination Countries                            |\n";
    cout << "| 5 - Reachable in x flights                           |\n";
    cout << "|                                                      |\n";
    cout << "| 0 - Return to Main Menu                              |\n";
    cout << "--------------------------------------------------------\n";
    char opt;
    while (true) {
        cout << "\nOption: ";
        cin >> opt;
        if (opt <= '5' && opt >= '0') {
            break;
        }
        cout << "Not a valid option, please choose another.\n";
    }
    switch (opt) {
        case '1':
            flightsFromAirportInfo(airport_code);
            break;
        case '2':
            airlinesFromAirportInfo(airport_code);
            break;
        case '3':
            citiesFromAirportInfo(airport_code);
            break;
        case '4':
            countriesFromAirportInfo(airport_code);
            break;
        case '5':
            reachInFlights(airport_code);
            break;
        default:
            clearScreen();
            return;
    }
}

void Menu::airlineInfo() const {
    string airline_code;
    Airline airline;
    clearScreen();
    while (true) {
        cout << "Please enter the airline code: ";
        cin >> airline_code;
        if (data.checkIfAirlineExists(airline_code)) {
            airline = data.getAirline(airline_code);
            break;
        }
        else {
            cout << "Airline doesn't exists\n\n";
        }
    }
    clearScreen();
    string tmp;
    cout << "--------------------------------------------------------\n";
    cout << "|                    Airline Info                      |\n";
    tmp = "| Code: " + airline.getCode();
    cout << tmp;
    for (int i = 0; i < 55 - tmp.length(); i++) {
        cout << " ";
    }
    cout << "|\n";
    tmp = "| Name : " + airline.getName();
    cout << tmp;
    for (int i = 0; i < 55 - tmp.length(); i++) {
        cout << " ";
    }
    cout << "|\n";
    tmp = "| Call Sign : " + airline.getCallSign();
    cout << tmp;
    for (int i = 0; i < 55 - tmp.length(); i++) {
        cout << " ";
    }
    cout << "|\n";
    tmp = "| Country : " + airline.getCountry();
    cout << tmp;
    for (int i = 0; i < 55 - tmp.length(); i++) {
        cout << " ";
    }
    cout << "|\n";
    cout << "--------------------------------------------------------\n";
    cout << "\nPress <Enter> to go to main menu...";
    cin.ignore();
    while (cin.get() != '\n') {}
}

void Menu::flightsFromAirportInfo(const string& airport_code) const {
    set<string> airports = data.getArrivalAirport(airport_code);
    string tmp;
    stringstream ss;
    clearScreen();
    cout << "--------------------------------------------------------\n";
    cout << "| List of Airports:                                    |\n";
    cout << "|                                                      |\n";
    for (const string& code : airports) {
        tmp = "| Airport - " + data.getAirport(code).getCode();
        cout << tmp;
        for (int i = 0; i < 55 - tmp.length(); i++) {
            cout << " ";
        }
        cout << "|\n";
    }
    cout << "|                                                      |\n";
    ss << "| You can reach " << airports.size() << " airports.";
    tmp = ss.str();
    cout << tmp;
    for (int i = 0; i < 55 - tmp.length(); i++) {
        cout << " ";
    }
    cout << "|\n";
    cout << "--------------------------------------------------------\n";
    cout << "\nPress <Enter> to go to main menu...";
    cin.ignore();
    while (cin.get() != '\n') {}
}

void Menu::airlinesFromAirportInfo(const string &airport_code) const {
    list<Airline> airlines = data.getAirlinesFromAirport(airport_code);
    string tmp;
    stringstream ss;
    clearScreen();
    cout << "--------------------------------------------------------\n";
    cout << "| List of Airlines:                                    |\n";
    cout << "|                                                      |\n";
    for (const Airline& airline : airlines) {
        tmp = "| Airline - " + airline.getCode() ;
        cout << tmp;
        for (int i = 0; i < 55 - tmp.length(); i++) {
            cout << " ";
        }
        cout << "|\n";
    }
    cout << "|                                                      |\n";
    ss << "| Airport have " << airlines.size() << " airlines available.";
    tmp = ss.str();
    cout << tmp;
    for (int i = 0; i < 55 - tmp.length(); i++) {
        cout << " ";
    }
    cout << "|\n";
    cout << "--------------------------------------------------------\n";
    cout << "\nPress <Enter> to go to main menu...";
    cin.ignore();
    while (cin.get() != '\n') {}
}

void Menu::citiesFromAirportInfo(const string &airport_code) const {
    set<string> cities = data.getArrivalCities(airport_code);
    string tmp;
    stringstream ss;
    clearScreen();
    cout << "--------------------------------------------------------\n";
    cout << "| List of Cities:                                      |\n";
    cout << "|                                                      |\n";
    for (const string& city : cities) {
        tmp = "| " + city;
        cout << tmp;
        for(int i = 0; i < 55 - tmp.length(); i++) {
            cout << " ";
        }
        cout << "|\n";
    }
    cout << "|                                                      |\n";
    ss << "| You can reach " << cities.size() << " cities.";
    tmp = ss.str();
    cout << tmp;
    for (int i = 0; i < 55 - tmp.length(); i++) {
        cout << " ";
    }
    cout << "|\n";
    cout << "--------------------------------------------------------\n";
    cout << "\nPress <Enter> to go to main menu...";
    cin.ignore();
    while (cin.get() != '\n') {}
}

void Menu::countriesFromAirportInfo(const string& airport_code) const {
    set<string> countries = data.getArrivalCountries(airport_code);
    string tmp;
    stringstream ss;
    clearScreen();
    cout << "--------------------------------------------------------\n";
    cout << "| List of Countries:                                   |\n";
    cout << "|                                                      |\n";
    for (const string& country: countries) {
        tmp = "| " + country;
        cout << tmp;
        for (int i = 0; i < 55 - tmp.length(); i++) {
            cout << " ";
        }
        cout << "|\n";
    }
    cout << "|                                                      |\n";
    ss << "| You can reach " << countries.size() << " countries.";
    tmp = ss.str();
    cout << tmp;
    for (int i = 0; i < 55 - tmp.length(); i++) {
        cout << " ";
    }
    cout << "|\n";
    cout << "--------------------------------------------------------\n";
    cout << "\nPress <Enter> to go to main menu...";
    cin.ignore();
    while (cin.get() != '\n') {}
}

void Menu::reachInFlights(const string& airport_code) {
    clearScreen();
    cout << "--------------------------------------------------------\n";
    cout << "|         What information you want to know?           |\n";
    cout << "|                                                      |\n";
    cout << "| 1 - Airports                                         |\n";
    cout << "| 2 - Cities                                           |\n";
    cout << "| 3 - Countries                                        |\n";
    cout << "|                                                      |\n";
    cout << "| 0 - Return to Main Menu                              |\n";
    cout << "--------------------------------------------------------\n";
    char opt;
    while (true) {
        cout << "\nOption: ";
        cin >> opt;
        if (opt <= '3' && opt >= '0') {
            break;
        }
        cout << "Not a valid option, please choose another.\n";
    }
    int nr_flights;
    cout << "Maximum number of flights wanted: ";
    cin >> nr_flights;
    switch (opt) {
        case '1':
            reachableAirportsInFlights(airport_code, nr_flights);
            break;
        case '2':
            reachableCitiesInFlights(airport_code, nr_flights);
            break;
        case '3':
            reachableCountriesInFlights(airport_code, nr_flights);
            break;
        default:
            clearScreen();
            return;
    }
}

void Menu::reachableAirportsInFlights(const string& airport_code, int nr_flights) {
    list<Airport> airports = data.getAirportsReached(airport_code, nr_flights);
    string tmp;
    stringstream ss;
    clearScreen();
    cout << "--------------------------------------------------------\n";
    cout << "| List of Airports:                                    |\n";
    cout << "|                                                      |\n";
    for (const Airport& airport : airports) {
        tmp = "| Airport - " + airport.getCode();
        cout << tmp;
        for (int i = 0; i < 55 - tmp.length(); i++) {
            cout << " ";
        }
        cout << "|\n";
    }
    cout << "|                                                      |\n";
    ss << "| You can reach " << airports.size() << " airports.";
    tmp = ss.str();
    cout << tmp;
    for (int i = 0; i < 55 - tmp.length(); i++) {
        cout << " ";
    }
    cout << "|\n";
    cout << "--------------------------------------------------------\n";
    cout << "\nPress <Enter> to go to main menu...";
    cin.ignore();
    while (cin.get() != '\n') {}
}

void Menu::reachableCitiesInFlights(const string& airport_code, int nr_flights) {
    set<string> cities = data.getCitiesReached(airport_code, nr_flights);
    string tmp;
    stringstream ss;
    clearScreen();
    cout << "--------------------------------------------------------\n";
    cout << "| List of Cities:                                      |\n";
    cout << "|                                                      |\n";
    for (const string& city : cities) {
        tmp = "| " + city;
        cout << tmp;
        for (int i = 0; i < 55 - tmp.length(); i++) {
            cout << " ";
        }
        cout << "|\n";
    }
    cout << "|                                                      |\n";
    ss << "| You can reach " << cities.size() << " cities.";
    tmp = ss.str();
    cout << tmp;
    for (int i = 0; i < 55 - tmp.length(); i++) {
        cout << " ";
    }
    cout << "|\n";
    cout << "--------------------------------------------------------\n";
    cout << "\nPress <Enter> to go to main menu...";
    cin.ignore();
    while (cin.get() != '\n') {}
}

void Menu::reachableCountriesInFlights(const string& airport_code, int nr_flights) {
    set<string> countries = data.getCountriesReached(airport_code, nr_flights);
    string tmp;
    stringstream ss;
    clearScreen();
    cout << "--------------------------------------------------------\n";
    cout << "| List of Countries:                                   |\n";
    cout << "|                                                      |\n";
    for (const string& country: countries) {
        tmp = "| " + country;
        cout << tmp;
        for (int i = 0; i < 55 - tmp.length(); i++) {
            cout << " ";
        }
        cout << "|\n";
    }
    cout << "|                                                      |\n";
    ss << "| You can reach " << countries.size() << " countries.";
    tmp = ss.str();
    cout << tmp;
    for (int i = 0; i < 55 - tmp.length(); i++) {
        cout << " ";
    }
    cout << "|\n";
    cout << "--------------------------------------------------------\n";
    cout << "\nPress <Enter> to go to main menu...";
    cin.ignore();
    while (cin.get() != '\n') {}
}
