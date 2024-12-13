#include "graph.hpp"

void Graph::add(Node n){
    graph.push_back(n);    
}

void Graph::add_edge(int from, par dupla){
    graph[from-1].connections.push_back(dupla);
}

Graph::~Graph(){
    graph.clear();
}

void Graph::print_graph(){
    for(Node node : graph){
        cout << node.index << " - to | flow:" << endl;
        if(!node.connections.size()) cout << "no connections\n";
        for(par dupla : node.connections){
            cout << dupla.to << " | " << dupla.capacity << endl;
        }
    }
}

// Adiciona uma fonte unica e um fim unico
void Graph::graph_transform(){
    Node Source(vertices+1,0); // Super Source -> conecta a todos os geradores com arestas de peso: max_int (em tese infinito)
    Source.is_generator = true;
    Node Sink(vertices+2,0); // Super Sink -> todos os consumidores conectam a ele com arestas de peso: node.needed_flow
    
    graph.push_back(Source);
    graph.push_back(Sink);

    for(Node n : graph){
        if(n.is_generator && n.index != vertices+1){
            par dupla_gen(n.index,2147483647);
            add_edge(vertices+1,dupla_gen);
        }
        if(!n.is_generator && n.index != vertices+2){
            par dupla_con(vertices+2, n.needed_flow);
            add_edge(n.index, dupla_con);
        }
    }
}