#pragma once
#include "components/component.h"
#include "components/node.h"

class NotGate : public Component {
public:
    NotGate(unsigned int id);

    void evaluate() override;

    void commit() override;

    void display() const override;

};

