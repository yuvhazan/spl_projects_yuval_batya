#include "../include/Agent.h"

Agent::Agent() {}

Virus::Virus(int nodeInd) : Agent(), nodeInd(nodeInd) {};

void Virus::act(Session &session) {
    Graph currGraph = session.getGraph();
    if (!currGraph.isInfected(nodeInd)) {
        currGraph.setState(nodeInd, Infected);
        session.enqueueInfected(nodeInd);
    }
    int nodeToInfect = currGraph.getMinHealthy(nodeInd);
    if (nodeToInfect != -1) {
        currGraph.infectNode(nodeToInfect);
        session.addAgent(Virus(nodeToInfect));
    }
    session.setGraph(currGraph);
}


Agent *Virus::clone() const {
    return new Virus(*this);
}

ContactTracer::ContactTracer() : Agent() {};

void ContactTracer::act(Session &session) {
    if (session.infectedIsEmpty())
        return;

    int rootOfBFS = session.dequeueInfected();
    Graph currGraph = session.getGraph();
    Tree *root = currGraph.bfs(session, rootOfBFS);
    int toDisconnect = root->traceTree();
    delete (root);
    currGraph.disconnect(toDisconnect);
    session.setGraph(currGraph);
}

Agent *ContactTracer::clone() const {
    return new ContactTracer(*this);
}




