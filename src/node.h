#ifndef _GRAPH_NODE_H
#define _GRAPH_NODE_H

class GraphNode {
public:
    GraphNode(int i, int d);
    int getId();
    void setId(int);
    int getDistance();
    void setDistance(int);

    bool operator >(GraphNode&);
    bool operator <(GraphNode&);
private:
    int id;
    int distance;
};

#endif