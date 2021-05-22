#include "util.h"
#include <vector>
#include <iostream>

using namespace std;

void driver(Graph& graph, bool print) {
    if (print) {
        cout << "Graph data:" << endl;
        cout << graph.print() << endl;
    }
    vector<int> topological = graph.topologicalSort();
    cout << "Topological sort:" << endl;
    for (int n : topological) {
        cout << n << " ";
    }
    cout << endl;
    cout << "Is bipartite? " << (graph.bipartiteGraph() ? "True" : "False") << endl;
    cout << "Shortest path from 0:" << endl << graph.shortestPath() << endl;
}

bool getInput() {
    cout << "Print graphs? (y/n): ";
    string ans;
    cin >> ans;
    if (ans[0] != 'y' && ans[0] != 'n') {
        cout << "Invalid selection, try again" << endl;
        return getInput();
    }
    return ans[0] == 'y';
}