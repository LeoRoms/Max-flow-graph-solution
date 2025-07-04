#ifndef SOLVE_HPP
#define SOLVE_HPP

#include "graph.hpp"
#include <queue>

bool bfs(vector<Node> &rGraph, int source, int sink, vector<int> &parent);

int solve_max_flow(vector<Node> &graph, int v); // correto

//void calculate_flow(Graph &net, int v);
int verify_flow(Graph &net);

int calculate_waste(vector<Node> rGraph); // correto

void find_critical(Graph &net);

void heapify(vector<edge>& edges, int n, int i);

void heapSort(vector<edge>& edges);

#endif