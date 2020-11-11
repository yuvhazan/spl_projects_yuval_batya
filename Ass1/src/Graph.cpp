//
// Created by spl211 on 07/11/2020.
//
#include "../include/Graph.h"
#include "../include/Session.h"
#include <queue>

using namespace std;

Graph::Graph(std::vector<std::vector<int>> matrix) : edges(matrix), states(matrix.size(), Healthy),
                                                     outputInfectedList() {
}

void Graph::infectNode(int nodeInd) {
    if (states[nodeInd] == Healthy) {
        states[nodeInd] = Carry;
    }
}

bool Graph::isInfected(int nodeInd) {
    return states[nodeInd] == Infected;
}

vector<int> Graph::getNeighborsSorted(int v) {
    vector<int> output;
    for (size_t i(0); i < edges.size(); i++) {
        if (containEdge(v, i)) {
            output.push_back(i);
        }
    }
    return output;
}

Tree *Graph::bfs(Session &session, int rootLabel) {
    Tree *root = Tree::createTree(session, rootLabel);
    queue<Tree *> bfsQueue;
    bfsQueue.push(root);
    vector<bool> visited(edges.size(), false);
    visited[rootLabel] = true;
    while (!bfsQueue.empty()) {
        Tree *curr = bfsQueue.front();
        bfsQueue.pop();
        int currLabel = curr->getNode();
        vector<int> neighbors = getNeighborsSorted(currLabel);
        for (int neighbor: neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                Tree *child = Tree::createTree(session, neighbor);
                curr->addChild(*child);
                delete (child);
            }
        }
        vector<Tree *> allChildren = curr->getChildren();
        for (Tree *child:allChildren) {
            bfsQueue.push(child);
        }
    }
    return root;
}

void Graph::disconnect(int toDisconnect) {
    for (size_t neighbor(0); neighbor < edges.size(); neighbor++) {
        removeEdge(toDisconnect, neighbor);
        removeEdge(neighbor, toDisconnect);
    }
}

NodeState Graph::getState(int v) {
    //returns the state of a node
    return states[v];
}

void Graph::setState(int v, NodeState state) {
    states[v] = state;
}

int Graph::getMinHealthy(int v) {
    // returns the min neighbor of v who is not carry or infected
    for (size_t i(0); i < edges.size(); i++)
        if (containEdge(v, i) && states[i] == Healthy)
            return i;
    return -1;
}

bool Graph::isSatisfied() {
    // return true if termination conditions are satisfied
    for (size_t i(0); i < edges.size(); i++) {
        for (size_t j(i + 1); j < edges.size(); j++) {
            if (containEdge(i, j)) {
                if ((states[i] != states[j]) || states[i] == Carry)
                    // check if there is an edge of two different "states"
                    // check if any state of a node is nor Healthy or Infected
                    return false;
            }
        }
    }
    return true;
}

vector<vector<int>> Graph::getEdges() {
    // use only for writing to output.json
    return edges;
}

vector<int> Graph::getInfected() {
    // returns add infected nodes
    // will be called in the end of all circles
    // used to write to output.json
    sort(outputInfectedList.begin(), outputInfectedList.end());
    return outputInfectedList;
}

bool Graph::containEdge(int v1, int v2) {
    return edges[v1][v2] == 1;
}

void Graph::removeEdge(int v1, int v2) {
    edges[v1][v2] = 0;
}

void Graph::addToInfectedOutput(int v) {
    outputInfectedList.push_back(v);
}
