#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <vector>
#include <iostream>

using namespace std;//a

struct par{
    int to;
    int capacity;

    par(int a, int b) : to(a), capacity(b) {}
};

struct Node{
    int index;
    int needed_flow;
    bool is_generator;
    vector<par> connections;

    Node(int i, int f) : index(i), needed_flow(f), is_generator(false), connections() {}
};

class Graph{
public:
    Graph(int v, int e) : vertices(v), arestas(e), graph() {}
    ~Graph();
    void add(Node n);
    void add_edge(int from, par dupla);
    void print_graph();
    void graph_transform();

private:
    int vertices;
    int arestas;
    vector<Node> graph;
};

#endif