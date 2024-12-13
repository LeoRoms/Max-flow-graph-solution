#include "graph.hpp"

using namespace std;

int main(){
    int V, E;
    cin >> V >> E;

    Graph city(V,E);

    for(int i=0; i<V; i++){
        int index, cost;
        cin >> index >> cost;
        Node n(index, cost);
        if(cost == 0) n.is_generator = true;
        city.add(n);
    }

    for(int i=0; i<E; i++){
        int from, to, cost;
        cin >> from >> to >> cost;
        par dupla(to,cost);
        city.add_edge(from, dupla);
    }

    city.graph_transform();

    // OK
    city.print_graph();
}