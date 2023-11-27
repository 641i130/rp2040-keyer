#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
// Mine
#include "chisai.h"

int main() {
    stdio_init_all(); // Setup serial over USB
    // Set up bootsel button to flash
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    // boot sel setup ^ 
    adc_init();
    adc_gpio_init(RPIN);
    adc_select_input(ADCCH);
    init_led();
    sleep_ms(3000);
    space();
    intro(); // Run text intro
    bool mode = checkButt(); // See if user presses the boot sel button
    // depending on the outcome of if they pressed the button down
    if (!mode) {
        printf("Skipping ");
        for (int lmao = 0;lmao < 3;lmao++) {
            printf(". ");
            sleep_ms(200);
        }
        printf("\n");
        while (true) {
            challenges();
            char *u = getInputString();
            printf("\nEntered string: %s\n", u);
            switch (u[0]) {
                case '0':
                    // challenge 0
                    ch0();
                    break;
                case '1':
                    // challenge 1
                    ch1();
                    break;
                default:
                    break;
            }
            free(u);
        }
    } else {
        printf("OK");
        aes();
        while (true) {
            sleep_ms(1000);
            blink(10);
        }
    }
    return 0;
}
