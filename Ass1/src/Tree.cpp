#include "../include/Tree.h"


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
        clearChildren();

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

    //delete current children
    clearChildren();

    for (auto &child: other.children) {
        children.push_back(child);
        child = nullptr;
    }
    return *this;
}

//destructor
Tree::~Tree() {
    for (Tree *child : children)
        delete (child);
    children.clear();
}

int Tree::getNode() const {
    return node;
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
    int cycleNum = 0;
    Tree *currNode = this;
    while ((cycleNum < currCycle) && currNode->getChildrenSize() != 0) {
        currNode = currNode->getChildren()[0];
        cycleNum++;
    }
    return currNode->getNode();
}

int MaxRankTree::traceTree() {
    queue<Tree *> childrenQueue;
    childrenQueue.push(this);
    int maxDegNode = -1;
    int deg = -1;
    while (!childrenQueue.empty()) {
        Tree *curr = childrenQueue.front();
        childrenQueue.pop();
        if (curr->getChildrenSize() > deg) {
            maxDegNode = curr->getNode();
            deg = curr->getChildrenSize();
        }
        vector<Tree *> childrens = curr->getChildren();

        // push children to queue
        for (Tree *child : childrens) {
            childrenQueue.push(child);
        }
    }
    return maxDegNode;
}

int RootTree::traceTree() {
    return node;
}

void Tree::addChild(const Tree &child) {
    children.push_back(child.clone());
}

void Tree::clearChildren() {
    for (auto child: children)
        delete (child);
    children.clear();
}
