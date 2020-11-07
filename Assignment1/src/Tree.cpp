#include "../include/Tree.h"
#include <queue>
#include "../include/Session.h"

using namespace std;

Tree *Tree::createTree(const Session &session, int rootLabel) {
    swith(session.getTreeType())
    {
        case Cycle:
            return new CycleTree(rootLabel, session.getCurrCycle());
        case MaxRank:
            return new MaxRankTree(rootLable);
        case Root:
            return new RootTree(rootLable);
        default:
            return nullptr;
    }
}

void Tree::createBFS(const Session &session) {
    Graph g = session.getGraph();
    vec edges = g.getEdges();
    queue<int> bfsQueue;
    vector<bool> visited = new vector[]


}


