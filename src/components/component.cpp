#include "component.h"

Rectangle Component::getBounds() const {
    return {m_x, m_y, m_width, m_height};
}

Rectangle Component::getInteractionBounds() const {
    float padding = 10.0f; // 10 pixels of padding on all sides
    return {
        m_x - padding,
        m_y - padding,
        m_width + (padding * 2),
        m_height + (padding * 2)
    };
}
