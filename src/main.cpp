#include <iostream>
#include "graph.h"

using namespace std;

int main() {
    cout << "Adj. List" << endl;
    Graph a("data.txt", true);
    cout << a.print() << endl;
    cout << a.bfs(3, 4) << endl;
    cout << a.dfs(3, 4) << endl;
    cout << "Adj. Matrix" << endl;
    Graph b("data.txt", false);
    cout << b.print() << endl;
    cout << b.bfs(3, 4) << endl;
    cout << b.dfs(3, 4) << endl;
}