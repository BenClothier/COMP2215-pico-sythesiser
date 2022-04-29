/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/adc.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    stdio_init_all();
    gpio_init(25);
    adc_init();
    adc_gpio_init(26);
    adc_select_input(0);

    while(true) {
        uint16_t result = adc_read();
        const float conversion_factor = 3.3f / (1 << 12);
        printf("Raw value: 0x%03x, voltage: %f V\n", result, result * conversion_factor);
        sleep_ms(1000);
    }
}