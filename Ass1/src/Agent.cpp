#include "../include/Agent.h"

Agent::Agent() {}

Virus::Virus(int nodeInd) : Agent(), nodeInd(nodeInd) {};

void Virus::act(Session &session) {
//    session.enqueueInfected(nodeInd);
//    infect(); // TODO
}


Agent *Virus::clone()const {
    return new Virus(*this);
}

ContactTracer::ContactTracer() : Agent() {};

void ContactTracer::act(Session &session) {
}

Agent *ContactTracer::clone()const {
    return new ContactTracer(*this);
}




