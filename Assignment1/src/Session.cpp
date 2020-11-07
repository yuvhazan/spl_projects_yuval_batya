#include "../include/Session.h"
#include <iostream>
#include <fstream>

using json = nlohmann::json;
using namespace std;
Session ::Session(const std::string &path): g(vector<vector<int>>()) {
    ifstream i(path);
    json j;
    j << i;
    for (auto &agent:j["agents"]) {
        switch (agent[0]) {
            case 'V':
                agents.push_back(new Virus(agent[1]));
            case 'C':
                agents.push_back(new ContactTracer());
        }
    }
    g = Graph(j[graph]);
    switch (j["tree"]) {
        case 'M':
            treeType = MaxRank;
        case 'R':
            treeType = Root;
        case 'C':
            treeType = Cycle;
    }
}
void Session::simulate() {
    cout<<"simulate"<< endl;
}
void Session::addAgent(const Agent &agent) {
    Agent* toPush = new Agent(agent);
    agents.push_back(toPush);
}


}
