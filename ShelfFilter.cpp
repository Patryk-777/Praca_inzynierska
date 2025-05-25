#include "ShelfFilter.h"

void ShelfFilter::Init(float sampleRate, ShelfType type) {
    sr_ = sampleRate;
    type_ = type;
    SetGainDb(0.0f);
    SetFrequency((type == ShelfType::Low) ? 200.0f : 3000.0f);
    Reset();
}

void ShelfFilter::SetGainDb(float gainDb) {
    gain_ = powf(10.0f, gainDb / 20.0f);
    UpdateCoeffs();
}

void ShelfFilter::SetFrequency(float freq) {
    freq_ = freq;
    UpdateCoeffs();
}

float ShelfFilter::Process(float in) {
    float out = b0_ * in + b1_ * x1_ + b2_ * x2_ - a1_ * y1_ - a2_ * y2_;
    x2_ = x1_; x1_ = in; y2_ = y1_; y1_ = out;
    return out;
}

void ShelfFilter::Reset() {
    x1_ = x2_ = y1_ = y2_ = 0.0f;
}

void ShelfFilter::UpdateCoeffs() {
    float A = sqrtf(gain_);
    float w0 = 2.0f * float(M_PI) * freq_ / sr_;
    float cosw0 = cosf(w0), sinw0 = sinf(w0);
    float alpha = sinw0 / 2.0f * sqrtf((gain_ + 1.0f/gain_) * (1.0f/0.707f - 1.0f) + 2.0f);

    if (type_ == ShelfType::Low) {
        float b0 = gain_ * ((gain_ + 1) - (gain_ - 1) * cosw0 + 2 * A * alpha);
        float b1 = 2 * gain_ * ((gain_ - 1) - (gain_ + 1) * cosw0);
        float b2 = gain_ * ((gain_ + 1) - (gain_ - 1) * cosw0 - 2 * A * alpha);
        float a0 = (gain_ + 1) + (gain_ - 1) * cosw0 + 2 * A * alpha;
        float a1 = -2 * ((gain_ - 1) + (gain_ + 1) * cosw0);
        float a2 = (gain_ + 1) + (gain_ - 1) * cosw0 - 2 * A * alpha;
        b0_ = b0/a0; b1_ = b1/a0; b2_ = b2/a0; a1_ = a1/a0; a2_ = a2/a0;
    } else {
        float b0 = gain_ * ((gain_ + 1) + (gain_ - 1) * cosw0 + 2 * A * alpha);
        float b1 = -2 * gain_ * ((gain_ - 1) + (gain_ + 1) * cosw0);
        float b2 = gain_ * ((gain_ + 1) + (gain_ - 1) * cosw0 - 2 * A * alpha);
        float a0 = (gain_ + 1) - (gain_ - 1) * cosw0 + 2 * A * alpha;
        float a1 = 2 * ((gain_ - 1) - (gain_ + 1) * cosw0);
        float a2 = (gain_ + 1) - (gain_ - 1) * cosw0 - 2 * A * alpha;
        b0_ = b0/a0; b1_ = b1/a0; b2_ = b2/a0; a1_ = a1/a0; a2_ = a2/a0;
    }
}