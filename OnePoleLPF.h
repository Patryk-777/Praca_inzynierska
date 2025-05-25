#pragma once
#include <cmath>

class OnePoleLPF {
public:
    void Init(float sampleRate);
    void SetCutoff(float cutoff);
    float Process(float in);

private:
    float sr_, a_, z_ = 0.0f;
};
