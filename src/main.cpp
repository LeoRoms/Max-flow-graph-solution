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
        edge data(to, cost, from);
        city.add_edge(from, data);
    }

    city.graph_transform();  
    int max_flow = solve_max_flow(city.rGraph,V);
    cout << max_flow << endl;
    cout << verify_flow(city) << endl;
    cout << calculate_waste(city.rGraph) - max_flow << endl;

    //city.print_graph();
}