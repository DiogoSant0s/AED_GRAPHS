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
    while(true) {
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
        while(true) {
            cout << "\nOption: ";
            cin >> opt;
            if(opt <= '4' && opt >= '0' || opt == '9')
                break;
            cout << "Not a valid option, please choose another.\n";
        }

        switch(opt) {
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
    while(true) {
        clearScreen();
        std::cout << "--------------------------------------------------------\n";
        std::cout << "|           How do you pretend to search?              |\n";
        std::cout << "|                                                      |\n";
        std::cout << "| 1 - Airport Code                                     |\n";
        std::cout << "| 2 - City                                             |\n";
        std::cout << "| 3 - Coordinates                                      |\n";
        std::cout << "| 4 - Coordinates (closest airport)                    |\n";
        std::cout << "|                                                      |\n";
        std::cout << "| 0 - Return to Main Menu                              |\n";
        std::cout << "--------------------------------------------------------\n";

        char opt;
        while(true) {
            std::cout << "\nOption: ";
            std::cin >> opt;
            if(opt <= '4' && opt >= '0')
                break;
            std::cout << "Not a valid option, please choose another.\n";
        }

        switch(opt) {
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
    while(true) {
        std::cout << "Please enter source airport code: ";
        std::cin >> source;

        if(data.checkIfAirportExists(source)) {
            airport = data.getAirport(source);
            std::cout << '\n';

            std::cout << "--------------------------------------------------------\n";
            std::cout << "|                    Airport Info                      |\n";

            /* extract to a function to avoid code duplication */
            tmp = "| Code: " + airport.getCode();
            std::cout << tmp;
            for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
            std::cout << "|\n";

            tmp = "| Name : " + airport.getName();
            std::cout << tmp;
            for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
            std::cout << "|\n";

            tmp = "| City : " + airport.getCity();
            std::cout << tmp;
            for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
            std::cout << "|\n";

            tmp = "| Country : " + airport.getCountry();
            std::cout << tmp;
            for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
            std::cout << "|\n";
            std::cout << "--------------------------------------------------------\n";

            std::cout << "\nConfirm [y/n/e(xit)]: ";
            std::cin >> opt;
            if(opt == 'y')
                break;
            else if(opt == 'e')
                return;

            clearScreen();
        } else {
            std::cout << "Airport doesn't exists\n\n";
        }
    }

    clearScreen();
    while(true) {
        std::cout << "Please enter target airport code: ";
        std::cin >> target;

        if(data.checkIfAirportExists(target)) {
            airport = data.getAirport(target);
            std::cout << '\n';

            std::cout << "--------------------------------------------------------\n";
            std::cout << "|                    Airport Info                      |\n";

            /* extract to a function to avoid code duplication */
            tmp = "| Code: " + airport.getCode();
            std::cout << tmp;
            for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
            std::cout << "|\n";

            tmp = "| Name : " + airport.getName();
            std::cout << tmp;
            for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
            std::cout << "|\n";

            tmp = "| City : " + airport.getCity();
            std::cout << tmp;
            for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
            std::cout << "|\n";

            tmp = "| Country : " + airport.getCountry();
            std::cout << tmp;
            for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
            std::cout << "|\n";
            std::cout << "--------------------------------------------------------\n";

            std::cout << "\nConfirm [y/n/e(xit)]: ";
            std::cin >> opt;
            if(opt == 'y')
                break;
            else if(opt == 'e')
                return;

            clearScreen();
        } else {
            std::cout << "Airport doesn't exists\n\n";
        }
    }

    std::list<std::list<std::pair<Airport,std::string>>> traveled_airports = data.getTraveledAirports(source, target);
    pages(traveled_airports);
}

void Menu::inputCity() const {
    std::string source, target;
    Airport airport;
    char opt;
    clearScreen();
    while(true) {
        std::cout << "Please enter the source city: ";
        std::cin.ignore();
        getline(std::cin,source);
        std::cout << "\nConfirm [y/n/e(xit)]: ";
        std::cin >> opt;
        if(opt == 'y')
            break;
        else if(opt == 'e')
            return;
        clearScreen();
    }
    clearScreen();
    while (true) {
        std::cout << "Please enter the target city: ";
        std::cin.ignore();
        getline(std::cin,target);
        std::cout << "\nConfirm [y/n/e(xit)]: ";
        std::cin >> opt;
        if(opt == 'y')
            break;
        else if(opt == 'e')
            return;
        clearScreen();
    }
    std::list<std::list<std::pair<Airport, std::string>>> traveled_airports = data.localCity(source, target);
    pages(traveled_airports);
}

void Menu::inputCoordinates(bool option) const {
    double source_latitude, source_longitude, target_latitude, target_longitude;
    std::stringstream ss;
    Airport airport;
    std::list<std::string> source, target;
    char opt;
    clearScreen();
    while (true) {
        std::cout << "Please enter the source latitude: ";
        std::cin >> source_latitude;
        std::cout << "\nPlease enter the source longitude: ";
        std::cin >> source_longitude;
        std::cout << "\n\nConfirm [y/n/e(xit)]: ";
        std::cin >> opt;
        if(opt == 'y')
            break;
        else if(opt == 'e')
            return;
        clearScreen();
    }
    clearScreen();
    while(true) {
        std::cout << "Please enter the target latitude: ";
        std::cin >> target_latitude;
        std::cout << "\nPlease enter the target longitude: ";
        std::cin >> target_longitude;
        std::cout << "\n\nConfirm [y/n/e(xit)]: ";
        std::cin >> opt;
        if(opt == 'y')
            break;
        else if(opt == 'e')
            return;
        clearScreen();
    }
    std::list<std::list<std::pair<Airport, std::string>>> traveled_airports;
    if(option) {
        int dist;
        std::cout<<"Insert desired radius: ";
        std::cin>>dist;
        traveled_airports = data.localCoordinates(source_latitude,source_longitude,target_latitude,target_longitude, dist);
    }
    else
        traveled_airports = data.localCoordinatesClosest(source_latitude,source_longitude,target_latitude,target_longitude);
    pages(traveled_airports);
}

void Menu::pages(const std::list<std::list<std::pair<Airport, std::string>>> &traveled_airports) {
    if (traveled_airports.empty()) {
        std::cout << "There is no way to travel!\n";
        std::cout << "\nPress <Enter> to go to search menu...";
        /* wait for enter to be pressed */
        std::cin.ignore(); // ignore characters in buffer
        while(std::cin.get() != '\n')
            continue;
        return;
    }
    int page = 1;
    std::string tmp;
    std::stringstream ss;
    auto path = traveled_airports.begin();
    while(true) {
        clearScreen();

        std::cout << "--------------------------------------------------------\n";
        std::cout << "|                    Flight Info                       |\n";
        std::cout << "|                                                      |\n";

        for(const auto &traveled_airport: *path) {
            if(!traveled_airport.second.empty()) {
                tmp = "| (" + traveled_airport.second + ")";
                std::cout << tmp;
                for (int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
                std::cout << "|\n";
            }

            tmp = "| Airport - " + traveled_airport.first.getCode();
            std::cout << tmp;
            for (int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
            std::cout << "|\n";
        }
        std::cout << "|                                                      |\n";

        ss.str("");
        ss << "| You traveled by " << path->size() << " airports.";
        tmp = ss.str();
        std::cout << tmp;
        for (int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
        std::cout << "|\n";
        std::cout << "|                                                      |\n";

        ss.str("");
        ss << "| Page " << page << "/" << traveled_airports.size();
        tmp = ss.str();
        std::cout << tmp;
        for (int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
        std::cout << "|\n";
        std::cout << "--------------------------------------------------------\n";

        std::cout << "\nPress n(ext)/p(rev)/e(xit): ";

        char opt;
        while (true) {
            std::cin >> opt;
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
                    page = (int) traveled_airports.size();
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

void Menu::globalInfo() {
    clearScreen();

    int k;
    std::cout << "\nInsert limit of the top: ";
    std::cin>>k;

    clearScreen();

    std::cout << "Number of Aiports: " << data.size_aiports();
    std::cout << "\nNumber of Airlines: " << data.size_airlines();
    std::cout << "\nNumber of Flights: " << data.size_flights();
    std::cout << "\nDiameter: " << data.diameter();
    std::cout << "\n\nTop "<<k<<" Aiports with most flights:\n";
    for (const auto& i : data.top_flights(k))
        std::cout<<i.first<<" -> "<<i.second<<"\n";

    std::cout << "\nPress <Enter> to go to main menu...";

    /* wait for enter to be pressed */
    std::cin.ignore(); // ignore characters in buffer
    while(std::cin.get() != '\n')
        continue;
}


void Menu::airportInfo() {
    std::string airport_code;
    Airport airport;

    clearScreen();
    while(true) {
        std::cout << "Please enter the airport code: ";
        std::cin >> airport_code;

        if(data.checkIfAirportExists(airport_code)) {
            airport = data.getAirport(airport_code);
            break;
        }
        else
            std::cout << "Airport doesn't exists\n\n";
    }

    clearScreen();
    std::string tmp;

    std::cout << "--------------------------------------------------------\n";
    std::cout << "|                    Airport Info                      |\n";

    tmp = "| Code: " + airport.getCode();
    std::cout << tmp;
    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
    std::cout << "|\n";

    tmp = "| Name : " + airport.getName();
    std::cout << tmp;
    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
    std::cout << "|\n";

    tmp = "| City : " + airport.getCity();
    std::cout << tmp;
    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
    std::cout << "|\n";

    tmp = "| Country : " + airport.getCountry();
    std::cout << tmp;
    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
    std::cout << "|\n";

    std::cout << "|                                                      |\n";
    std::cout << "| 1 - Flighs                                           |\n";
    std::cout << "| 2 - Airlines                                         |\n";
    std::cout << "| 3 - Destination Cities                               |\n";
    std::cout << "| 4 - Destination Countries                            |\n";
    std::cout << "| 5 - Reachable in x flights                           |\n";
    std::cout << "|                                                      |\n";
    std::cout << "| 0 - Return to Main Menu                              |\n";
    std::cout << "--------------------------------------------------------\n";

    char opt;
    while(true) {
        std::cout << "\nOption: ";
        std::cin >> opt;
        if(opt <= '5' && opt >= '0')
            break;
        std::cout << "Not a valid option, please choose another.\n";
    }

    switch(opt) {
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
    std::string airline_code;
    Airline airline;

    clearScreen();
    while(true) {
        std::cout << "Please enter the airline code: ";
        std::cin >> airline_code;

        if(data.checkIfAirlineExists(airline_code)) {
            airline = data.getAirline(airline_code);
            break;
        }
        else
            std::cout << "Airline doesn't exists\n\n";
    }

    clearScreen();
    std::string tmp;

    std::cout << "--------------------------------------------------------\n";
    std::cout << "|                    Airline Info                      |\n";

    /* extract to a function to avoid code duplication */
    tmp = "| Code: " + airline.getCode();
    std::cout << tmp;
    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
    std::cout << "|\n";

    tmp = "| Name : " + airline.getName();
    std::cout << tmp;
    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
    std::cout << "|\n";

    tmp = "| Call Sign : " + airline.getCallSign();
    std::cout << tmp;
    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
    std::cout << "|\n";

    tmp = "| Country : " + airline.getCountry();
    std::cout << tmp;
    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
    std::cout << "|\n";
    std::cout << "--------------------------------------------------------\n";
    std::cout << "\nPress <Enter> to go to main menu...";

    /* wait for enter to be pressed */
    std::cin.ignore(); // ignore characters in buffer
    while(std::cin.get() != '\n')
        continue;
}

void Menu::flightsFromAirportInfo(const string& airport_code) const {
    std::set<std::string> airports = data.getArrivalAirport(airport_code);
    std::string tmp;
    std::stringstream ss;

    clearScreen();
    std::cout << "--------------------------------------------------------\n";

    std::cout << "| List of Airports:                                    |\n";
    std::cout << "|                                                      |\n";
    for(const string& code: airports) {
        tmp = "| Airport - " + data.getAirport(code).getCode();
        std::cout << tmp;
        for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
        std::cout << "|\n";
    }

    cout << "|                                                      |\n";

    ss << "| You can reach " << airports.size() << " airports.";
    tmp = ss.str();
    cout << tmp;
    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
    cout << "|\n";

    cout << "--------------------------------------------------------\n";
    cout << "\nPress <Enter> to go to main menu...";


    cin.ignore();
    while(cin.get() != '\n')
        continue;
}

void Menu::airlinesFromAirportInfo(const string &airport_code) const {
    list<Airline> airlines = data.getAirlinesFromAirport(airport_code);
    string tmp;
    stringstream ss;

    clearScreen();
    cout << "--------------------------------------------------------\n";

    cout << "| List of Airlines:                                    |\n";
    cout << "|                                                      |\n";
    for(const Airline& airline: airlines) {
        tmp = "| Airline - " + airline.getCode() ;
        std::cout << tmp;
        for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
        std::cout << "|\n";
    }

    cout << "|                                                      |\n";

    ss << "| Airport have " << airlines.size() << " airlines available.";
    tmp = ss.str();
    cout << tmp;
    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
    cout << "|\n";

    cout << "--------------------------------------------------------\n";
    cout << "\nPress <Enter> to go to main menu...";

    std::cin.ignore();
    while(std::cin.get() != '\n')
        continue;
}

void Menu::citiesFromAirportInfo(const string &airport_code) const {
    set<std::string> cities = data.getArrivalCities(airport_code);
    string tmp;
    stringstream ss;

    clearScreen();
    cout << "--------------------------------------------------------\n";

    std::cout << "| List of Cities:                                      |\n";
    std::cout << "|                                                      |\n";
    for(const std::string &city: cities) {
        tmp = "| " + city;
        std::cout << tmp;
        for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
        std::cout << "|\n";
    }

    std::cout << "|                                                      |\n";

    ss << "| You can reach " << cities.size() << " cities.";
    tmp = ss.str();
    std::cout << tmp;
    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
    std::cout << "|\n";

    std::cout << "--------------------------------------------------------\n";
    std::cout << "\nPress <Enter> to go to main menu...";

    /* wait for enter to be pressed */
    std::cin.ignore(); // ignore characters in buffer
    while(std::cin.get() != '\n')
        continue;
}

void Menu::countriesFromAirportInfo(const std::string &airport_code) const {
    std::set<std::string> countries = data.getArrivalCountries(airport_code);
    std::string tmp;
    std::stringstream ss;

    clearScreen();
    std::cout << "--------------------------------------------------------\n";

    std::cout << "| List of Countries:                                   |\n";
    std::cout << "|                                                      |\n";
    for(const std::string &country: countries) {
        tmp = "| " + country;
        std::cout << tmp;
        for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
        std::cout << "|\n";
    }

    std::cout << "|                                                      |\n";

    ss << "| You can reach " << countries.size() << " countries.";
    tmp = ss.str();
    std::cout << tmp;
    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
    std::cout << "|\n";

    std::cout << "--------------------------------------------------------\n";
    std::cout << "\nPress <Enter> to go to main menu...";

    /* wait for enter to be pressed */
    std::cin.ignore(); // ignore characters in buffer
    while(std::cin.get() != '\n')
        continue;
}

void Menu::reachInFlights(const std::string &airport_code) {
    clearScreen();
    std::cout << "--------------------------------------------------------\n";
    std::cout << "|         What information you want to know?           |\n";
    std::cout << "|                                                      |\n";
    std::cout << "| 1 - Airports                                         |\n";
    std::cout << "| 2 - Cities                                           |\n";
    std::cout << "| 3 - Countries                                        |\n";
    std::cout << "|                                                      |\n";
    std::cout << "| 0 - Return to Main Menu                              |\n";
    std::cout << "--------------------------------------------------------\n";

    char opt;
    while(true) {
        std::cout << "\nOption: ";
        std::cin >> opt;
        if(opt <= '3' && opt >= '0')
            break;
        std::cout << "Not a valid option, please choose another.\n";
    }

    int nr_flights;
    std::cout << "Maximum number of flights wanted: ";
    std::cin >> nr_flights;

    switch(opt) {
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
            return; }
}

void Menu::reachableAirportsInFlights(const std::string &airport_code, int nr_flights) {
    std::list<Airport> airports = data.getAirportsReached(airport_code, nr_flights);
    std::string tmp;
    std::stringstream ss;

    clearScreen();
    std::cout << "--------------------------------------------------------\n";

    std::cout << "| List of Airports:                                    |\n";
    std::cout << "|                                                      |\n";
    for(const Airport &airport: airports) {
        tmp = "| Airport - " + airport.getCode() /* + " - " + airport.getName() */;
        std::cout << tmp;
        for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
        std::cout << "|\n";
    }
    std::cout << "|                                                      |\n";

    ss << "| You can reach " << airports.size() << " airports.";
    tmp = ss.str();
    std::cout << tmp;
    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
    std::cout << "|\n";

    std::cout << "--------------------------------------------------------\n";
    std::cout << "\nPress <Enter> to go to main menu...";

    /* wait for enter to be pressed */
    std::cin.ignore(); // ignore characters in buffer
    while(std::cin.get() != '\n')
        continue;
}

void Menu::reachableCitiesInFlights(const std::string &airport_code, int nr_flights) {
    std::set<std::string> cities = data.getCitiesReached(airport_code, nr_flights);
    std::string tmp;
    std::stringstream ss;

    clearScreen();
    std::cout << "--------------------------------------------------------\n";

    std::cout << "| List of Cities:                                      |\n";
    std::cout << "|                                                      |\n";
    for(const std::string &city: cities) {
        tmp = "| " + city;
        std::cout << tmp;
        for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
        std::cout << "|\n";
    }
    std::cout << "|                                                      |\n";

    ss << "| You can reach " << cities.size() << " cities.";
    tmp = ss.str();
    std::cout << tmp;
    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
    std::cout << "|\n";

    std::cout << "--------------------------------------------------------\n";
    std::cout << "\nPress <Enter> to go to main menu...";


    std::cin.ignore();
    while(std::cin.get() != '\n')
        continue;
}

void Menu::reachableCountriesInFlights(const std::string &airport_code, int nr_flights) {
    std::set<std::string> countries = data.getCountriesReached(airport_code, nr_flights);
    std::string tmp;
    std::stringstream ss;

    clearScreen();
    std::cout << "--------------------------------------------------------\n";

    std::cout << "| List of Countries:                                   |\n";
    std::cout << "|                                                      |\n";
    for(const std::string &country: countries) {
        tmp = "| " + country;
        std::cout << tmp;
        for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
        std::cout << "|\n";
    }
    std::cout << "|                                                      |\n";

    ss << "| You can reach " << countries.size() << " countries.";
    tmp = ss.str();
    std::cout << tmp;
    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
    std::cout << "|\n";

    std::cout << "--------------------------------------------------------\n";
    std::cout << "\nPress <Enter> to go to main menu...";


    std::cin.ignore();
    while(std::cin.get() != '\n')
        continue;
}
