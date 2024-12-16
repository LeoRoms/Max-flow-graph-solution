#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <vector>
#include <iostream>
#include <climits>

using namespace std;

struct edge{
    int to;
    int capacity;
    int original_capacity;

    edge(int a, int b) : to(a), capacity(b), original_capacity(b) {}
};

struct Node{
    int index;
    int needed_flow;
    bool is_generator;
    vector<edge> connections;

    Node(int i, int f) : index(i), needed_flow(f), is_generator(false), connections() {}
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

    vector<Node> rGraph;

private:
    int vertices;
    int arestas;
    vector<Node> graph;
};

#endif