#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);
    
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    Tree* bfs (const Session &session){
        node to begin=session.dequeue;
        Tree *output = Tree::createTree(session , tobegin);
        tree add child;
    }
private:
    std::vector<std::vector<int>> edges;
};

#endif
