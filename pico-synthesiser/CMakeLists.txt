# add_executable(pico-synthesiser
#         pico-synthesiser.c
#         )
        
add_executable(pico-synthesiser_complete
        pico-synthesiser_complete.c
)

# pull in common dependencies
# target_link_libraries(pico-synthesiser pico_stdlib hardware_adc hardware_pwm)
target_link_libraries(pico-synthesiser_complete pico_stdlib hardware_adc hardware_pwm)

# pico_enable_stdio_usb(pico-synthesiser 1)
pico_enable_stdio_usb(pico-synthesiser_complete 1)

# pico_enable_stdio_uart(pico-synthesiser 0)
pico_enable_stdio_uart(pico-synthesiser_complete 0)

# create map/bin/hex file etc.
# pico_add_extra_outputs(pico-synthesiser)
pico_add_extra_outputs(pico-synthesiser_complete)

# add url via pico_set_program_url
# example_auto_set_url(pico-synthesiser)
example_auto_set_url(pico-synthesiser_complete)
