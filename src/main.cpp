#include <iostream>
#include "graph.h"

using namespace std;

int main() {
    // cout << "Adj. List" << endl;
    // Graph a(cin, true);
    // cout << a.printAdjList() << endl;
    cout << "Adj. Matrix" << endl;
    Graph b;
    b.loadGraphMatrix(cin);
    cout << b.printMatrix() << endl;
}