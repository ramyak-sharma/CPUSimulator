#pragma once
#include <vector>
#include "components/common.h"
#include "raylib.h"

class Component {
public:
    virtual ~Component() = default;

    virtual void update() = 0;

    virtual void display() const = 0;

    unsigned int getId() const { return m_id; }

    Rectangle getBounds() const;
    
    Rectangle getInteractionBounds() const;

public:
	float m_x = 0;
	float m_y = 0;
	float m_width = 100;
	float m_height = 100;
	ComponentType m_type;

protected:
    Component(unsigned int id) : m_id(id) {}

    unsigned int m_id;
    
};
