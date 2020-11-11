//
// Created by spl211 on 07/11/2020.
//
#include "../include/Graph.h"
#include "../include/Session.h"
#include <queue>

using namespace std;

Graph::Graph(std::vector<std::vector<int>> matrix) : edges(matrix), states(matrix.size(), Healthy) {
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
        if (edges[v][i] == 1) {
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
        edges[toDisconnect][neighbor] = 0;
        edges[neighbor][toDisconnect] = 0;
    }
}

NodeState Graph::getState(int v) {
    return states[v];
}

void Graph::setState(int v, NodeState state) {
    states[v] = state;
}

int Graph::getMinHealthy(int v) {
    for (size_t i(0); i < edges.size(); i++)
        if (edges[v][i] == 1 && states[i] == Healthy)
            return i;
    return -1;
}

bool Graph::isSatisfied() {
    for (size_t i(0); i < edges.size(); i++) {
        for (size_t j(i + 1); j < edges.size(); j++) {
            if (edges[i][j] == 1) {
                if (states[i] != states[j] || states[i] == Carry)
                    return false;
            }
        }
    }
    return true;
}

vector<vector<int>> Graph::getEdges() {
    return edges;
}

vector<int> Graph::getInfected() {
    vector<int> output;
    for (size_t i(0); i < edges.size(); i++)
        if (this->isInfected(i))
            output.push_back(i);
    return output;
}
