#include "graph.hpp"
#include "solve.hpp"

void Graph::add(Node n){
    graph.push_back(n);    
}

void Graph::add_edge(int from, edge data) {
    if (from - 1 >= 0 && from - 1 < (int)graph.size()) {
        graph[from - 1].connections.push_back(data);
    } else {
        cerr << "Erro: Índice inválido em add_edge: " << from << endl;
    }
}

Graph::~Graph(){
    graph.clear();
    rGraph.clear();
}

void Graph::print_graph() {
    for (Node &node : graph) {
        cout << "Node " << node.index << " :" << endl;
        if (node.connections.empty()) {
            cout << "  No connections\n";
        }
        for (edge &data : node.connections) {
            int flow = data.original_capacity - data.capacity; // Fluxo real
            cout << "  To: " << data.to 
                 << ", Flow: " << flow 
                 << ", Original Capacity: " << data.original_capacity << endl;
        }
    }
}

// Adiciona uma fonte unica e um fim unico
void Graph::graph_transform(){
    Node Source(vertices+1, 0); // Super Source
    Source.is_generator = true;
    Node Sink(vertices+2, 0);  // Super Sink
    
    // Adiciona o Source e o Sink ao grafo
    graph.push_back(Source);
    graph.push_back(Sink);

    for (size_t i = 0; i < graph.size() - 2; i++) { // Evitar usar o próprio Source/Sink na iteração
        Node &n = graph[i];
        if (n.is_generator) {
            edge data_gen(n.index, INT_MAX, 0); // Aresta com peso "infinito"
            add_edge(vertices + 1, data_gen);
        } 
        if (!n.is_generator) {
            edge data_con(vertices + 2, n.needed_flow, 0); // Aresta até o Sink com fluxo necessário
            add_edge(n.index, data_con);
        }
    }
}

int Graph::get_vertices(){
    return vertices;
}

int Graph::get_arestas(){
    return arestas;
}

vector<Node> Graph::get_graph(){
    return graph;
}

void Graph::initializeResidualGraph() {
    rGraph.clear();
    rGraph.resize(graph.size()); // Ajusta o tamanho do rGraph

    for (size_t u = 0; u < graph.size(); ++u) {
        Node residualNode(graph[u].index, graph[u].needed_flow);
        residualNode.is_generator = graph[u].is_generator;

        for (const edge& e : graph[u].connections) {
            // Aresta direta
            residualNode.connections.emplace_back(e.to, e.original_capacity, u);

            // Adiciona a aresta reversa ao grafo residual
            bool reverseEdgeExists = false;
            for (edge& re : rGraph[e.to].connections) {
                if (re.to == u) {
                    reverseEdgeExists = true;
                    break;
                }
            }
            if (!reverseEdgeExists) {
                rGraph[e.to].connections.emplace_back(u, 0, e.to);
            }
        }

        rGraph[u] = residualNode;
    }
}


bool Graph::bfs(int source, int sink, vector<int>& parent) {
    parent.assign(rGraph.size(), -1); // Ajusta o tamanho para rGraph
    vector<bool> visited(rGraph.size(), false);
    queue<int> q;

    q.push(source);
    visited[source] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (const edge& e : rGraph[u].connections) {
            if (!visited[e.to] && e.capacity > 0) { // Capacidade residual positiva
                parent[e.to] = u;
                if (e.to == sink)
                    return true;
                visited[e.to] = true;
                q.push(e.to);
            }
        }
    }
    return false;
}

int Graph::fordFulkerson(int source, int sink) {
    initializeResidualGraph(); // Inicializa o rGraph com base no grafo original

    vector<int> parent(vertices);
    int maxFlow = 0;

    while (bfs(source, sink, parent)) {
        int pathFlow = INT_MAX;

        // Encontra o fluxo máximo no caminho aumentante
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            for (edge& e : rGraph[u].connections) {
                if (e.to == v) {
                    pathFlow = min(pathFlow, e.capacity);
                    break;
                }
            }
        }

        // Atualiza capacidades residuais no caminho
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            for (edge& e : rGraph[u].connections) {
                if (e.to == v) {
                    e.capacity -= pathFlow; // Reduz capacidade no sentido do fluxo
                    break;
                }
            }
            for (edge& e : rGraph[v].connections) {
                if (e.to == u) {
                    e.capacity += pathFlow; // Aumenta capacidade no sentido contrário
                    break;
                }
            }
        }

        maxFlow += pathFlow; // Incrementa o fluxo máximo
    }

    return maxFlow;
}

void Graph::updateOriginalGraph() {
    for (size_t u = 0; u < graph.size(); ++u) {
        for (edge& e : graph[u].connections) {
            for (const edge& re : rGraph[u].connections) {
                if (e.to == re.to) {
                    e.capacity = e.original_capacity - re.capacity; // Fluxo efetivo
                    e.capacity = max(0, e.capacity); // Garante que o fluxo não é negativo
                    break;
                }
            }
        }
    }
}