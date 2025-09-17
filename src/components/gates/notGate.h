#pragma once
#include "components/component.h"

class NotGate : public Component {
public:
    NotGate(unsigned int id);
    
    void evaluate() override;
    void commit() override;
};