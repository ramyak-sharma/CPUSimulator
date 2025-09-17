#include "components/gates/notGate.h"
#include <iostream>

void NotGate::evaluate() {
    if(m_inputNodes[0]->currentState == LogicState::LOW) 
        m_outputNodes[0]->nextState = LogicState::HIGH;
    else 
        m_outputNodes[0]->nextState = LogicState::LOW;
}

void NotGate::commit() {
    m_outputNodes[0]->currentState = m_outputNodes[0]->nextState;
}

NotGate::NotGate(unsigned int id)
    : Component(id)
{
    m_inputNodes.push_back(std::make_shared<Node>());
    m_outputNodes.push_back(std::make_shared<Node>());

    m_type = ComponentType::NOT_GATE;

    m_size = {50, 25};
    m_color = RED;
    m_label = "NOT";

    m_inputNodes[0]->type = NodeType::INPUT;
    m_inputNodes[0]->owner = id;

    m_outputNodes[0]->type = NodeType::OUTPUT;
    m_outputNodes[0]->owner = id;

}

void NotGate::display() const{
    std::cout << "\nNOT GATE, component id: " << m_id << "\n";
}