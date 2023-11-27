#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "hardware/sync.h"
#include "hardware/structs/ioqspi.h"
#include "hardware/structs/sio.h"

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
    printf("\n\n~\nDaemonCTF{lift_off}\n~\n\n");
    for (int j = 0; j < 100; ++j) { // Adjust the number of iterations as needed
        for (int i = 0; i < 69; ++i) { // Adjust the number of iterations as needed
            get_random_data(buf, len);
            char character_to_print = (buf[0] % 4 == 0) ? '*' : ' ';
            printf("%c", character_to_print);
        }
        printf("\n"); // TODO if putty doesn't wrap, we will need to make sure it does
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
    printf("Die ID UNKOWN\n");
    rsleep(10, 300);
    printf("4-bit x-loader detected, on-die ecc enabled\n");
    rsleep(10, 300);
    printf("g_bootData0.bootableconfig 0x0000008f, lastbootableconfig 0x00000080 ...\n");
    rsleep(10, 500);
    printf("eccflags 0x00000000 ecc_status 0x55555555\n");
    rsleep(10, 200);
    printf("\n");
    rsleep(10, 300);
    printf("@@@@@@@@@@@@ starting RP2040 pi-boot 2  @@@@@@@@@@@@@\n");
    rsleep(10, 100);
    printf("\033[1;32m"); // Set text color to neon green
    printf("                             ``.                                   `.'`                             \n"
       "                        `-~^^:`                                     `-\":~_                         \n"
       "                      \"!x*<-                         ``            .`    _r<=.                      \n"
       "                    !^x*^`                           `<,:`           `     -(v~-                    \n"
       "                  `<x*v-              `'   `            -^r_`        .      `*rx_                   \n"
       "                 `\\*x^'-            `\"````               `-~v\"`          `   `rx*_                  \n"
       "                 _x*x_`'           :_.``                    _>|-              ^x**                  \n"
       "                 .x*x_            !x;*'`                      <r!     .       *x**                  \n"
       "                  r*x^:          ^*x*]~-                       =v<          `<rx*_                  \n"
       "                  ->x*x^^,_'`  `,x*x*x.                     ` `.v?!-` ``-_~~xv*r.                   \n"
       "                   ,-,^^x*x?)v*x*x*x*~                      `  `v()x*xv)x*x;=_`:                    \n"
       "                    :- `,!x|*^!^=x*x*`                        . -()\\<vv)x!\"` .:                     \n"
       "                     -,   `:r*-``x*x^` .         ``         `.` `(~ _|),`  `.:                      \n"
       "                    `'`,-    ,<x!x^x^` x=:`      .-      `:~x*` :(*v<,    ._- -                     \n"
       "     ,!r<r=*:^!~!:!_\"'  _!.    !*x^x*` }*i<^'  ` .!`   .=rxrL`  *?r:    '.:  '_:\"~:^!<<!^=r>*:`     \n"
       "  ,~v}r>-'`. `      `.:_::\"-\"-   -x^x*. T)Tr}rr_x'.^v,:<vxv}?Y   ?)`   `.\"'-_::```` '     ` `*Trr:`  \n"
       " _!!^\\rY^^__ '      '   `,  `,-- =^]*_ !!vrT?Yr? '*x*ivi]vx~! `,v_  `,,`                _,r^}L<^:!` \n"
       "      ``-!^Y<^`     '          `_r*x!'    `,:)*^ `*x)Y*;:-`   -`|!-,_`               !*r}~~-'  `    \n"
       "          :!.~r\\:`   `          -x*,.*`        ` `*x-'   `  `!. *r` -            `-)r<!``           \n"
       "          `.   *rx\\_`           .x^  !^.         `*x`      .)\"  ^>          '  :=L~:` `             \n"
       "                 -~^}=\"  `      `x*- _!x,`       `*x\"    `=*;   r.          !^(x:,'`  `             \n"
       "             ``  `  .:i*<.``     *^* ``ruV:-      *x:  -=v}!  `-! _`  ` ``~*}^_`                    \n"
       "             ``  `>    !rr|!`    `'x_  .|#HZv^,\"'.^=,^vs6Ox`  :<  ``   _r)v_- ..             `      \n"
       "             ``  ~i !,   :<||>`  ` -^!  -cO@$#MgI$I85#Q#Bx= `-*`   - !(^x:,'`  `             \n"
       "                 '_         !?r>` ',`\\:` =L@$@0@D@D@$@Q#I^:`<=    `^*x!` `  - `.                    \n"
       "                   \"~        ._r*^\", `=r` ,3$@0@E@D@0@Qe!`_=~   `=vr_ .  :` `.                      \n"
       "                   `      -'  ''`^^).  ^~\" !]B0@D@D@$#V: _)-  `!x!`   .  `                          \n"
       "                           `   ``'-:=r` _v:-`^x$d@d8c*.`~!  '!]v-   ` `                             \n"
       "                                   _ _!~ `:?-``,,~,_` .^\" `!v_!v`                                   \n"
       "                                  _^  `_!: -!=`.     ;>` ,*-.`\\`                                   \n"
       "                                  `-`  ` -!_ -!!`` :^! `~:'`= _`_ '\"    `                           \n"
       "                             `   ``` .    -:` _^~)<).  '.     ':                                    \n");
    printf("\033[0m"); // Reset text color
    printf("Press BOOTSEL button to interrupt bootcycle:\n");
}

