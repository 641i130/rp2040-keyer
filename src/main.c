#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"

// For memcpy
#include <string.h>

const uint LED_PIN = PICO_DEFAULT_LED_PIN;

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

void init_led() {
    #ifndef PICO_DEFAULT_LED_PIN
    #warning Blink requires a board with the default LED
    #else
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    #endif
}

void blink(int t) {
    gpio_put(LED_PIN, 1);
    sleep_ms(t);
    gpio_put(LED_PIN, 0);
    sleep_ms(t);
}

#define MAX_INPUT_LENGTH 100

char* getInputString() {
    char *inputString = (char *)malloc(MAX_INPUT_LENGTH * sizeof(char));
    
    if (inputString == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter a string: ");

    char c;
    int index = 0;

    while (1) {
        c = getchar();
        putchar(c);  // Print the character as it is typed
        // Store the character in the inputString
        inputString[index] = c;
        index++;
        
        if (c == '\n' || c == '\r' || c == EOF) {
            break;  // Exit the loop when Enter is pressed
        }
        // Check if the inputString is about to exceed the maximum length
        if (index >= MAX_INPUT_LENGTH - 1) {
            fprintf(stderr, "Input length exceeds the maximum limit.\n");
            exit(EXIT_FAILURE);
        }
    }

    inputString[index] = '\0';  // Null-terminate the string

    return inputString;
}

int main() {
    stdio_init_all(); // Setup serial over USB
    adc_init();
    adc_gpio_init(26);
    adc_select_input(0);
    init_led();
    sleep_ms(3000);
    printf("\n\n\n***\n");
    printf("BOOTED!\n");
    while (true) {
        printf("Hello! What is your name? \n");
        char *userInput = getInputString();

        // You can now use the userInput string as needed
        printf("\nEntered string: %s\n", userInput);

        // Don't forget to free the allocated memory
        free(userInput);
        sleep_ms(1000);
        blink(10);
    }
}
