#include "u_button.h"

#include "zf_gpio.h"
#include "zf_delay.h"

unsigned char button_state = BUTTON_EMPTY;

void u_button_Init(void)
{
    gpio_mode(P1_5, GPI_IMPEDANCE);
    gpio_mode(P1_7, GPI_IMPEDANCE);
    gpio_mode(P5_0, GPI_IMPEDANCE);
    gpio_mode(P5_1, GPI_IMPEDANCE);
}

void u_button_get_state(void)
{
    
}

