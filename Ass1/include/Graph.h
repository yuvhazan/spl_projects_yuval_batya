#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>

class Tree;

class Session;

using namespace std;

enum NodeState {
    // NodeState represents the condition of a node
    // Healthy = "white" , Carry="yellow" Infected="red"
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

    NodeState getState(int v);

    void setState(int v, NodeState state);

    int getMinHealthy(int v);

    bool isSatisfied();

    vector<vector<int>> getEdges();

    vector<int> getInfected();

    bool containEdge(int v1, int v2);

    void removeEdge(int v1, int v2);

    void addToInfectedOutput(int v);

private:
    vector<std::vector<int>> edges;

    vector<int> getNeighborsSorted(int v);

    std::vector<NodeState> states;

    vector<int> outputInfectedList;
};

#endif
