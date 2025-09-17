#include "outLight.h"

OutLight::OutLight(unsigned int id) : Component(id) {
    m_type = ComponentType::OUTLIGHT;
    m_label = "OUT";
    m_size = {50, 50};
    m_color = GRAY;
    m_nextColor = GRAY;

    m_inputNodes.resize(1);
    m_inputNodes[0].type = NodeType::INPUT;

    setPosition(m_position);
}

void OutLight::evaluate() {

    LogicState inputState = m_inputNodes[0].incomingConnection 
                            ? m_inputNodes[0].incomingConnection->currentState 
                            : LogicState::LOW;
                            
    m_nextColor = (inputState == LogicState::HIGH) ? YELLOW : GRAY;
}

void OutLight::commit() {
    m_color = m_nextColor;
    m_label = (m_color.r == YELLOW.r) ? "1" : "0";
}