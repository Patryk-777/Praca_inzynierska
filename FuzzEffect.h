#pragma once
#include "AnalogFuzz.h"
#include "OnePoleLPF.h"
#include "ShelfFilter.h"

class FuzzEffect {
public:
    void Init(float sampleRate);
    float Process(float in);
    void SetGain(float gain);
    void SetVolume(float volume);
    void SetFilter(float cutoff);
    void SetLowEQ(float db);
    void SetHighEQ(float db);

private:
    float volume_ = 1.0f;
    AnalogFuzz fuzz_;
    OnePoleLPF filter_;
    ShelfFilter low_, high_;
};