#pragma once
#include <vector>
#include <string>
#include "raylib.h"
#include "raymath.h"
#include "node.h"
#include "common.h"

class Component {
public:
    // --- Rule of Five ---
    Component(unsigned int id);
    virtual ~Component() = default;
    Component(const Component&) = delete;
    Component& operator=(const Component&) = delete;
    Component(Component&&) = delete;
    Component& operator=(Component&&) = delete;

    // --- Core Logic (Pure Virtual) ---
    virtual void evaluate() = 0;
    virtual void commit() = 0;

    // --- Capabilities (Virtual) ---
    // Override in derived classes to grant specific abilities
    virtual bool isToggleable() const { return false; }
    virtual void toggle() { /* Default: do nothing */ }

    // --- Getters and Setters ---
    unsigned int getId() const { return m_id; }
    Rectangle getBounds() const;
    Rectangle getInteractionBounds() const;
    void setPosition(const Vector2& pos);

public:
    // Public members for easy access by managers
    Vector2 m_position = {150, 150};
    Vector2 m_size = {75, 50};
    Color m_color = BLACK;
    Color m_nextColor = BLACK; // For two-phase visual updates
    std::string m_label = "default";
    ComponentType m_type;

    std::vector<Node> m_inputNodes;
    std::vector<Node> m_outputNodes;

protected:
    unsigned int m_id;
    
private:
    // Helper to update node positions when the component moves
    void updateNodePositions();
};