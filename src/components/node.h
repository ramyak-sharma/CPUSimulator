#pragma once
#include <iostream>
#include "common.h"
#include "raylib.h"

class Component;

struct Node : public std::enable_shared_from_this<Node>{

    static unsigned int ID;
    unsigned int m_id;

    LogicState nextState = LogicState::LOW;
    LogicState currentState = LogicState::LOW;

    Vector2 position = {0.0f, 0.0f};
    float radius = 5;
    Color color;
    NodeType type;

    unsigned int owner; 

    Node();
};
