#include "components/gates/andGate.h"
#include <iostream>

void AndGate::update() {
    LogicState result = LogicState::HIGH;
    if (m_input1.state == LogicState::LOW || m_input2.state == LogicState::LOW) {
        result = LogicState::LOW;
    }
    m_output.state = result;
}

AndGate::AndGate(unsigned int id)
    : Component(id)
{
    m_type = ComponentType::AND_GATE;
   
    m_input1.type = NodeType::INPUT;
    m_input1.owner = this; 

    m_input2.type = NodeType::INPUT;
    m_input2.owner = this; 

    m_output.type = NodeType::OUTPUT;
    m_output.owner = this;
}


void AndGate::display() const{
    std::cout << "\nAND GATE, component id: " << m_id << "\n";
    std::cout << "input 1: " << m_input1 << "\ninput 2: " << m_input2 << "\noutput: " << m_output << "\n";    
}