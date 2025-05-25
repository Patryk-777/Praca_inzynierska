#pragma once
#include <cmath>

class AnalogFuzz {
public:
    void Init();
    void SetGain(float gain);
    float Process(float in);

private:
    float gain_ = 1.0f;
};