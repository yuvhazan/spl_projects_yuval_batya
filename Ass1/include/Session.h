#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <queue>
#include <string>
#include "Graph.h"
#include "json.hpp"
#include "Agent.h"
#include "Tree.h"

class Agent;

enum TreeType {
    Cycle,
    MaxRank,
    Root
};



class Session {
public:

    Session(const std::string &path);

    //coy constructor
    Session(const Session &other);

    //copy assignment operator
    const Session &operator=(const Session &other);

    //move constructor
    Session(Session &&other);

    //move assignment operator
    const Session &operator=(Session &&other);

    //destructor
    virtual ~Session();

    void simulate();

    void addAgent(const Agent &agent);

    void setGraph(const Graph &graph);

    void enqueueInfected(int toEnqueue);

    int dequeueInfected();

    TreeType getTreeType() const;

    int getCurrCycle() const;

    Graph getGraph();

    bool infectedIsEmpty();


private:
    Graph g;
    TreeType treeType;
    std::vector<Agent *> agents;
    std::queue<int> infected;

    int currCycle;
};

#endif
