#ifndef _GRAPH_H
#define _GRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include "point.h"

enum GraphType { List, Matrix, Weighted, None };

class Graph {
private:
    int numNodes;
    int numEdges;
    GraphType type;
    std::vector<int>* data;
    //std::vector<vector<int> > matrix;
    void split(std::string line, std::vector<int>& res);
    std::vector<int> getAdjecentNodes(int);
    std::string printAdjList();
    std::string printMatrix();
    std::string printWeighted();
    // DFS AUX
    int clock;
    int cc;
    int alreadyVisited;
    std::vector<int> pre;
    std::vector<Point> pos;
    std::vector<int> dfsTree;
    std::vector<int> numcc;
    void exploreDFS(int, std::vector<bool>&, std::stringstream&);

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
    Graph(std::string, GraphType);
    // Filename constructor
    // Takes cin as the first argument for use with stdin redirection.
    // If the second argument is
    // set to true the graph is stored as an adjecency list,
    // else it's stored as an adj. matrix
    Graph(std::istream&, GraphType);
    // Loads the graph as an adj.list
    void loadGraphList(std::istream& input);
    // Loads the graph as an adj.matrix
    void loadGraphMatrix(std::istream& input);
    // Loads a weighted graph
    void loadWeightedGraph(std::istream& input);
    // Returns a string containing the graph elements
    std::string print();
    std::string dfs(int start = 0, bool extended = false);
    std::string bfs(int start = 0, int finish = -1);
    std::vector<int> topologicalSort();
    std::string shortestPath();
    bool bipartiteGraph();
};

#endif