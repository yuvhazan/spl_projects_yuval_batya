#include "../include/Session.h"
#include <iostream>
#include <fstream>

using json = nlohmann::json;
using namespace std;

Session::Session(const std::string &path) : infected(), g(vector<vector<int >>()), currCycle(0) {
    ifstream i(path);
    json j;
    j << i;
    for (const auto &agent:j["agents"]) {
        string agentType(agent[0]);

        if (agentType == "V") {
            agents.push_back(new Virus(agent[1]));
        } else if (agentType == "C")
            agents.push_back(new ContactTracer());
    }

    g = Graph(j["graph"]);

    string type = j["tree"];
    if (type == "M") {
        treeType = MaxRank;
    } else if (type == "R") {
        treeType = Root;
    } else if (type == "C") {
        treeType = Cycle;
    }
}

//copy constructor
Session::Session(const Session &other) :
        g(other.g), infected(other.infected), treeType(other.treeType), currCycle(other.currCycle) {
    for (const auto agent: other.agents) {
        agents.push_back(agent->clone());
    }
}

//copy assignment operator
const Session &Session::operator=(const Session &other) {
    if (this != &other) {
        g = other.g;
        infected = other.infected;
        treeType = other.treeType;
        currCycle = other.currCycle;

        //delete current agents
        for (auto agent: agents)
            delete (agent);
        agents.clear();

        //copy other's agents
        for (const auto agent: other.agents) {
            agents.push_back(agent->clone());
        }
    }
    return *this;
}

//move constructor
Session::Session(Session &&other)
        : g(other.g), infected(other.infected), treeType(other.treeType), agents(), currCycle(other.currCycle) {
    for (auto &agent:other.agents) {
        agents.push_back(agent);
        agent = nullptr;
    }
}

//move assignment operator
const Session &Session::operator=(Session &&other) {
    g = other.g;
    infected = other.infected;
    treeType = other.treeType;
    currCycle = other.currCycle;

    //delete current agents
    for (auto agent: agents)
        delete (agent);
    agents.clear();

    for (auto &agent:other.agents) {
        agents.push_back(agent);
        agent = nullptr;
    }
    return *this;
}


//destructor
Session::~Session() {
    for (auto agent : agents) {
        delete (agent);
    }
    agents.clear();
}

void Session::simulate() {
    cout << "simulate" << endl;
    Tree *root = g.bfs(*this, 0);
    cout << "tree type is " << treeType << endl;
    cout << "pleas it will be one : " << root->traceTree() << "!!!!!!!!!" << endl;
    cout << "done bfs for 0!!!!" << endl;
}

void Session::addAgent(const Agent &agent) {
    agents.push_back(agent.clone());

}

void Session::setGraph(const Graph &graph) {
    g = graph;
}

void Session::enqueueInfected(int toEnqueue) {
    infected.push(toEnqueue);
}

int Session::getCurrCycle() const {
    return currCycle;
}

int Session::dequeueInfected() {
    int output = infected.front();
    infected.pop();
    return output;
}

TreeType Session::getTreeType() const {
    return treeType;
}






