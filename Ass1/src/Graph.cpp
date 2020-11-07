//
// Created by spl211 on 07/11/2020.
//
#include "../include/Graph.h"
#include "../include/Session.h"
#include "../include/Tree.h"
#include <queue>

using namespace std;

Graph::Graph(std::vector<std::vector<int>> matrix) : edges(matrix) {
}

void Graph::infectNode(int nodeInd) {}

bool Graph::isInfected(int nodeInd) {
    return true;
}

Tree *Graph::bfs(Session &session) {
    vector<bool> visited(edges.size(),false);
    queue<Tree *> bfsQueue;
    int from = session.dequeueInfected();
    Tree *root = Tree::createTree(session, from);
    Tree* curr;
    bfsQueue.push(root);
    while (!bfsQueue.empty()) {
        curr=bfsQueue.front();
        bfsQueue.pop();
    }
    return root;
}
