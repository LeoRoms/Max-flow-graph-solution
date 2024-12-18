#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <vector>
#include <iostream>
#include <climits>

using namespace std;

struct edge{
    int from;
    int to;
    int capacity;
    int original_capacity;

    edge(int to, int cost, int from) : from (from), to(to), capacity(cost), original_capacity(cost) {}
};

struct Node{
    int index;
    int needed_flow;
    int effective_flow;
    bool is_generator;
    vector<edge> connections;

    Node(int i, int f) : index(i), needed_flow(f), effective_flow(0), is_generator(false), connections() {}
};

class Graph{
public:
    Graph(int v, int e) : vertices(v), arestas(e), graph() {}
    ~Graph();
    void add(Node n);
    void add_edge(int from, edge data);
    void print_graph();
    void graph_transform();

    int get_vertices();
    int get_arestas();
    vector<Node> get_graph();
    void graph_update();
    void node_update();
    void print_node_capacity();

    vector<Node> rGraph;

private:
    int vertices;
    int arestas;
    vector<Node> graph;
};

#endif