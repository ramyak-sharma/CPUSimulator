#include "components/gates/andGate.h"
#include <iostream>

void AndGate::evaluate() {
    LogicState result = LogicState::HIGH;
    if (m_inputNodes[0]->currentState == LogicState::LOW || m_inputNodes[1]->currentState == LogicState::LOW) {
        result = LogicState::LOW;
    }
    m_outputNodes[0]->nextState = result;
}

void AndGate::commit() {
    m_outputNodes[0]->currentState = m_outputNodes[0]->nextState;
}

AndGate::AndGate(unsigned int id)
    : Component(id)
{
    m_inputNodes.push_back(std::make_shared<Node>());
    m_inputNodes.push_back(std::make_shared<Node>());
    m_outputNodes.push_back(std::make_shared<Node>());

    m_type = ComponentType::AND_GATE;

    m_size = {75, 50};
    m_color = BLUE;
    m_label = "AND";

    m_inputNodes[0]->type = NodeType::INPUT;
    m_inputNodes[0]->owner = id;

    m_inputNodes[1]->type = NodeType::INPUT;
    m_inputNodes[1]->owner = id;

    m_outputNodes[0]->type = NodeType::OUTPUT;
    m_outputNodes[0]->owner = id;
}


void AndGate::display() const{
    std::cout << "\nAND GATE, component id: " << m_id << "\n";  
}