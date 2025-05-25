#include "daisy_seed.h"
#include "FuzzEffect.h"
#include "EffectBypass.h"

using namespace daisy;

DaisySeed hw;
FuzzEffect fuzz;
EffectBypass bypass;

// ADC channels for knobs
constexpr int VOLUME_ADC_CH = 0;
constexpr int GAIN_ADC_CH   = 1;
constexpr int FILTER_ADC_CH = 2;
constexpr int LOW_ADC_CH    = 3;
constexpr int HIGH_ADC_CH   = 4;

AnalogControl volumeCtrl, gainCtrl, filterCtrl, lowCtrl, highCtrl;

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
    bypass.Update();

    float volume = volumeCtrl.Process();
    float gain   = gainCtrl.Process();
    float filter = filterCtrl.Process();
    float low    = lowCtrl.Process();
    float high   = highCtrl.Process();

    fuzz.SetVolume(volume);
    fuzz.SetGain(gain * 50.0f);
    fuzz.SetFilter(filter * 8000.0f + 200.0f); // 200Hz–8.2kHz
    fuzz.SetLowEQ((low - 0.5f) * 12.0f);  // -6dB to +6dB
    fuzz.SetHighEQ((high - 0.5f) * 12.0f);

    for (size_t i = 0; i < size; ++i)
    {
        float input = in[0][i];
        float processed = bypass.IsEngaged() ? fuzz.Process(input) : input;
        out[0][i] = out[1][i] = processed;
    }
}

int main(void)
{
    hw.Configure();
    hw.Init();

    AdcChannelConfig adc_cfg[5];
    adc_cfg[0].InitSingle(hw.GetPin(16));
    adc_cfg[1].InitSingle(hw.GetPin(17));
    adc_cfg[2].InitSingle(hw.GetPin(18));
    adc_cfg[3].InitSingle(hw.GetPin(19));
    adc_cfg[4].InitSingle(hw.GetPin(20));
    hw.adc.Init(adc_cfg, 5);
    hw.adc.Start();

    volumeCtrl.Init(hw.adc.GetPtr(0), hw.AudioSampleRate());
    gainCtrl.Init(hw.adc.GetPtr(1), hw.AudioSampleRate());
    filterCtrl.Init(hw.adc.GetPtr(2), hw.AudioSampleRate());
    lowCtrl.Init(hw.adc.GetPtr(3), hw.AudioSampleRate());
    highCtrl.Init(hw.adc.GetPtr(4), hw.AudioSampleRate());

    fuzz.Init(hw.AudioSampleRate());
    bypass.Init(hw.GetPin(25), hw.GetPin(22));

    hw.StartAudio(AudioCallback);
    while (1) {
        System::Delay(1);
    }
} 