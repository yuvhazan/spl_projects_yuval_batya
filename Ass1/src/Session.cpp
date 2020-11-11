#include "../include/Session.h"

using json = nlohmann::json;
using namespace std;

Session::Session(const std::string &path) : g(vector<vector<int >>()), currCycle(0) {
    initFieldsFromJson(path);
}

void Session::initFieldsFromJson(const std::string &path) {
    //read json
    ifstream i(path);
    json j;
    i >> j;

    //graph init
    g = Graph(j["graph"]);

    //agents init
    for (const auto &agent:j["agents"]) {
        string agentType(agent[0]);
        if (agentType == "V") {
            int vertex(agent[1]);
            agents.push_back(new Virus(vertex));
            g.setState(vertex, Carry);
        } else if (agentType == "C")
            agents.push_back(new ContactTracer());
    }

    //treeType init
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
        g(other.g), treeType(other.treeType), infected(other.infected), currCycle(other.currCycle) {
    for (const auto agent: other.agents) {
        agents.push_back(agent->clone());
    }
}

//copy assignment operator
const Session &Session::operator=(const Session &other) {
    if (this != &other) {
        // copy values of other
        g = other.g;
        treeType = other.treeType;
        infected = other.infected;
        currCycle = other.currCycle;

        //delete current agents
        clearAgents();

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
    // copy values of other
    g = other.g;
    treeType = other.treeType;
    infected = other.infected;
    currCycle = other.currCycle;


    //delete current agents
    clearAgents();

    for (auto &agent:other.agents) {
        agents.push_back(agent);
        agent = nullptr;
    }
    return *this;
}


//destructor
Session::~Session() {
    for (Agent* agent : agents) {
        delete (agent);
    }
    agents.clear();
}

void Session::simulate() {
    while (!g.isSatisfied())
        circle();
    this->writeToJson();
}

void Session::circle() {
    size_t sizeOfCycle(agents.size());
    for (size_t i(0); i < sizeOfCycle; i++)
        agents[i]->act(*this);
    currCycle++;
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

void Session::writeToJson() {
    json j;
    j["graph"] = g.getEdges();
    j["infected"] = g.getInfected();
    ofstream o("output.json");
    o << j;
}

void Session::clearAgents() {
    for (Agent *agent: agents)
        delete (agent);
    agents.clear();
}






