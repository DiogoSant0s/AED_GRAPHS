#include "string"
#include "Menu.h"

Menu::Menu(Airports a): airpot(a) {};

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
int Menu::getUserInput(vector<int> inputs) {
    int input;
    if(!cin){
        cin.ignore();
        cin.ignore(100,'\n');
        cin.clear();
    }
    cin >> input;
    while (cin.fail() || (find(inputs.begin(), inputs.end(), input) == inputs.end())) {
        if (cin.eof() || input == 0) {
            cout << "\nExiting\n\n";
            exit(0);
        }
        cin.clear();
        cin.ignore();
        cerr << "Not a valid input, please input one of the shown options: ";
        cin >> input;
    }
    cin.ignore(100, '\n');
    return input;
}

string Menu::getUserTextInput() {
    string input;
    getline(cin, input);
    if (cin.fail()) cout << "deez";
    while (cin.fail() || input.length() == 0) {
        if (cin.eof()) {
            cout << "\nExiting\n\n";
            exit(0);
        }
        cin.clear();
        cin.ignore(100, '\n');
        cerr << "Not a valid input, please try again: ";
        getline(cin, input);
    }
    return input;
}
void Menu::MainMenu() {
    List_Size = 15;
    printTitle();

    cout << "\n";
    cout << "\tMain Menu\n";
    cout << "(1) Best Route\n";
    cout << "(2) Flight Network Statistics\n";
    cout << "(3) \n";
    cout << "(4) Requests\n";
    cout << "(0) Exit\n";
    cout << " > ";

    vector<int> inputs = {0, 1, 2, 3, 4};
    int input;
    input = getUserInput(inputs);

    switch (input) {
        case 1:
            clearScreen();
            BestRouteMenu();
            break;
        case 2:
            clearScreen();
            StudentsMenu(List_Size);
            break;
        case 3:
            clearScreen();
            SchedulesMenu(List_Size);
            break;
        case 4:
            clearScreen();
            RequestMenu(List_Size);
            break;
        case 0:
            LoadData::processAllRequests(data.getStudents(), data.getUCs(), data.getSchedules(), data.getRequests());
            LoadData::archiveStudents(data.getStudents());
            exit(0);
        default:
            break;
    }
}

void Menu::BestRouteMenu(){
    int dep , dest;
    string departure, destination;

    cout << "Insert the following details\n\n";
    cout << "Departure:" << "\n";
    cout << "Choose the option that suits you" << "\n";
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
    showBestRoute(airport, departure, destination, dep, dest);
    break;
}

void Menu::showBestRoute(Airports &a, string departure, string destination, dep, dest){
    vector<string> res = manager.bestRouteDistribution(departure, destination, dep,dest);

    cout << "----------------------------------------------------------\n";

    cout << "The best route available from" << departure << "to" << destination << "is:\n";

    for(auto a:res){
        cout << " ->" << s << "airport\n";
    }

    cout << "-----------------------------------------------------------\n";

}




