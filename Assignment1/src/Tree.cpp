#include "../include/Tree.h"

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
