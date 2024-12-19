#include "graph.hpp"

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
    rGraph = graph;
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

void Graph::graph_update(){
    for(size_t i=0; i<graph.size(); i++){
        for(size_t j=0; j<graph[i].connections.size(); j++){
                graph[i].connections[j].capacity = rGraph[i].connections[j].capacity;
        }
    }
}

void Graph::node_update(){
    for (Node &node : graph) {
        for (edge &data : node.connections) {
            if(data.to == vertices+2 && data.original_capacity>0 && node.index < vertices){
                node.effective_flow = data.original_capacity - data.capacity; //cada vertice guarda capacidade efetiva
            } else {
                node.effective_flow += data.original_capacity - data.capacity; //vertice 1 e vertice 10 guardam capacidade max
            }
            
        }
    }
}

void Graph::print_node_capacity(){
    for(Node node : graph){
        cout << node.index << " : " << node.effective_flow << " | " << node.needed_flow << endl;
    }
}