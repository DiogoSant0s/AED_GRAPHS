#include "Graph.h"

Graph::Graph(bool dir): has_dir(dir) {}

int Graph::size_Nodes(){
    return (int) nodes.size();
}

int Graph::size_Flights(){
    int count = 0;
    for (auto const &n : nodes){
        count += (int) n.second.adj.size();
    }
    return count;
}

multiset<pair<string,int>, Distance> Graph::top_flights(int k){
    multiset<pair<string,int>, Distance> flights;
    flights.insert({"",0});
    for (auto const &n:nodes) {
        for (auto &p: flights) {
            if (flights.size() < k){
                flights.insert({n.first, n.second.adj.size()});
                break;
            }
            if (p.second < n.second.adj.size()) {
                flights.insert({n.first, n.second.adj.size()});
                break;
            }
        }
        while (flights.size() > k)
            flights.erase(prev(flights.end()));
    }
    return flights;
}

int Graph::Diameter(){
    int size = 0;
    for (auto const &n:nodes) {
        bfs_diameter(n.first);
        for (auto &i:nodes) {
            if (i.second.visited) {
                i.second.visited = false;
                if (i.second.travel_from_src.front().size() - 1 > size)
                    size = (int) i.second.travel_from_src.front().size() - 1;
            }
        }
    }
    return size;
}
void Graph::bfs_diameter(const string &airport_code) {
    setUnvisited();
    queue<string> q;
    q.push(airport_code);
    nodes[airport_code].visited = true;
    nodes[airport_code].travel_from_src.push_back({ { nodes[airport_code].airport, "" } });
    while (!q.empty()) {
        std::string u = q.front();
        q.pop();
        Node& node = nodes[u];
        for (const auto &e: node.adj) {
            std::string w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].travel_from_src=node.travel_from_src;
                nodes[w].travel_from_src.front().emplace_back(nodes[w].airport, e.airline);
            }
        }
    }
}

void Graph::shortestPath(const string& airport_code) {
    priority_queue<pair<string, double>, vector<pair<string, double>>, Distance> q;
    setUnvisited();
    nodes[airport_code].src_distance = 0;
    nodes[airport_code].travel_from_src.push_back({{nodes[airport_code].airport,""}});
    for (auto &node: nodes) {
        if (node.first != airport_code)
            node.second.src_distance = INF;
        else {
            q.emplace( node.first, node.second.src_distance );
        }
    }
    while(!q.empty()) {
        pair<string, double> u = q.top();
        q.pop();
        Node& node = nodes[u.first];
        for (auto &e: node.adj) {
            if (!wanted_airlines.empty() && wanted_airlines.find(e.airline) == wanted_airlines.end()) {
                continue;
            }
            double alt = node.src_distance + e.distance;
            Node &v = nodes[e.dest];
            if (alt < v.src_distance) {
                v.travel_from_src.clear();
                for (auto n : node.travel_from_src) {
                    n.emplace_back(v.airport,e.airline);
                    v.travel_from_src.push_back(n);
                }
                v.src_distance = alt;
                q.emplace( e.dest, alt );
            }
            else if (alt < INF && alt == v.src_distance ){
                bool flag = true;
                for (auto n : v.travel_from_src) {
                    auto it = n.end();
                    advance(it,-2);
                    if (it -> first == node.airport) {
                        flag = false;
                        break;
                    }
                }
                if (!flag) continue;
                for (auto n : node.travel_from_src) {
                    n.emplace_back(v.airport,e.airline);
                    v.travel_from_src.push_back(n);
                }
            }
        }
    }
}

void Graph::addNode(const string& airport_code, const Airport& airport) {
    nodes.insert({ airport_code, { airport, {}, false, INF, list<list<pair<Airport, string>>>() } });//n
}

void Graph::addEdge(const string& source_airport, const string& target_airport, const string& airline) {
    auto s_airport = nodes.find(source_airport);
    auto t_airport = nodes.find(target_airport);
    if (s_airport == nodes.end() || t_airport == nodes.end() || s_airport == t_airport) {
        return;
    }
    double distance = haversine(s_airport -> second.airport, t_airport -> second.airport);
    s_airport -> second.adj.push_back({ target_airport, airline, distance });
    if (!this -> has_dir) {
        t_airport -> second.adj.push_back({ source_airport, airline, distance });
    }
}

void Graph::setUnvisited() {
    for (auto &it: nodes) {
        it.second.visited = false;
        it.second.travel_from_src.clear();
    }
}

void Graph::dfs(const string& airport_code) {
    cout << nodes[airport_code].airport.getCode() << '\n';
    nodes[airport_code].visited = true;
    for (const auto &e: nodes[airport_code].adj) {
        Node& target_node = nodes[e.dest];
        if (!target_node.visited) {
            dfs(e.dest);
        }
    }
}

