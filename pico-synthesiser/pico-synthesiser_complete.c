/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/adc.h"
#include <stdio.h>
#include <stdlib.h>

float input_voltage = 3.3f;
double highest_freq = 3000;
double lowest_freq = 0;

int main() {
    stdio_init_all();
    gpio_init(25);
    adc_init();
    adc_gpio_init(26);
    adc_select_input(0);

    while(true) {
        float voltage = getVoltageFromADC();
        printf("Voltage: %f V\n", result * conversion_factor, );
        sleep_ms(1000);
    }
}

double voltageToFreq(float voltage) {
    return highest_freq - (voltage / input_voltage) * (highest_freq - lowest_freq)
}

float getVoltageFromADC() {
    return adc_read() * (input_voltage / (1 << 12))
}