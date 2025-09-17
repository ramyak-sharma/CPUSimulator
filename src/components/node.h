#pragma once
#include <iostream>
#include "common.h"
#include "raylib.h"

class Component;

struct Node {

    static unsigned int ID;
    unsigned int m_id;

    LogicState nextState = LogicState::LOW;
    LogicState currentState = LogicState::LOW;

    Vector2 position = {0.0f, 0.0f};
    NodeType type;

    unsigned int owner; 
    std::vector<std::unique_ptr<Node>> out_connections;

    Node();
};
