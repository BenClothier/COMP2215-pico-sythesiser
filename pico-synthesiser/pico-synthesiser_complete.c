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

#define VOLTAGE_IN_PIN 26
#define AUDIO_OUT_PIN 18

float input_voltage = 3.3f;
float highest_freq = 1000.0f;
float lowest_freq = 0.0f;

uint slice_num;
const uint16_t duty = 50;

uint32_t voltageToFreq(float voltage) {
    return (uint32_t)(highest_freq - (voltage / input_voltage) * (highest_freq - lowest_freq));
}

float getVoltageFromADC() {
    return (float)adc_read() * (input_voltage / (1 << 12));
}

int pwm_set_freq(uint32_t freq) {
    uint32_t f_sys = clock_get_hz(clk_sys);
    float divider = f_sys / 1000000UL;
    pwm_set_clkdiv(slice_num, divider);

    uint32_t top = 1000000UL / freq - 1;
    pwm_set_wrap(slice_num, top);

    uint16_t level = (top + 1) * duty / 100 - 1;
    pwm_set_chan_level(slice_num, 0, level);
}

void on_pwm_wrap() {
    float voltage = getVoltageFromADC();
    uint32_t freq = voltageToFreq(voltage);
    pwm_set_freq(freq);
}

int main() {
    stdio_init_all();

    adc_init();
    adc_gpio_init(VOLTAGE_IN_PIN);
    adc_select_input(VOLTAGE_IN_PIN - 26);

    gpio_set_function(AUDIO_OUT_PIN, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(AUDIO_OUT_PIN);

    pwm_clear_irq(slice_num);
    pwm_set_irq_enabled(slice_num, true);
    irq_set_exclusive_handler(PWM_IRQ_WRAP, on_pwm_wrap);
    irq_set_enabled(PWM_IRQ_WRAP, true);

    pwm_set_enabled(slice_num, true);

    for (;;);
}