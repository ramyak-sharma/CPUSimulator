#include "andGate.h"

AndGate::AndGate(unsigned int id) : Component(id) {
    m_type = ComponentType::AND_GATE;
    m_label = "AND";
    m_size = {75, 50};
    m_color = BLUE;
    m_nextColor = BLUE;

    m_inputNodes.resize(2);
    m_inputNodes[0].type = NodeType::INPUT;
    m_inputNodes[1].type = NodeType::INPUT;
    
    m_outputNodes.resize(1);
    m_outputNodes[0].type = NodeType::OUTPUT;

    setPosition(m_position);
}

void AndGate::evaluate() {

    LogicState stateA = m_inputNodes[0].incomingConnection 
                        ? m_inputNodes[0].incomingConnection->currentState 
                        : LogicState::LOW;

    LogicState stateB = m_inputNodes[1].incomingConnection 
                        ? m_inputNodes[1].incomingConnection->currentState 
                        : LogicState::LOW;

    m_outputNodes[0].nextState = (stateA == LogicState::HIGH && stateB == LogicState::HIGH) 
                                 ? LogicState::HIGH : LogicState::LOW;
}

void AndGate::commit() {
    m_outputNodes[0].currentState = m_outputNodes[0].nextState;
}