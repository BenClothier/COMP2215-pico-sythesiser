/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "hardware/irq.h"
#include <stdio.h>
#include <stdlib.h>

#define VOLTAGE_IN_PIN 26       // Desired ADC input pin (make sure to check which pins are compatible with the ADC if you want to change this)
#define AUDIO_OUT_PIN 18        // Buzzer/AUX pin

float input_voltage = 3.3f;     // Voltage input of the potential divider circuit
float highest_freq = 1000.0f;   // Highest frequency wave that you want to generate
float lowest_freq = 0.0f;       // Lowest/Base frequency of the synthesiser

uint slice_num;                 // Slice number of the PWM
const uint16_t duty = 50;       // Duty cycle for the PWM

uint32_t voltageToFreq(float voltage) {
    return (uint32_t)(highest_freq - (voltage / input_voltage) * (highest_freq - lowest_freq));
}

float getVoltageFromADC() {
    return (float)adc_read() * (input_voltage / (1 << 12));
}

int pwm_set_freq(uint32_t freq) {
    // TODO: Configure the PWM to generate a wave of the given frequency...
}

void on_pwm_wrap() {
    // Every pwm-wrap, measures the voltage input and recalculates the desired frequency
    float voltage = getVoltageFromADC();
    uint32_t freq = voltageToFreq(voltage);
    pwm_set_freq(freq);
}

int main() {
    stdio_init_all();

    // TODO: Initialise ADC here...

    // Initialises PWM and on-wrap routine
    gpio_set_function(AUDIO_OUT_PIN, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(AUDIO_OUT_PIN);
    pwm_clear_irq(slice_num);
    pwm_set_irq_enabled(slice_num, true);
    irq_set_exclusive_handler(PWM_IRQ_WRAP, on_pwm_wrap);
    irq_set_enabled(PWM_IRQ_WRAP, true);
    pwm_set_enabled(slice_num, true);

    for (;;);
}