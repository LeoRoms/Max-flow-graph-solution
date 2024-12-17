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
}

void Graph::print_graph(){
    for(Node node : rGraph){
        cout << node.index << " - to | capacity | original capacity:" << endl;
        if(!node.connections.size()) cout << "no connections\n";
        for(edge data : node.connections){
            data.capacity = data.original_capacity - data.capacity;
            cout << data.to << " | " << data.capacity << " " << data.original_capacity <<  endl;
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
            edge data_gen(n.index, INT_MAX); // Aresta com peso "infinito"
            add_edge(vertices + 1, data_gen);
        } 
        if (!n.is_generator) {
            edge data_con(vertices + 2, n.needed_flow); // Aresta até o Sink com fluxo necessário
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