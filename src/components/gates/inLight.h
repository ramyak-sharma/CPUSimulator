#pragma once
#include "components/component.h"

class InLight : public Component {
public:
    InLight(unsigned int id);

    void evaluate() override;
    void commit() override;

    bool isToggleable() const override { return true; }
    void toggle() override;

private:
    LogicState m_manualState = LogicState::LOW;
};