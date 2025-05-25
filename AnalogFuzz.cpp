#include "AnalogFuzz.h"

void AnalogFuzz::Init() {
    gain_ = 1.0f;
}

void AnalogFuzz::SetGain(float gain) {
    gain_ = gain;
}

float AnalogFuzz::Process(float in) {
    float amplified = in * gain_;

    // Mieszanka soft i hard clippingu dla mocniejszego efektu fuzz
    float soft = tanhf(amplified);
    float hard = amplified;
    if (hard > 1.0f) hard = 1.0f;
    else if (hard < -1.0f) hard = -1.0f;

    return 0.6f * soft + 0.4f * hard; // mieszanka stylów przesteru
}
