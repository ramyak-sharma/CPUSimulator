#pragma once
#include "components/component.h"

class OutLight : public Component {
public:
    OutLight(unsigned int id);

    void evaluate() override;
    
    void commit() override;
};