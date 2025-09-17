#pragma once
#include "components/component.h"
#include "components/node.h"

class AndGate : public Component {
public:
    AndGate(unsigned int id);
    
    void evaluate() override;

    void commit() override;

    void display() const override;

};

