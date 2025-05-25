#include "EffectBypass.h"

void EffectBypass::Init(dsy_gpio_pin switchPin, dsy_gpio_pin ledPin) {
    footswitch_.pin = switchPin;
    footswitch_.mode = DSY_GPIO_MODE_INPUT;
    footswitch_.pull = DSY_GPIO_PULLUP;
    dsy_gpio_init(&footswitch_);

    led_.pin = ledPin;
    led_.mode = DSY_GPIO_MODE_OUTPUT_PP;
    dsy_gpio_init(&led_);

    dsy_gpio_write(&led_, engaged_);
}

void EffectBypass::Update() {
    bool current = !dsy_gpio_read(&footswitch_);
    if (current && !lastState_) {
        engaged_ = !engaged_;
        dsy_gpio_write(&led_, engaged_);
    }
    lastState_ = current;
}

bool EffectBypass::IsEngaged() const {
    return engaged_;
}