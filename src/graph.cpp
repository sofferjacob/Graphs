#include <stdexcept>
#include <sstream>
#include <set>
#include <fstream>
#include "linear/queue.h"
#include "linear/quick_sort.h"
#include "graph.h"
#include "heap.h"
#include "node.h"

using namespace std;

Graph::Graph() : type(None) {}

Graph::Graph(std::istream& input, GraphType type) {
    if (type == List) {
        loadGraphList(input);
    }
    else if (type == Matrix) {
        loadGraphMatrix(input);
    }
    else if (type == Weighted) {
        loadWeightedGraph(input);
    }
    else {
        throw invalid_argument("Invalid graph type");
    }
}

Graph::Graph(std::string filename, GraphType type) {
    ifstream file(filename);
    if (!file.good()) {
        file.close();
        throw invalid_argument("File not found");
    }
    if (type == List) loadGraphList(file);
    else if (type == Matrix) loadGraphMatrix(file);
    else if (type == Weighted) loadWeightedGraph(file);
    else throw invalid_argument("Invalid graph type");
    file.close();
}

void Graph::loadGraphList(std::istream& input) {
    // if (data->size() > 0) clear();
    std::string line;
    int i = 0;
    while (std::getline(input, line)) {
        if (i == 0) {
            i++;
            continue;
        }
        if (i == 1) {
            std::vector<int> res;
            split(line, res);
            for (int i = 0; i < res.size(); i++)
                cout << res[i] << endl;
            numNodes = res[0];
            numEdges = res[1];
            data = new vector<int>[numNodes + 1];
            type = List;
            i++;
            continue;
        }
        vector<int> res;
        split(line, res);
        int u = res[0];
        int v = res[1];
        data[u].push_back(v);
        // data[v].push_back(u); /* Uncomment for undirected graphs */
        i++;
    }
}

void Graph::loadGraphMatrix(std::istream& input) {
    // if (data->size() > 0) clear();
    std::string line;
    int i = 0;
    while (std::getline(input, line)) {
        if (i == 0) {
            i++;
            continue;
        }
        if (i == 1) {
            std::vector<int> res;
            split(line, res);
            numNodes = res[0];
            numEdges = res[1];
            //matrix = vector<vector<int> >(numNodes + 1, vector<int>(numNodes + 1, 0));
            data = new vector<int>[numNodes + 1];
            for (int j = 0; j <= numNodes; j++) {
                for (int k = 0; k <= numNodes; k++) {
                    data[j].push_back(0);
                }
            }
            type = Matrix;
            i++;
            continue;
        }
        vector<int> res;
        split(line, res);
        int u = res[0];
        int v = res[1];
        data[u].at(v) = 1;
        // data[v].at(u) = 1; /* Uncomment for undirected graphs */
        i++;
    }
}

void Graph::loadWeightedGraph(std::istream& input) {
    std::string line;
    int i = 0;
    while (std::getline(input, line)) {
        if (i == 0) {
            i++;
            continue;
        }
        if (i == 1) {
            std::vector<int> res;
            split(line, res);
            numNodes = res[0];
            numEdges = res[1];
            data = new vector<int>[numNodes + 1];
            for (int j = 0; j <= numNodes; j++) {
                for (int k = 0; k <= numNodes; k++) {
                    data[j].push_back(0);
                }
            }
            type = Weighted;
            i++;
            continue;
        }
        vector<int> res;
        split(line, res);
        int u = res[0];  // Origin node
        int v = res[1];  // Distance (weight) of edge
        int w = res[2];  // Destination node
        data[u].at(w) = v;
        i++;
    }
}

void Graph::split(std::string line, std::vector<int>& res) {
    int strPos = line.find(" ");
    int lastPos = 0;
    while (strPos != std::string::npos) {
        res.push_back(stoi(line.substr(lastPos, strPos - lastPos)));
        lastPos = strPos + 1;
        strPos = line.find(" ", lastPos);
    }
    res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}

string Graph::print() {
    if (type == List) return printAdjList();
    else if (type == Matrix) return printMatrix();
    else if (type == Weighted) return printWeighted();
    else {
        throw invalid_argument("A graph must be loaded before using this operation");
    }
}

string Graph::printWeighted() {
    stringstream aux;
    for (int i = 0; i <= numNodes; i++) {
        aux << i << ": [" << endl;
        for (int j = 0; j <= numNodes; j++) {
            if (j == i) continue;
            if (data[i].at(j) == 0) continue;
            aux << "  " << j << "; weight: " << data[i].at(j) << "," << endl;
        }
        aux << "]," << endl;
    }
    return aux.str();
}

string Graph::printAdjList() {
    stringstream aux;
    for (int i = 0; i <= numNodes; i++) {
        aux << "vertex "
            << i << " :";
        for (int j = 0; j < data[i].size(); j++) {
            aux << " " << data[i][j];
        }
        aux << " ";
    }
    return aux.str();

}

string Graph::printMatrix() {
    stringstream aux;
    for (int i = 0; i <= numNodes; i++) {
        aux << i << ": [" << endl;
        for (int j = 0; j <= numNodes; j++) {
            if (j == i) continue;
            if (data[i].at(j) == 0) continue;
            aux << "  " << j << "," << endl;
        }
        aux << "]," << endl;
    }
    return aux.str();
}

