#include "component.h"

Rectangle Component::getBounds() const {
    return {m_position.x, m_position.y, m_size.x , m_size.y};
}

Rectangle Component::getInteractionBounds() const {
    float padding = 10.0f; // 10 pixels of padding on all sides
    return {
        m_position.x - padding,
        m_position.y - padding,
        m_size.x + (padding * 2),
        m_size.y + (padding * 2)
    };
}
