#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"

// For memcpy
#include <string.h>

void get_random_data(char *buf, uint16_t len) {
    // Copied from https://github.com/evinrude/pico-rng
    uint16_t adc_result;
    uint8_t size;
    int i;
    gpio_put(25, 1);
    if(len > 64) {
        //TODO handle length error
        size = 64;
    }
    memset(buf, 0, len);
    for(i = 1; i <= len; i=i+1)
    {
        adc_result = adc_read();
        memcpy(&buf[i-1], (void*)&adc_result, 2);
    }
    gpio_put(25, 0);
}

int main() {
    stdio_init_all();
    adc_init();
    adc_gpio_init(26);
    adc_select_input(0);
    
    while (true) {
        #ifndef PICO_DEFAULT_LED_PIN
        #warning Blink requires a board with the default LED
        #else
        const uint LED_PIN = PICO_DEFAULT_LED_PIN;
        gpio_init(LED_PIN);
        gpio_set_dir(LED_PIN, GPIO_OUT);
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
        #endif
        printf("Hello, world!\n");
        sleep_ms(1000);
        // Example: Initialize the random data buffer
        char random_data[10];  // Change the size as needed
        uint16_t data_length = sizeof(random_data);

        // Call the function to get random data
        get_random_data(random_data, data_length);

        // Print the random data using printf
        printf("Random Data: ");
        for (int i = 0; i < data_length; ++i) {
            printf("%02X ", (unsigned char)random_data[i]);
        }
        printf("\n");
        sleep_ms(1000);
    }
}

