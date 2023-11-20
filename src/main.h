// For memcpy
#include <string.h>

// Global vars
#define LED_PIN PICO_DEFAULT_LED_PIN
#define MAX_INPUT_LENGTH 100
#define RPIN 25
#define ADCCH 0

void get_random_data(char *buf, uint16_t len) {
    // Copied from https://github.com/evinrude/pico-rng
    uint16_t adc_result;
    uint8_t size;
    int i;
    gpio_put(RPIN, 1);
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
    gpio_put(RPIN, 0);
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

// Read USER INPUT BECAUSE ITS NOT PART OF THE STANDARD LIBRARY FOR SOME REASON
char* getInputString() {
    char *inputString = (char *)malloc(MAX_INPUT_LENGTH * sizeof(char));
    if (inputString == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
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


void rsleep(uint32_t min_ms, uint32_t max_ms) {
    char buf[64]; // Assuming the buffer size is 64
    uint16_t len = sizeof(buf);
    // Get random data
    get_random_data(buf, len);
    // Calculate a random sleep duration based on the data
    uint64_t sum = 0;
    for (int i = 0; i < len; i++) {
        sum += buf[i];
    }
    // Normalize the sum to be in the range [min_ms, max_ms]
    uint32_t sleep_duration = (sum % (max_ms - min_ms + 1)) + min_ms;
    // Sleep for the calculated duration
    sleep_ms(sleep_duration);
    // For testing purposes, print the sleep duration
    //printf("Slept for %u milliseconds\n", sleep_duration);
}

void space() {
    char buf[64]; // Assuming the buffer size is 64
    uint16_t len = sizeof(buf);

    for (int j = 0; j < 200; ++j) { // Adjust the number of iterations as needed
        for (int i = 0; i < 69; ++i) { // Adjust the number of iterations as needed
            get_random_data(buf, len);
            char character_to_print = (buf[0] % 4 == 0) ? '*' : ' ';
            printf("%c", character_to_print);
        }
        printf("\n");
        sleep_ms(10); // 100,000 microseconds = 100 milliseconds
    }
}

void intro() {
    // Randomize the intro and make it somewhat faithful to u-boot (to give them familiarity when hacking real devices)
    printf("In:    serial\n");
    rsleep(10, 200);
    printf("Out:   serial\n");
    rsleep(10, 200);
    printf("Err:   serial\n");
    rsleep(10, 200);
    printf("Die ID #2a8800010000000001433a3a0800e01b\n");
    rsleep(10, 300);
    printf("4-bit x-loader detected, on-die ecc enabled\n");
    rsleep(10, 300);
    printf("g_bootData1.bootableconfig 0x0000008f, lastbootableconfig 0x00000080 ...\n");
    rsleep(10, 500);
    printf("g_bootData2.bootableconfig 0x0000008f, lastbootableconfig 0x00000080 ...\n");
    rsleep(10, 700);
    printf("eccflags 0x00000000 ecc_status 0x55555555\n");
    rsleep(10, 200);
    printf("Current rootmtd: /dev/mtdblock11\n");
    rsleep(10, 200);
    printf("Current kerneladdr: 0x700000\n");
    rsleep(10, 200);
    printf("\n");
    rsleep(10, 300);
    printf("@@@@@@@@@@@@ starting RP2040 pi-boot 2  @@@@@@@@@@@@@\n");
    rsleep(10, 100);
    printf("Press BOOTSEL button to interrupt bootcycle.\n");
    printf(". ");
    sleep_ms(100);
    printf(". ");
    sleep_ms(100);
    printf(". ");
    sleep_ms(100);
    printf("\n");
}

