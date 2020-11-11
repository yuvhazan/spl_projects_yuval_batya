#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>

class Tree;

class Session;

using namespace std;

enum NodeState {
    Healthy,
    Carry,
    Infected
};


class Graph {
public:
    Graph(std::vector<std::vector<int>> matrix);

    void infectNode(int nodeInd);

    bool isInfected(int nodeInd);

    Tree *bfs(Session &session, int rootLabel);

    void disconnect(int toDisconnect);

    int getSize();

    NodeState getState(int v);

    void setState(int v, NodeState state);

    int getMinHealthy(int v);

    bool isSatisfied();

    void print();

private:
    vector<std::vector<int>> edges;

    vector<int> getNeighborsSorted(int v);

    std::vector<NodeState> states;
};

#endif
