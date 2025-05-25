#pragma once
#include <cmath>

enum class ShelfType {
    Low,
    High
};

class ShelfFilter {
public:
    void Init(float sampleRate, ShelfType type);
    void SetGainDb(float gainDb);
    void SetFrequency(float freq);
    float Process(float in);
    void Reset();

private:
    void UpdateCoeffs();

    ShelfType type_;
    float sr_, freq_, gain_;
    float b0_, b1_, b2_, a1_, a2_;
    float x1_ = 0, x2_ = 0, y1_ = 0, y2_ = 0;
};