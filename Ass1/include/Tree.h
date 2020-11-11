#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include <iostream>

class Session;
class Tree {
public:
    Tree(int rootLabel);

    //copy constructor
    Tree(const Tree &other);

    //copy assignment operator
    const Tree &operator=(const Tree &other);

    //move constructor
    Tree(Tree &&other);

    //move assignment operator
    const Tree &operator=(Tree &&other);

    //destructor
    virtual ~Tree();

    void addChild(const Tree &child);

    virtual Tree *clone() const = 0;


    static Tree *createTree(const Session &session, int rootLabel);

    virtual int traceTree() = 0;

    int getNode() const;

    int getChildrenSize() {
        return children.size();
    }

    std:: vector<Tree*> getChildren() const{
        return children;
    }

protected:
    int node;
    std::vector<Tree *> children;
};

class CycleTree : public Tree {
public:
    CycleTree(int rootLabel, int currCycle);

    virtual int traceTree();

    virtual Tree *clone() const;

private:
    int currCycle;
};

class MaxRankTree : public Tree {
public:
    MaxRankTree(int rootLabel);

    virtual int traceTree();

    virtual Tree *clone() const;
};

class RootTree : public Tree {
public:
    RootTree(int rootLabel);

    virtual int traceTree();

    virtual Tree *clone() const;
};

#endif
