#include "../include/Tree.h"
#include <queue>
#include "../include/Session.h"

using namespace std;

Tree *Tree::createTree(const Session &session, int rootLabel) {
    int type = (int) session.getTreeType();
    switch (type) {
        case Cycle:
            return new CycleTree(rootLabel, session.getCurrCycle());
        case MaxRank:
            return new MaxRankTree(rootLabel);
        case Root:
            return new RootTree(rootLabel);
        default:
            return nullptr;
    }
}
//constructor

Tree::Tree(int rootLabel) : node(rootLabel), children() {
}

//copy constructor
Tree::Tree(const Tree &other) : node(other.node), children() {
    for (const auto &child: other.children) {
        children.push_back(child->clone());
    }
}

//copy assignment operator
const Tree &Tree::operator=(const Tree &other) {
    if (this != &other) {
        node = other.node;

        //delete current children
        for (auto child: children)
            delete (child);
        children.clear();

        //copy other's children
        for (const auto child: other.children) {
            children.push_back(child->clone());
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
Tree::~Tree() {
    for (auto child : children) {
        delete (child);
    }
    children.clear();
}


Tree *CycleTree::clone() const {
    return new CycleTree(*this);
}


Tree *MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}

Tree *RootTree::clone() const {
    return new RootTree(*this);
}

CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {}

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}

RootTree::RootTree(int rootLabel) : Tree(rootLabel) {}

int CycleTree::traceTree() {
    return 0;
}

int MaxRankTree::traceTree() {
    return 0;
}

int RootTree::traceTree() {
    return 0;
}

void Tree::addChild(const Tree &child) {
    children.push_back(child.clone());
}