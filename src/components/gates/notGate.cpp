#include "notGate.h"

NotGate::NotGate(unsigned int id) : Component(id) {
    m_type = ComponentType::NOT_GATE;
    m_label = "NOT";
    m_size = {75, 50};
    m_color = {200, 50, 50, 255};
    m_nextColor = m_color;

    m_inputNodes.resize(1);
    m_inputNodes[0].type = NodeType::INPUT;
    
    m_outputNodes.resize(1);
    m_outputNodes[0].type = NodeType::OUTPUT;

    setPosition(m_position);
}

void NotGate::evaluate() {

    LogicState inputState = m_inputNodes[0].incomingConnection 
                            ? m_inputNodes[0].incomingConnection->currentState 
                            : LogicState::LOW;

    m_outputNodes[0].nextState = (inputState == LogicState::LOW) 
                                 ? LogicState::HIGH : LogicState::LOW;
}

void NotGate::commit() {
    m_outputNodes[0].currentState = m_outputNodes[0].nextState;
}