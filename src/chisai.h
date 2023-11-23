// Global vars
#define LED_PIN PICO_DEFAULT_LED_PIN
#define MAX_INPUT_LENGTH 100
#define RPIN 25
#define ADCCH 0

void get_random_data(char *buf, uint16_t len);
void init_led();
void blink(int t);
char* getInputString();
void rsleep(uint32_t min_ms, uint32_t max_ms);
void space();
void intro();