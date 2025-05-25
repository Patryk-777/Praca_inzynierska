#include "OnePoleLPF.h"

void OnePoleLPF::Init(float sampleRate) {
    sr_ = sampleRate;
    SetCutoff(1000.0f);
    z_ = 0.0f;
}

void OnePoleLPF::SetCutoff(float cutoff) {
    float x = expf(-2.0f * float(M_PI) * cutoff / sr_);
    a_ = 1.0f - x;
}

float OnePoleLPF::Process(float in) {
    z_ += a_ * (in - z_);
    return z_;
}