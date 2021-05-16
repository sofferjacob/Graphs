#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Graph {
private:
    int numNodes;
    int numEdges;
    std::vector<int>* adjList;
    std::vector<vector<int> > matrix;
    void split(std::string line, std::vector<int>& res);

public:
    Graph();
    Graph(std::istream&, bool);
    void loadGraphList(std::istream& input);
    void loadGraphMatrix(std::istream& input);
    string printAdjList();
    string printMatrix();
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

void Graph::loadGraphList(std::istream& input) {
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
            adjList = new vector<int>[numNodes + 1];
            i++;
            continue;
        }
        vector<int> res;
        split(line, res);
        int u = res[0];
        int v = res[1];
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        i++;
    }
}

void Graph::loadGraphMatrix(std::istream& input) {
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
            matrix = vector<vector<int> >(numNodes + 1, vector<int>(numNodes + 1, 0));
            cout << "rows: " << matrix.size() << endl;
            cout << "columns: " << matrix[0].size() << endl;
            i++;
            continue;
        }
        vector<int> res;
        split(line, res);
        int u = res[0];
        int v = res[1];
        matrix[u].at(v) = 1;
        matrix[v].at(u) = 1;
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

string Graph::printAdjList() {
    stringstream aux;
    for (int i = 0; i < numNodes; i++) {
        aux << "vertex "
            << i << " :";
        for (int j = 0; j < adjList[i].size(); j++) {
            aux << " " << adjList[i][j];
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
            if (matrix[i].at(j) == 0) continue;
            aux << "  " << j << "," << endl;
        }
        aux << "]," << endl;
    }
    return aux.str();
}

