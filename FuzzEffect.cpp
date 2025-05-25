#include "FuzzEffect.h"

void FuzzEffect::Init(float sr) {
    fuzz_.Init();
    filter_.Init(sr);
    low_.Init(sr, ShelfType::Low);
    high_.Init(sr, ShelfType::High);
}

float FuzzEffect::Process(float in) {
    float out = fuzz_.Process(in);
    out = filter_.Process(out);
    out = low_.Process(out);
    out = high_.Process(out);
    return out * volume_;
}

void FuzzEffect::SetGain(float gain) {
    fuzz_.SetGain(gain);
}

void FuzzEffect::SetVolume(float volume) {
    volume_ = volume;
}

void FuzzEffect::SetFilter(float cutoff) {
    filter_.SetCutoff(cutoff);
}

void FuzzEffect::SetLowEQ(float db) {
    low_.SetGainDb(db);
}

void FuzzEffect::SetHighEQ(float db) {
    high_.SetGainDb(db);
}