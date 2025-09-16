#include "components/gates/notGate.h"
#include <iostream>

void NotGate::update() {
    if(m_input.state == LogicState::LOW) 
        m_output.state = LogicState::HIGH;
    else 
        m_output.state = LogicState::LOW;
}

NotGate::NotGate(unsigned int id)
    : Component(id)
{
    m_type = ComponentType::NOT_GATE;

    m_input.type = NodeType::INPUT;
    m_input.owner = this; 

    m_output.type = NodeType::OUTPUT;
    m_output.owner = this;

}

void NotGate::display() const{
    std::cout << "\nNOT GATE, component id: " << m_id << "\n";
    std::cout << "input: " << m_input << "\noutput: " << m_output << "\n";    
}