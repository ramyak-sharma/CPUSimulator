#include "component.h"

Component::Component(unsigned int id) : m_id(id) {

}

Rectangle Component::getBounds() const {
    return {m_position.x, m_position.y, m_size.x, m_size.y};
}

Rectangle Component::getInteractionBounds() const {
    float padding = 10.0f;
    return {
        m_position.x - padding,
        m_position.y - padding,
        m_size.x + (padding * 2),
        m_size.y + (padding * 2)
    };
}

void Component::setPosition(const Vector2& pos) {
    m_position = pos;
    
    updateNodePositions();
}

void Component::updateNodePositions() {
    Rectangle bounds = getBounds();
    
    float in_spacing = bounds.height / (m_inputNodes.size() + 1);
    for (int i = 0; i < m_inputNodes.size(); ++i) {
        m_inputNodes[i].position = {bounds.x, bounds.y + in_spacing * (i + 1)};
    }

    float out_spacing = bounds.height / (m_outputNodes.size() + 1);
    for (int i = 0; i < m_outputNodes.size(); ++i) {
        m_outputNodes[i].position = {bounds.x + bounds.width, bounds.y + out_spacing * (i + 1)};
    }
}