void Graph::bfs(const string& airport_code) {
    setUnvisited();
    queue<string> q;
    q.push(airport_code);
    nodes[airport_code].visited = true;
    nodes[airport_code].travel_from_src.push_back({ { nodes[airport_code].airport, "" } });
    while(!q.empty()) {
        string u = q.front();
        q.pop();
        Node& node = nodes[u];
        for (const auto &e: node.adj) {
            if (!wanted_airlines.empty() && wanted_airlines.find(e.airline) == wanted_airlines.end()) {
                continue;
            }
            string w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                for (auto n: node.travel_from_src) {
                    n.emplace_back(nodes[w].airport, e.airline);
                    nodes[w].travel_from_src.push_back(n);
                }
            }
            else if (node.travel_from_src.front().size() + 1 == nodes[w].travel_from_src.front().size()){
                bool flag = true;
                for (auto n : nodes[w].travel_from_src) {
                    auto it = n.end();
                    advance(it,-2);
                    if (it -> first == node.airport) {
                        flag = false;
                        break;
                    }
                }
                if (!flag) continue;
                for (auto n: node.travel_from_src) {
                    n.emplace_back(nodes[w].airport,e.airline);
                    nodes[w].travel_from_src.push_back(n);
                }
            }
        }
    }
}

Airport Graph::getAirport(const string& airport_code) const {
    return nodes.at(airport_code).airport;
}

list<list<pair<Airport, string>>> Graph::getTraveledAirports(const string &source_airport, const string &target_airport) {
    bfs(source_airport);
    return nodes[target_airport].travel_from_src;
}

double Graph::getShortestPath(const string& target_airport) {
    return nodes.at(target_airport).src_distance;
}

list<list<pair<Airport, string>>> Graph::getTraveledAirportsByDistance(const string &source_airport, const string &target_airport) {
    shortestPath(source_airport);
    return nodes[target_airport].travel_from_src;
}

string Graph::findAirport(double latitude, double longitude){
    string code;
    double latitude_min = INT64_MAX, longitude_min = INT64_MAX;
    for (const auto& node: nodes) {//V
        if (haversine(latitude,node.second.airport.getLatitude(),longitude,node.second.airport.getLongitude())<haversine(latitude,latitude_min,longitude,longitude_min)) {//log(n)
            code = node.second.airport.getCode();//1
            latitude_min=node.second.airport.getLatitude();//1
            longitude_min=node.second.airport.getLongitude();//1
        }
    }
    return code;
}

list<string> Graph::findAirports(double latitude, double longitude, int dist){
    list<string> airports ;
    for (const auto& node: nodes) {
        if (haversine(latitude,node.second.airport.getLatitude(),longitude,node.second.airport.getLongitude())<dist) {
            airports.push_back(node.first);
        }
    }
    return airports;
}

list<string> Graph::findAirportByCity(const string &city) {
    list<std::string> airports;
    for (const auto& node:nodes) {
        if (node.second.airport.getCity() == city)
            airports.push_back(node.first);
    }
    return airports;
}

set<string> Graph::getAirlinesFromAirport(const string &airport_code) const {
    set<string> airlines;
    for (auto &a: nodes.at(airport_code).adj) {
        airlines.insert(a.airline);
    }
    return airlines;
}

list<Airport> Graph::getAirportsReached(const string &source_airport, int k) {
    bfs(source_airport);
    list<Airport> airports;
    for (const auto &n: nodes) {
        const Node &node = n.second;
        if (node.airport.getCode() == source_airport) {
            continue;
        }
        if (node.travel_from_src.front().size() - 1 <= k) {
            airports.push_back(node.airport);
        }
    }

    return airports;
}

set<string> Graph::getCitiesReached(const string &source_airport, int k) {
    bfs(source_airport);
    set<string> cities;
    for (const auto &n: nodes) {
        const Node &node = n.second;
        if (node.airport.getCode() == source_airport) {
            continue;
        }
        if (node.travel_from_src.front().size() - 1 <= k) {
            cities.insert(node.airport.getCity());
        }
    }
    return cities;
}

set<string> Graph::getCountriesReached(const string &source_airport, int k) {
    bfs(source_airport);
    set<string> countries;
    for (const auto &n: nodes) {
        const Node &node = n.second;
        if (node.airport.getCode() == source_airport) {
            continue;
        }
        if (node.travel_from_src.front().size() - 1 <= k) {
            countries.insert(node.airport.getCountry());
        }
    }
    return countries;
}

set<string> Graph::getArrivalAirports(const string &airport_code) const {
    set<string> airports;
    for (auto &a: nodes.at(airport_code).adj) {
        airports.insert(a.dest);//log n
    }
    return airports;
}

set<string> Graph::getArrivalCities(const string &airport_code) const {
    set<string> cities;
    for (const Edge &edge: nodes.at(airport_code).adj) {
        cities.insert(nodes.at(edge.dest).airport.getCity());
    }
    return cities;
}

set<string> Graph::getArrivalCountries(const string &airport_code) const {
    set<string> countries;
    for (const Edge &edge: nodes.at(airport_code).adj) {
        countries.insert(nodes.at(edge.dest).airport.getCountry());
    }
    return countries;
}

bool Graph::checkIfAirportExists(const string &airport_code) const {
    return nodes.find(airport_code) != nodes.end();
}
