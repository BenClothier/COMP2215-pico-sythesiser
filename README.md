# Pico Synthesiser
## Description
In this task you will make a synthesiser using the PWM and a potential divider. You will need to implement the function `pwm_set_freq(uint32_t freq)` to tell the PWM to generate a wave at the given frequency, and then create a small potential divider circuit to input an adjustable voltage into the ADC (I did this using a light dependent resistor).

## Task Classification
MEDIUM since there are multiple aspects to this task that require a fair amount of reading about the pico's ADC and PWM.

## Help
- [The Pico in C: Basic PWM](https://www.i-programmer.info/programming/hardware/14849-the-pico-in-c-basic-pwm.html)
- [Basic Pico ADC in C](https://www.okdo.com/getting-started/get-started-with-raspberry-pi-pico-gpio-c-c/)

## Making a Potential Divider
### Potential divider circuit using an LDR
![Circuit Diagram](./images/circuit.png)

### My potential divider
![My Potential Divider](./images/board.png)
