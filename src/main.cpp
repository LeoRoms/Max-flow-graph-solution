#include "graph.hpp"
#include "solve.hpp"

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
        edge data(to,cost);
        city.add_edge(from, data);
    }

    city.graph_transform();
    //city.print_graph();   

    cout << solve_max_flow(city.rGraph,V) << endl;
    cout << verify_flow(city) << endl;
    cout << calculate_waste(city.rGraph) << endl;

    city.print_graph();
}