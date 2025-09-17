#pragma once
#include <iostream>
#include "common.h"
#include "raylib.h"

class Component;

struct Node {

    static unsigned int ID;
    unsigned int id;

    LogicState nextState = LogicState::LOW;
    LogicState currentState = LogicState::LOW;
    Node* incomingConnection = nullptr;

    Vector2 position = {0.0f, 0.0f};
    float radius = 5;
    Color color;
    NodeType type;

    Node();
};
