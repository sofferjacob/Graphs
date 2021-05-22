#include <iostream>
#include "graph.h"
#include "util.h"

using namespace std;

int main() {
    cout << "Graph Algorithms" << endl;
    bool printGraphs = getInput();
    Graph a("petersen.mtx", Matrix);
    Graph b("weighted2.txt", Weighted);
    Graph c("bipartite.txt", Matrix);
    cout << "Graph A (petersen.mtx, unweighted):" << endl;
    driver(a, printGraphs);
    cout << "Graph B (weighted2.txt, weighted):" << endl;
    driver(b, printGraphs);
    cout << "Graph C (bipartite.txt, unweighted):" << endl;
    driver(c, printGraphs);
}