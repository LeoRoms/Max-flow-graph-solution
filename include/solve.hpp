#ifndef SOLVE_HPP
#define SOLVE_HPP

#include "graph.hpp"
#include <queue>

bool bfs(vector<Node> &rGraph, int source, int sink, vector<int> &parent);

int solve_max_flow(Graph &net, int v);

int verify_flow(Graph &net);

int calculate_waste(Graph &net);

void print_effective_flows(Graph &net);

#endif