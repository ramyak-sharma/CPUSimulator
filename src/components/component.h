#pragma once
#include <vector>
#include "components/common.h"
#include "raylib.h"
#include "node.h"
#include "raymath.h"

class Component  {
public:
    virtual ~Component() = default;

    virtual void evaluate() = 0;

    virtual void commit() = 0;

    virtual void display() const = 0;

    unsigned int getId() const { return m_id; }

    Rectangle getBounds() const;
    
    Rectangle getInteractionBounds() const;


public:
	Vector2 m_position = {0, 0};
	Vector2 m_size = {100, 50};
    Color m_color = BLACK;
    std::string m_label = "default";
	ComponentType m_type;
    std::vector<std::shared_ptr<Node>> m_inputNodes;
    std::vector<std::shared_ptr<Node>> m_outputNodes;

protected:
    Component(unsigned int id) : m_id(id) {}

    unsigned int m_id;
    
};
