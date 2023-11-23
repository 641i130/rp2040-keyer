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
    // See if user presses the boot sel button
    // Code just lights up light for now
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    while (true) {
        gpio_put(PICO_DEFAULT_LED_PIN, get_bootsel_button() ^ PICO_DEFAULT_LED_PIN_INVERTED);
        sleep_ms(10);
    }
    // depending on the outcome of if they pressed the button down
    // put them in a weird mode
    // not normal ctf mode
    // NULL mode is what its called cause its \0 lol

    // if they dont switch it into flashy light mode for future problems
    char *userInput = getInputString();
    // You can now use the userInput string as needed
    printf("\nEntered string: %s\n", userInput);
    // Don't forget to free the allocated memory
    free(userInput);
    
    // INPUT LOOP
    // Cycle through the problems, given the user requesting X question to solve

    while (true) {
        sleep_ms(1000);
        blink(10);
    }
}
