#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <vector>
#include <iostream>
#include <climits>
#include <queue>

using namespace std;

struct edge{
    int from;
    int to;
    int capacity;
    int original_capacity;

    edge(int to, int capacity, int from) : from (from), to(to), capacity(capacity), original_capacity(capacity) {}
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

    int fordFulkerson(int source, int sink);
    void updateOriginalGraph();

private:
    int vertices;
    int arestas;
    vector<Node> graph;
    vector<Node> rGraph;

    bool bfs(int source, int sink, vector<int>& parent);
    void initializeResidualGraph();
};

#endif