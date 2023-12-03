#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

void init_led() {
    #ifndef PICO_DEFAULT_LED_PIN
    #warning Blink requires a board with the default LED
    #else
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    #endif
}

int main() {
    stdio_init_all(); // Setup serial over USB
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    init_led();
    printf("\n\n\nStarting...\n");

    gpio_init(4);
    gpio_set_dir(4, GPIO_IN);
    gpio_init(7);
    gpio_set_dir(7, GPIO_IN);

    // Input loop
    while (true) {
        bool button1_state = gpio_get(4);
        bool button2_state = gpio_get(7);

        if (button1_state && button2_state) {
            printf("Both buttons pressed\n");
        } else if (button1_state) {
            printf("Button on 4 pressed\n");
        } else if (button2_state) {
            printf("Button on 7 pressed\n");
        }

        // Add a delay to avoid printing too quickly
        sleep_ms(100);
        printf("uwu\n");
    }
}

