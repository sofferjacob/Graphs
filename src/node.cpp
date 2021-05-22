#include "node.h"

GraphNode::GraphNode(int i, int d) : id(i), distance(d) {}

int GraphNode::getId() {
    return id;
}

void GraphNode::setId(int newId) {
    id = newId;
}

int GraphNode::getDistance() {
    return distance;
}

void GraphNode::setDistance(int d) {
    distance = d;
}

bool GraphNode::operator<(GraphNode& other) {
    return distance < other.distance;
}

bool GraphNode::operator>(GraphNode& other) {
    return distance > other.distance;
}