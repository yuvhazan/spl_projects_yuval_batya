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

//constructor

Tree::Tree(int rootLabel) : node(rootLabel), children() {
}

//copy constructor
Tree::Tree(const Tree &other) : node(other.node), children() {
    for (const auto &child: other.children) {
        children.push_back(child.clone());
    }
}

//copy assignment operator
const Tree &Tree::operator=(const Tree &other) {
    if (this != other) {
        node = other.node;

        //delete current children
        for (auto child: children)
            delete (child);
        children.clear();

        //copy other's children
        for (const auto child: other.children) {
            children.push_back(child.clone());
        }
    }
    return *this;
}

//move constructor
Tree::Tree(Tree &&other) : node(other.node) {
    for (auto &child:other.children) {
        children.push_back(child);
        child = nullptr;
    }
}

const Tree &Tree::operator=(Tree &&other) {
    node = other.node;

    //delete current agents
    for (auto child: children)
        delete (child);
    children.clear();

    for (auto &child: other.children) {
        children.push_back(child);
        child = nullptr;
    }
    return *this;
}

//destructor
virtual Tree::~Tree() {
    for (auto child : children) {
        delete (child);
    }
    children.clear();
}


virtual *

Tree CycleTree::clone() {
    return new CycleTree(*this);
}

virtual *

Tree MaxRankTree::clone() {
    return new MaxRankTree(*this);
}

virtual *

Tree RootTree::clone() {
    return new RootTree(*this);
}
