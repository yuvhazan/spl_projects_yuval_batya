//
// Created by spl211 on 07/11/2020.
//
#include "../include/Graph.h"
#include "../include/Session.h"
#include "../include/Tree.h"
#include <queue>
#include <iostream>

using namespace std;

Graph::Graph(std::vector<std::vector<int>> matrix) : edges(matrix) {
}

void Graph::infectNode(int nodeInd) {}

bool Graph::isInfected(int nodeInd) {
    return true;
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
                bfsQueue.push(child);
            }
        }
    }
    return root;
}
