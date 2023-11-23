#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"

#include "chisai.h"

int main() {
    stdio_init_all(); // Setup serial over USB
    adc_init();
    adc_gpio_init(RPIN);
    adc_select_input(ADCCH);
    init_led();
    sleep_ms(3000);
    space();
    intro(); // Run text intro
    char *userInput = getInputString();
    // You can now use the userInput string as needed
    printf("\nEntered string: %s\n", userInput);
    // Don't forget to free the allocated memory
    free(userInput);

    while (true) {
        sleep_ms(1000);
        blink(10);
    }
}
