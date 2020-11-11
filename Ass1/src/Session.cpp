#include "../include/Session.h"
#include <iostream>
#include <fstream>

using json = nlohmann::json;
using namespace std;

Session::Session(const std::string &path) :g(vector<vector<int >>()) , currCycle(0) {
    ifstream i(path);
    json j;
    i >> j;

    g = Graph(j["graph"]);

    for (const auto &agent:j["agents"]) {
        string agentType(agent[0]);
        if (agentType == "V") {
            int vertex(agent[1]);
            agents.push_back(new Virus(vertex));
            g.setState(vertex, Carry);
        } else if (agentType == "C")
            agents.push_back(new ContactTracer());
    }


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
        g(other.g), treeType(other.treeType), infected(other.infected) , currCycle(other.currCycle) {
    for (const auto agent: other.agents) {
        agents.push_back(agent->clone());
    }
}

//copy assignment operator
const Session &Session::operator=(const Session &other) {
    if (this != &other) {
        g = other.g;
        treeType = other.treeType;
        infected = other.infected;
        currCycle = other.currCycle;

        //delete current agents
        for (Agent* agent: agents)
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
        : g(other.g), treeType(other.treeType), agents(), infected(other.infected), currCycle(other.currCycle) {
    for (auto &agent:other.agents) {
        agents.push_back(agent);
        agent = nullptr;
    }
}

//move assignment operator
const Session &Session::operator=(Session &&other) {
    g = other.g;
    treeType = other.treeType;
    infected = other.infected;
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
    while (!g.isSatisfied()) {
        size_t sizeOfCycle(agents.size());
        for (size_t i(0); i < sizeOfCycle; i++)
            agents[i]->act(*this);
        currCycle++;
    }
    for (int i(0); i < g.getSize(); i++) {
        cout << "vertex: " << i << " , state: " << g.getState(i) << endl;
    }
    cout << "cycle: " << currCycle << endl;
    cout << "graph: " << endl;
    g.print();
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

Graph Session::getGraph() {
    return g;
}

bool Session::infectedIsEmpty() {
    return infected.empty();
}






