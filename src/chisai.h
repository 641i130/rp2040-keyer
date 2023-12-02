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
bool __no_inline_not_in_flash_func(get_bootsel_button)();
bool checkButt();
void challenges();
void aes();
void ch0();
void ch1();
void huh();
