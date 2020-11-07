#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>

class Tree;

class Session;

class Graph {
public:
    Graph(std::vector<std::vector<int>> matrix);

    void infectNode(int nodeInd);

    bool isInfected(int nodeInd);

    Tree *bfs(Session &session);

private:
    std::vector<std::vector<int>> edges;
};

#endif
