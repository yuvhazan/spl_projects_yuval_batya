#include "../include/Agent.h"

Agent::Agent() {}

Virus::Virus(int nodeInd) : Agent(), nodeInd(nodeInd) {};

virtual void Virus::act(Session &session) {
    session.enqueueInfected(nodeInd);
    infect(); // TODO
}

virtual *

Agent Virus::clone() {
    return new Virus(*this);
}

ContactTracer::ContactTracer() : Agent() {};

virtual void ContactTracer::act(Session &session) {
}

virtual *Agent ContactTracer::clone() {
    return new ContactTracer(*this);
}




