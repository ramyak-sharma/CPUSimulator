#pragma once
#include <iostream>
#include "common.h"

struct Node {
    static unsigned int ID;
    unsigned int m_id;
    LogicState state = LogicState::LOW;
    NodeType type;
    class Component* owner = nullptr;

    Node();
};

inline std::ostream& operator<<(std::ostream& os, const Node& node){
    std::string state = "HIGH";
    std::string type = "OUTPUT";
    if(node.state == LogicState::LOW) state = "LOW";
    if(node.type == NodeType::INPUT) type = "INPUT";

    os << " " << type << "      " << state;
    return os;
}
