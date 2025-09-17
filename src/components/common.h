#pragma once
#include <iostream>

enum class LogicState{
	LOW = 0, 
	HIGH = 1
};

enum class InteractionMode{
    NORMAL,
    WIRING
};

enum class ComponentType{
    AND_GATE, NOT_GATE
};

enum class NodeType {
    INPUT,
    OUTPUT
};

struct Button
{
    std::string label;
    std::function<void()> onClick;
};