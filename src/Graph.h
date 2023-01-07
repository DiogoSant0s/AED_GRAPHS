#ifndef AED_GRAPHS_GRAPH_H
#define AED_GRAPHS_GRAPH_H

#include <list>
#include <vector>
#include <queue>
#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include "Airports.h"

using namespace std;

/**
 * Classe usada para representar um grafo dirigido.
 * @details Esta classe representa aeroportos e os voos entre eles a partir de um vetor de nós, onde cada nó possui uma lista de adjacências.
 */
class Graph {
public:
    /**
     * Struct que representa uma aresta.
     * @details Contém o vértice de destino, o peso da aresta e um conjunto de airlines que realizam o voo.
     */
    struct Edge {
        int dest;
        int weight;
        set<string> airlines;
    };
    /**
     * Struct que representa um nó.
     * @details Contém uma lista de arestas que saem do nó, um booleano que indica se o nó já foi visitado numa pesquisa
     * e um inteiro que indica a distância do nó à origem da pesquisa.
     */
    struct Node {
        list<Edge> adj;
        bool visited;
        int distance;
    };
    /// Número de nós do grafo.
    int n;
    /// Vetor de nós do grafo.
    vector<Node> nodes;
    /**
     * @brief Construtor default classe Graph.
     * @Complexity Complexidade temporal: O(1)
     * @details Cria um grafo com 0 nós.
     */
    Graph();
    /**
     * Construtor classe Graph.
     * @Complexity Complexidade temporal: O(1)
     * @details Cria um grafo com n nós.
     * @param n Número de nós do grafo.
     */
    explicit Graph(int nodes);
    /**
     * Adiciona uma aresta ao grafo.
     * @Complexity Complexidade temporal: O(|E|)
     * @param src Nó de origem da aresta.
     * @param dest Nó de destino da aresta.
     * @param weight Peso da aresta.
     * @param airline Airline que realiza o voo.
     */
    void addEdge(int src, int dest, string airline, int weight = 1);
    /**
     * Retorna o grau de um nó.
     * @Complexity Complexidade temporal: O(1)
     * @param i Nó do qual se quer saber o grau.
     * @return Grau do nó.
     */
    int getOutDegree(int i);
    /**
     * Retorna o número de companhias aéreas diferentes que voam a partir de um nó.
     * Sendo E o número de arestas que saem do nó e Airlines o tamanho do set de airlines dessa aresta, temos:
     * @Complexity Complexidade temporal: O(|E| * |Airlines|)
     * @param i Nó do qual se quer saber o número de companhias aéreas.
     * @return Número de companhias aéreas.
     */
    int getAirlinesNumber(int i);
    /**
     * Retorna o número de destinos diferentes alcançáveis a partir de um nó.
     * Sendo E o número de arestas que saem do nó e Airlines o tamanho do set de airlines dessa aresta, temos:
     * @Complexity Complexidade temporal: O(|E|*|Airlines|)
     * @param i Nó de destino.
     * @return Número de destinos diferentes.
     */
    int getDestinationsNumber(int i);
    /**
     * @brief Retorna o número de destinos em países diferentes alcançáveis a partir de um nó.
     * Sendo E o número de arestas que saem do nó e Airlines o tamanho do set de airlines dessa aresta, temos:
     * @Complexity Complexidade temporal: O(|E|*|Airlines|)
     * @param i Nó de destino.
     * @return Número de destinos com países diferentes.
     */
    int getDestinationsCountries(int i, unordered_map<int, Airport> &airports);
    /**
     * @brief Retorna o número de arestas do grafo.
     * @Complexity Complexidade temporal: O(|V|)
     * @return Número de arestas do grafo.
     */
    int getNumEdges();
    /**
     * @brief Retorna o número de companhias aéreas.
     * @Complexity Complexidade temporal: O(|V|+|E|*|Airlines|)
     * @return Número de companhias aéreas.
     */
    int getCompanies();
    /**
     * @brief Retorna o diâmetro do grafo.
     * Para obter o diametro do grafo, é necessário calcular o menor caminho entre todos os pares de nós.
     * Para isso é necesário um BFS para cada nó.
     * @Complexity Complexidade temporal: O(|V| * (|V| + |E|)).
     */
    int getDiameter();
    /**
     * Retorna os destinos alcançáveis a partir de um nó com r voos ou menos.
     * É utilizado um simples BFS, adicionando à fila todos os nós com distância <= r.
     * @Complexity Complexidade temporal: O(|V|+|E|)
     * @param src
     * @param r
     * @return set<int> com os destinos alcançáveis.
     */
    set<int> getDestinations(int src, int r);
    /**
     * Retorna o vetor de nós do grafo.
     * @Complexity Complexidade temporal: O(1)
     * @return Vector com os nós do grafo.
     */
    vector<Node> getNodes() const;
    /**
     * @brief Função usada para determinar os i aeroportos com mais voos de uma rede.
     * @details Esta função percorre cada nó (aeroporto) da rede e determina o número de voos que saem desse aeroporto,
     * com auxílio da função getDestinationNumber(). Guarda todos os resultados num vetor e
     * ordena por ordem decrescente de voos e retorna apenas os i primeiros.
     * @Complexity Complexidade temporal: O(|V| * |E| * |Airlines|)
     * @param i Número de aeroportos a retornar.
     * @return Vetor de tamanho i com os pares aeroporto-voos que têm maior número de voos.
     */
    vector<pair<int, int>> getTopAirports(int i);
    /**
     * @details Esta função utiliza um DFS para determinar os pontos de articulação da rede.
     * @Complexity Complexidade temporal: O(|V| + |E|)
     * @return set<int> com os pontos de articulação.
     */
    set<int> getArticulationPoints();
    /**
     * @details Esta função utiliza um DFS para determinar os pontos de articulação da rede.
     * Mas para cada chamada do DFS também é feita uma interseção com o set de companhias aéreas da aresta.
     * @Complexity Complexidade temporal é: O(|V| + |E| * |Airlines|)
     * @param airlines_to_consider Companhias aéreas a considerar.
     * @return set<int> com os pontos de articulação.
     */
    set<int> getArticulationPoints(set<string> &airlines_to_consider);
    /**
     * @details Esta função utiliza um BFS para determinar os caminhos mais curtos entre os aeroportos de origem e os de destino.
     * São passados vários aeroportos para permitir pesquisas a partir e para cidades com mais de um aeroporto ou pontos proximos de dadas coordenadas.
     * @Complexity Complexidade temporal: O(|V| + |E|)
     * @param sources
     * @param destination
     * @return list<list<int>> com os caminhos mais curtos (em número de voos).
     */
    list<list<pair<int, string>>> least_flights(const vector<int>& sources, const vector<int>& destination);
    /**
     * Esta função utiliza um BFS para determinar os caminhos mais curtos entre os aeroportos de origem e os de destino, considerando apenas
     * as companhias aéreas passadas.
     * São passados vários aeroportos para permitir pesquisas a partir e para cidades com mais de um aeroporto ou pontos proximos de dadas coordenadas.
     * @Complexity Complexidade temporal: O(|V| + |E| * |Airlines|)
     * @param sources
     * @param destination
     * @param airlines_to_consider
     * @return list<list<int>> com os caminhos mais curtos (em número de voos), considerando apenas as companhias aéreas passadas.
     */
    list<list<pair<int, string>>> least_flights(const vector<int>& sources, const vector<int>& dest, const set<string> &airlines_to_consider);
    /**
     * @brief Retorna os caminhos mais curtos em distância física entre os aeroportos de origem e os de destino.
     * Esta função utiliza o algoritmo de Dijkstra (sem priority queue) para determinar os caminhos mais curtos entre os aeroportos de origem e os de destino.
     * São passados vários aeroportos para permitir pesquisas a partir e para cidades com mais de um aeroporto ou pontos proximos de dadas coordenadas.
     * @Complexity Complexidade temporal: O(|V| + |E|), o mesmo que o BFS.
     * @param sources
     * @param destination
     * @return list<list<int>> com os caminhos mais curtos (em distância).
     */
    list<list<pair<int, string>>> least_flights_with_distance(const vector<int>& src, const vector<int>& dest);
    /**
     * Esta função utiliza o algoritmo de Dijkstra (sem priority queue) para determinar os caminhos mais curtos entre os aeroportos de origem e os de destino.
     * São passados vários aeroportos para permitir pesquisas a partir e para cidades com mais de um aeroporto ou pontos proximos de dadas coordenadas.
     * São considerados apenas voos feitos pelas companhias aéreas passadas.
     * @Complexity Complexidade temporal: O(|V| + |E| * |Airlines|)
     * @param sources
     * @param destination
     * @param airlines_to_consider
     * @return list<list<int>> com os caminhos mais curtos (em distância), considerando apenas as companhias aéreas passadas.
     */
    list<list<pair<int, string>>> least_flights_with_distance(const vector<int>& src, const vector<int>& dest, const set<string>& airlines_to_consider);
    /**
     * Esta função utiliza apenas um DFS para determinar os pontos de articulação da rede.
     * Os pontos são guardados num set passado por referência.
     * @Complexity Complexidade temporal: O(|V| + |E|)
     * @param v
     * @param index
     * @param num
     * @param low
     * @param s
     * @param ap
     * @param first
     */
    void articulationPointsDFS(int v, int index, vector<int>& num, vector<int>& low, unordered_set<int>& s, set<int>& ap, bool first = false);
    /**
     * Esta função utiliza apenas um DFS para determinar os pontos de articulação da rede de um conjunto de companhias aéreas.
     * Os pontos são guardados num set.
     * @Complexity Complexidade temporal: O(|V| + |E| * |Airlines|)
     * @param v
     * @param index
     * @param num
     * @param low
     * @param s
     * @param ap
     * @param airlines_to_consider
     * @param first
     * @return set<int> com os pontos de articulação da rede de um conjunto de companhias aéreas.
     */
    set<int> articulationPointsDFS(int v, int index, vector<int>& num, vector<int>& low, unordered_set<int>& s, set<int>& ap, set<string> &airlines_to_consider, bool first = false);
};

#endif //AED_GRAPHS_GRAPH_H
