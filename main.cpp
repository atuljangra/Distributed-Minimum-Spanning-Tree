#include <iostream>

#include <cstdlib>

#include <thread>
#include <vector>
#include <chrono>

#include "Prims.h"
#include "Node.h"
#include "Edge.h"
#include "Graph.h"

using namespace std;

// This variable will be extern-ed.
int number_of_nodes;

void printGraph(vector <int>);

int main (void) {
    // We need to take the input here.
    cin >> number_of_nodes;
    Graph *g = Graph::getInstance();

    vector <int> graph;
    graph.resize(number_of_nodes * number_of_nodes);
    
    int temp;
    for (int i = 0; i < number_of_nodes * number_of_nodes; i++) {
        cin >> temp;
        graph[i] = temp;
    }
     
    printGraph(graph);

    // Creating the graph.
    g -> createGraph(number_of_nodes, graph);
    g -> printGraph();
    
    // Distributing the graph.
    g -> distributeGraph();
    
    // Run all the nodes.
    g -> runNodes();
    
    // Wake one node up.
    g -> wakeOneNodeUp();
    delete g; 
    // Sleep for a while maybe?
    chrono::milliseconds duration(2000);
//    this_thread::sleep_for(duration);
    /*Prims *p = new Prims(graph);
    p -> findMst();
    p -> printMst(); 
    */
    return 0;
}

void printGraph(vector<int> v) {
    for (int i = 0; i < number_of_nodes; i++) {
        for (int j = 0; j < number_of_nodes; j++) {
            cout << v[i*number_of_nodes + j] << " ";
        }
        cout << endl;
    }
    cout << endl;

}


