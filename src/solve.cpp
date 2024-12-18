#include "solve.hpp"

bool bfs(vector<Node> &rGraph, int source, int sink, vector<int> &parent) {
    vector<bool> visited(source-1, false);

    queue<int> q;
    q.push(source);
    visited[source - 1] = true;
    parent[source - 1] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (edge &edge : rGraph[u - 1].connections) {
            int v = edge.to;
            if (!visited[v - 1] && edge.capacity > 0) {
                q.push(v);
                visited[v - 1] = true;
                parent[v - 1] = u;

                if (v == sink) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Ford_Fulkerson algorithm for max flow / min cut
int solve_max_flow(vector<Node> &rGraph, int v) {
    int source = v + 1; // Super Source
    int sink = v + 2;   // Super Sink

    vector<int> parent(rGraph.size(), -1);
    int max_flow = 0;

    while (bfs(rGraph, source, sink, parent)) {
        int path_flow = INT_MAX;

        // Acha o fluxo mínimo no caminho aumentante
        for (int v = sink; v != source; v = parent[v - 1]) {
            int u = parent[v - 1];
            for (edge &edge : rGraph[u - 1].connections) {
                if (edge.to == v) {
                    path_flow = min(path_flow, edge.capacity);
                    break;
                }
            }
        }
        // Alteracao possível: atualizar as capacidades no prórpio grafo! -> muda as capacidades das arestas no fim 
        // Atualiza as capacidades residuais
        for (int v = sink; v != source; v = parent[v - 1]) {
            int u = parent[v - 1];

            // Atualiza a aresta direta
            for (edge &edge : rGraph[u - 1].connections) {
                if (edge.to == v) {
                    edge.capacity -= path_flow;
                    break;
                }
            }
            // Atualiza a aresta residual
            bool found = false;
            for (edge &edge : rGraph[v - 1].connections) {
                if (edge.to == u) {
                    edge.capacity += path_flow;
                    found = true;
                    break;
                }
            }
            // Se a aresta residual não existir, adicioná-la
            if (!found) {
            rGraph[v - 1].connections.push_back(edge(u, path_flow));
            }
        }

        // Incrementa o fluxo máximo
        max_flow += path_flow;
    }
    return max_flow;
}

int verify_flow(Graph &net) {
    vector<Node> rGraph = net.get_graph();
    int total_deficit = 0;

    // Itera sobre todos os vértices
    for (const Node &node : rGraph) {
        if (!node.is_generator && node.needed_flow > 0) {
            int received_flow = 0;

            // Soma os fluxos que chegam no nó atual
            for (const Node &other : rGraph) {
                for (const edge &connection : other.connections) {
                    if (connection.to == node.index) {
                        received_flow += connection.capacity; // Ajustar com base no residual
                    }
                }
            }

            // Calcula o déficit de fluxo, se houver
            if (received_flow < node.needed_flow) {
                int deficit = node.needed_flow - received_flow;
                total_deficit += deficit;
            }
        }
    }
    return total_deficit;
}

int calculate_waste(vector<Node> rGraph){
    int waste = 0;
    for(Node node : rGraph){
        if(node.is_generator){
            for(edge data : node.connections){
                if(data.capacity < 2000000) waste += data.capacity;
            }   
        }
    }
    return waste;
}
