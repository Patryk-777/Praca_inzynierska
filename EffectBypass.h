#pragma once
#include "daisy_seed.h"

class EffectBypass {
public:
    void Init(dsy_gpio_pin switchPin, dsy_gpio_pin ledPin);
    void Update();
    bool IsEngaged() const;

private:
    dsy_gpio footswitch_, led_;
    bool engaged_ = true;
    bool lastState_ = false;
};