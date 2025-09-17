#include "inLight.h"

InLight::InLight(unsigned int id) : Component(id) {
    m_type = ComponentType::INLIGHT;
    m_label = "IN";
    m_size = {50, 50};
    m_color = GRAY;
    m_nextColor = GRAY;
    
    m_outputNodes.resize(1);
    m_outputNodes[0].type = NodeType::OUTPUT;
    
    setPosition(m_position); 
}

void InLight::evaluate() {
    m_outputNodes[0].nextState = m_manualState;
}

void InLight::commit() {
    m_outputNodes[0].currentState = m_outputNodes[0].nextState;
    m_color = (m_outputNodes[0].currentState == LogicState::HIGH) ? RED : GRAY;
    m_label = (m_outputNodes[0].currentState == LogicState::HIGH) ? "1" : "0";
}

void InLight::toggle() {
    m_manualState = (m_manualState == LogicState::LOW) ? LogicState::HIGH : LogicState::LOW;
}