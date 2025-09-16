#pragma once
#include "components/component.h"
#include "components/node.h"

class NotGate : public Component {
public:
    NotGate(unsigned int id);

    void update() override;

    void display() const override;

private:

    Node m_input;
    Node m_output;

};