vector<int> Graph::getAdjecentNodes(int n) {
    if (type == List) {
        return data[n];
    }
    else {
        vector<int> res;
        for (int i = 0; i <= numNodes; i++) {
            if (data[n][i] != 0) res.push_back(i);
        }
        return res;
    }
}

string Graph::bfs(int start, int finish) {
    if (type == None) {
        throw invalid_argument("A graph must be loaded before using this operation");
    }
    stringstream aux;
    if (finish == -1) {
        finish = numNodes;
    }
    Queue<int> queue;
    set<int, greater<int> > seen;
    queue.push(start);
    while (!queue.isEmpty())
    {
        int node = queue.poll();
        vector<int> adj = getAdjecentNodes(node);
        if (seen.find(node) == seen.end()) {
            seen.insert(node);
            if (node == finish) {
                aux << "Found node: " << node << endl;
                break;
            }
            else {
                aux << node << endl;
            }
        }
        for (int n : adj) {
            if (seen.find(n) == seen.end()) {
                queue.push(n);
            }
        }
    }
    aux << "Visited nodes:" << endl;
    for (set<int>::iterator it = seen.begin(); it != seen.end(); ++it) {
        aux << *it << endl;
    }
    return aux.str();
}

void Graph::exploreDFS(int node, vector<bool>& visited, stringstream& aux) {
    visited[node] = true;
    pre[node] = clock;
    numcc[node] = cc;
    clock++;
    aux << node << " ";
    dfsTree.push_back(node);
    alreadyVisited++;
    vector<int> adj = getAdjecentNodes(node);
    for (int n : adj) {
        if (!visited[n]) {
            exploreDFS(n, visited, aux);
        }
    }
    pos[node] = Point(node, clock);
    clock++;
}

string Graph::dfs(int start, bool extended) {
    if (type == None) {
        throw invalid_argument("A graph must be loaded before using this operation");
    }
    stringstream aux;
    int i;
    pre = vector<int>(numNodes + 1, -1);
    pos = vector<Point>(numNodes + 1, Point());
    numcc = vector<int>(numNodes + 1, -1);
    dfsTree = vector<int>();
    vector<bool> visited(numNodes + 1, false);
    clock = 1;
    cc = 1;
    alreadyVisited = 0;
    exploreDFS(start, visited, aux);
    while (alreadyVisited < numNodes + 1) {
        for (i = 0; i <= numNodes; i++) {
            if (!visited[i]) break;
        }
        aux << endl << "Extra DFS call:" << endl;
        exploreDFS(i, visited, aux);
    }
    aux << endl;
    if (extended) {
        aux << "DFS Summary" << endl;
        aux << "Node: (numcc, pre, post)" << endl;
        for (int i = 0; i <= numNodes; i++) {
            int v = dfsTree.at(i);
            aux << v << ": (" << numcc[v] << ", " << pre[v] << ", " << pos[v].getPos() << ")" << endl;
        }
    }
    return aux.str();
}

vector<int> Graph::topologicalSort() {
    if (type == None) {
        throw invalid_argument("A graph must be loaded before using this operation");
    }
    if (pos.size() != numNodes + 1) dfs();
    quickSort(pos, 0, pos.size() - 1);
    vector<int> res;
    for (int i = pos.size() - 1; i >= 0; i--) {
        res.push_back(pos[i].getIndex());
    }
    return res;
}

string Graph::shortestPath() {
    if (type == List || type == None) {
        throw invalid_argument("Invalid graph type");
    }
    const int INF = 0x3f3f3f3f;
    stringstream aux;
    vector<int> dist = vector<int>(numNodes + 1, INF);
    dist[0] = 0;
    vector<int> prev = vector<int>(numNodes + 1, -1);
    Heap<GraphNode> queue;
    queue.push(GraphNode(0, 0));
    while (!queue.empty())
    {
        GraphNode node = queue.poll();
        int id = node.getId();
        vector<int> adj = getAdjecentNodes(id);
        for (int n : adj) {
            if (dist[n] > (dist[id] + data[id][n])) {
                dist[n] = (dist[id] + data[id][n]);
                prev[n] = id;
                queue.push(GraphNode(n, dist[n]));
            }
        }
    }
    aux << "Dist:" << endl;
    for (int i = 0; i < dist.size(); i++) {
        aux << i << ": " << dist[i] << endl;
    }
    aux << "Prev:" << endl;
    for (int i = 0; i < prev.size(); i++) {
        aux << i << ": " << prev[i] << endl;
    }
    return aux.str();
}

bool Graph::bipartiteGraph() {
    if (type == None) {
        throw invalid_argument("A graph must be loaded before using this operation");
    }
    vector<int> colors(numNodes + 1, -1);
    colors[0] = 0;
    Queue<int> queue;
    queue.push(0);
    while (!queue.isEmpty())
    {
        int node = queue.poll();
        vector<int> adj = getAdjecentNodes(node);
        for (int n : adj) {
            if (colors[n] == -1) {
                colors[n] = !colors[node];
                queue.push(n);
            }
            else if (colors[n] == colors[node]) {
                return false;
            }
        }
    }
    return true;
}