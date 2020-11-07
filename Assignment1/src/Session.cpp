#include "../include/Session.h"
#include <iostream>
#include <fstream>

using json = nlohmann::json;
using namespace std;

Session::Session(const std::string &path) : infected(), g(vector < vector < int >> ()) {
    ifstream i(path);
    json j;
    j << i;
    for (const auto &agent:j["agents"]) {
        std::string agentType(agent[0]);
//        switch (agent[0]) {
//            case "V":
//                agents.push_back(new Virus(agent[1]));
//                break;
//            case "C":
//                agents.push_back(new ContactTracer());
//                break;
//            default:
//                cout<<"Error"<<endl;
//                break;
//        }
    }
    g = Graph(j["graph"]);
//    switch (j["tree"]) {
//        case 'M':
//            treeType = MaxRank;
//            break;
//        case 'R':
//            treeType = Root;
//            break;
//        case 'C':
//            treeType = Cycle;
//            break;
//        default :
//            cout<<"error"<<endl;
//            break;
//    }
}

//copy constructor
Session::Session(const Session &other) :
        g(other.g), infected(other.infected), treeType(other.treeType), agents() {
    for (const auto agent: other.agents) {
        agents.push_back(agent.clone());
    }
}

//copy assignment operator
const Session &Session::operator=(const Session &other) {
    if (this != &other) {
        g = other.g;
        infected = other.infected;
        treeType = other.treeType;

        //delete current agents
        for (auto agent: agents)
            delete (agent);
        agents.clear();

        //copy other's agents
        for (const auto agent: other.agents) {
            agents.push_back(agent.clone());
        }
    }
    return *this;
}

//move constructor
Session::Session(Session &&other)
        : g(other.g), infected(other.infected), treeType(other.treeType), agents() {
    for (auto &agent:other.agents) {
        agents.push_back(agent);
        agent = nullptr;
    }
}

const Session &session::operator=(Session &&other) {
    g = other.g;
    infected = other.infected;
    treeType = other.treeType;

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
virtual Session::~Session() {
    for (auto agent : agents) {
        delete (agent);
    }
    agents.clear();
}

void Session::simulate() {
    cout << "simulate" << endl;
}

void Session::addAgent(const Agent &agent) {
    agents.push_back(agent.clone())

}

void Session::setGraph(const Graph &graph) {
    g = graph;
}

void Session:: enqueueInfected(int toEnqueue){
    infected.push(toEnqueue);
}






