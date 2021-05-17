#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>
#include <set>
#include "linear/queue.h"
#include "linear/stack.h"

using namespace std;

class Graph {
private:
    int numNodes;
    int numEdges;
    bool isAdjList;
    std::vector<int>* data;
    //std::vector<vector<int> > matrix;
    void split(std::string line, std::vector<int>& res);
    vector<int> getAdjecentNodes(int);
    string printAdjList();
    string printMatrix();

public:
    // Default constructor
    // A loadGraph must be called before
    // using the object
    Graph();
    // Filename constructor
    // Takes the filename containing the graph
    // as the first argument. If the second argument is
    // set to true the graph is stored as an adjecency list,
    // else it's stored as an adj. matrix
    Graph(std::string, bool);
    // Filename constructor
    // Takes cin as the first argument for use with stdin redirection.
    // If the second argument is
    // set to true the graph is stored as an adjecency list,
    // else it's stored as an adj. matrix
    Graph(std::istream&, bool);
    // Loads the graph as an adj.list
    void loadGraphList(std::istream& input);
    // Loads the graph as an adj.matrix
    void loadGraphMatrix(std::istream& input);
    // Returns a string containing the graph elements
    string print();
    string dfs(int start = 0, int finish = -1);
    string bfs(int start = 0, int finish = -1);
};

Graph::Graph() {}

Graph::Graph(std::istream& input, bool list) {
    if (list) {
        loadGraphList(input);
    }
    else {
        loadGraphMatrix(input);
    }
}

Graph::Graph(std::string filename, bool list) {
    ifstream file(filename);
    if (!file.good()) {
        file.close();
        throw invalid_argument("File not found");
    }
    if (list) loadGraphList(file);
    else loadGraphMatrix(file);
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
            isAdjList = true;
            i++;
            continue;
        }
        vector<int> res;
        split(line, res);
        int u = res[0];
        int v = res[1];
        data[u].push_back(v);
        data[v].push_back(u);
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
            isAdjList = false;
            cout << "rows: " << data->size() << endl;
            cout << "columns: " << data[0].size() << endl;
            i++;
            continue;
        }
        vector<int> res;
        split(line, res);
        int u = res[0];
        int v = res[1];
        data[u].at(v) = 1;
        data[v].at(u) = 1;
        i++;
    }
    // for (int j = 0; j < matrix.size(); j++) {
    //     for (int k = 0; k < matrix[j].size(); k++) {
    //         cout << matrix[j][k] << " ";
    //     }
    //     cout << endl;
    // }
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
    if (isAdjList) return printAdjList();
    return printMatrix();
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
    if (isAdjList) {
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

string Graph::dfs(int start, int finish) {
    stringstream aux;
    if (finish == -1) {
        finish = numNodes;
    }
    Stack<int> stack;
    set<int, greater<int> > seen;
    stack.push(start);
    while (!stack.isEmpty())
    {
        int node = stack.pop();
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
                stack.push(n);
            }
        }
    }
    aux << "Visited nodes:" << endl;
    for (set<int>::iterator it = seen.begin(); it != seen.end(); ++it) {
        aux << *it << endl;
    }
    return aux.str();
}