bool __no_inline_not_in_flash_func(get_bootsel_button)() {
    // This example blinks the Pico LED when the BOOTSEL button is pressed.
    //
    // Picoboard has a button attached to the flash CS pin, which the bootrom
    // checks, and jumps straight to the USB bootcode if the button is pressed
    // (pulling flash CS low). We can check this pin in by jumping to some code in
    // SRAM (so that the XIP interface is not required), floating the flash CS
    // pin, and observing whether it is pulled low.
    //
    // This doesn't work if others are trying to access flash at the same time,
    // e.g. XIP streamer, or the other core.
    const uint CS_PIN_INDEX = 1;

    // Must disable interrupts, as interrupt handlers may be in flash, and we
    // are about to temporarily disable flash access!
    uint32_t flags = save_and_disable_interrupts();

    // Set chip select to Hi-Z
    hw_write_masked(&ioqspi_hw->io[CS_PIN_INDEX].ctrl,
                    GPIO_OVERRIDE_LOW << IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_LSB,
                    IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_BITS);

    // Note we can't call into any sleep functions in flash right now
    for (volatile int i = 0; i < 1000; ++i);

    // The HI GPIO registers in SIO can observe and control the 6 QSPI pins.
    // Note the button pulls the pin *low* when pressed.
    bool button_state = !(sio_hw->gpio_hi_in & (1u << CS_PIN_INDEX));

    // Need to restore the state of chip select, else we are going to have a
    // bad time when we return to code in flash!
    hw_write_masked(&ioqspi_hw->io[CS_PIN_INDEX].ctrl,
                    GPIO_OVERRIDE_NORMAL << IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_LSB,
                    IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_BITS);

    restore_interrupts(flags);

    return button_state;
}

bool checkButt() {
    // Check if butt pressed within a small timeframe
    bool out = false; // if the button is pressed, we will eventually return true
    for (int i = 0;i < 300; ++i) { // 3 sec check
        gpio_put(PICO_DEFAULT_LED_PIN, get_bootsel_button() ^ PICO_DEFAULT_LED_PIN_INVERTED);
        if (get_bootsel_button() > 0) {
            out = true;
        }
        if (i % 100 == 0) {
            printf(". ");
        }
        sleep_ms(10);
    }
    printf("\n");
    return out;
}

void challenges() {
    printf("Challenges\n");
}
void aes() {
    printf("AES\n");
}
void ch0() {
    printf("ch0\n");
}
void ch1() {
    printf("ch1\n");
}
