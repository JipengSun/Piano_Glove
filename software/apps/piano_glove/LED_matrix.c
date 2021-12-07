#include "led_matrix.h"
#include "app_timer.h"
#include "font.h"
#include "microbit_v2.h"
#include <stdlib.h>
#include <string.h>
#include "nrf_delay.h"

APP_TIMER_DEF(my_timer);

static uint32_t led_states[5][5] = { { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 } };

static uint32_t row_num[5] = { LED_ROW1, LED_ROW2, LED_ROW3, LED_ROW4, LED_ROW5 };
static uint32_t col_num[5] = { LED_COL1, LED_COL2, LED_COL3, LED_COL4, LED_COL5 };

int index1 = 0;
char charValue;


void display_char(char my_char)
{
    // int row_index = (int)my_char;
    int row_index = (int)my_char;
    for (int i = 0; i < 5; i++) {
        led_states[i][0] = (font[row_index][i] >> 0) & 1;
        led_states[i][1] = (font[row_index][i] >> 1) & 1;
        led_states[i][2] = (font[row_index][i] >> 2) & 1;
        led_states[i][3] = (font[row_index][i] >> 3) & 1;
        led_states[i][4] = (font[row_index][i] >> 4) & 1;
    }
}

void LED_display(int my_char)
{
    if (my_char == 8) {
        charValue = 'L';
    } else if (my_char == 9) {
        charValue = 'R';
    } else{
        sprintf(&charValue, "%d", my_char);

    }
    display_char(charValue);
    //printf("In LED_display, the showing number is char:::%s \n", &charValue);
}

void led_write()
{
    nrf_gpio_pin_write(row_num[index1], 0);
    index1 = (index1 + 1) % 5;
    for (int i = 0; i < 5; i++) {
        nrf_gpio_pin_write(col_num[i], 1);
        nrf_gpio_pin_write(col_num[i], !led_states[index1][i]);
    }
    nrf_gpio_pin_write(row_num[index1], 1);
}

void display_string(char* mystring){
    for(int i = 0; i< strlen(mystring);i++){
        display_char(mystring[i]);
        nrf_delay_ms(500);
    }
}

void led_matrix_init(void)
{
    printf("Initializing the led matrix...\n");
    // initialize row pins
    nrf_gpio_pin_dir_set(LED_ROW1, NRF_GPIO_PIN_DIR_OUTPUT);
    nrf_gpio_pin_dir_set(LED_ROW2, NRF_GPIO_PIN_DIR_OUTPUT);
    nrf_gpio_pin_dir_set(LED_ROW3, NRF_GPIO_PIN_DIR_OUTPUT);
    nrf_gpio_pin_dir_set(LED_ROW4, NRF_GPIO_PIN_DIR_OUTPUT);
    nrf_gpio_pin_dir_set(LED_ROW5, NRF_GPIO_PIN_DIR_OUTPUT);
    // initialize col pins
    nrf_gpio_pin_dir_set(LED_COL1, NRF_GPIO_PIN_DIR_OUTPUT);
    nrf_gpio_pin_dir_set(LED_COL2, NRF_GPIO_PIN_DIR_OUTPUT);
    nrf_gpio_pin_dir_set(LED_COL3, NRF_GPIO_PIN_DIR_OUTPUT);
    nrf_gpio_pin_dir_set(LED_COL4, NRF_GPIO_PIN_DIR_OUTPUT);
    nrf_gpio_pin_dir_set(LED_COL5, NRF_GPIO_PIN_DIR_OUTPUT);
    // set default values for pins
    nrf_gpio_pin_clear(LED_ROW1);
    nrf_gpio_pin_clear(LED_ROW2);
    nrf_gpio_pin_clear(LED_ROW3);
    nrf_gpio_pin_clear(LED_ROW4);
    nrf_gpio_pin_clear(LED_ROW5);
    nrf_gpio_pin_set(LED_COL1);
    nrf_gpio_pin_set(LED_COL2);
    nrf_gpio_pin_set(LED_COL3);
    nrf_gpio_pin_set(LED_COL4);
    nrf_gpio_pin_set(LED_COL5);

    //app_timer_init();
    app_timer_create(&my_timer, APP_TIMER_MODE_REPEATED, led_write);
    app_timer_start(my_timer, 100, NULL);
}