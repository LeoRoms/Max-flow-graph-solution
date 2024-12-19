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
            rGraph[v - 1].connections.push_back(edge(u, path_flow, 0));
            }
        }

        // Incrementa o fluxo máximo
        max_flow += path_flow;
    }
    return max_flow;
}

int verify_flow(Graph &net) {
    vector<Node> temp_graph = net.get_graph();
    int total_deficit = 0;

    for(Node node : temp_graph){
        if(node.needed_flow>0){ // se nao eh gerador ou sink / source
            total_deficit += node.needed_flow;
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

void heapify(std::vector<edge>& edges, int n, int i) {
    int largest = i;         // Assume que o nó atual é o maior
    int left = 2 * i + 1;    // Filho à esquerda
    int right = 2 * i + 2;   // Filho à direita

    // Verifica se o filho à esquerda é maior que o nó atual
    if (left < n && edges[left].original_capacity < edges[largest].original_capacity) {
        largest = left;
    }

    // Verifica se o filho à direita é maior que o maior encontrado até agora
    if (right < n && edges[right].original_capacity < edges[largest].original_capacity) {
        largest = right;
    }

    // Se o maior não é o nó atual, troca os elementos e continua ajustando o heap
    if (largest != i) {
        std::swap(edges[i], edges[largest]);
        heapify(edges, n, largest);
    }
}

void heapSort(std::vector<edge>& edges) {
    int n = edges.size();

    // Constrói o heap máximo
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(edges, n, i);
    }

    // Extrai elementos do heap um por um
    for (int i = n - 1; i > 0; i--) {
        // Move o maior elemento atual para o final do vetor
        std::swap(edges[0], edges[i]);

        // Reorganiza o heap para manter a propriedade do heap
        heapify(edges, i, 0);
    }
}



void find_critical(Graph &net){
    vector<Node> g = net.get_graph();
    vector<edge> critical_edges;
    int count = 0;
    for(Node node : g){
        for(edge e : node.connections){
            int flow = e.original_capacity - e.capacity;
            if(node.index < net.get_vertices() && flow == e.original_capacity && e.from != 0){
                count++;
                critical_edges.push_back(e);
            }
        }
    }
    heapSort(critical_edges);
    cout << count << endl;
    if(count){
        for(size_t i=0; i<count; i++){
            cout << critical_edges[i].from << " " << critical_edges[i].to << " " << critical_edges[i].original_capacity << endl;
        }
    }
}