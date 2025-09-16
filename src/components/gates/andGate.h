#pragma once
#include "components/component.h"
#include "components/node.h"

class AndGate : public Component {
public:
    AndGate(unsigned int id);

    void update() override;

    void display() const override;

private:

    Node m_input1;
    Node m_input2;
    Node m_output;
};

