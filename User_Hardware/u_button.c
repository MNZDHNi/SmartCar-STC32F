#include "u_button.h"

#include "zf_gpio.h"
#include "zf_delay.h"

unsigned char button_state = BUTTON_EMPTY;

void u_button_Init(void)
{
    delay_init();

    gpio_mode(P1_5, GPI_IMPEDANCE);
    gpio_mode(P1_7, GPI_IMPEDANCE);
    gpio_mode(P5_0, GPI_IMPEDANCE);
    gpio_mode(P5_1, GPI_IMPEDANCE);
}

void u_button_scan(void)
{
    if(P15 == 0)
    {
        delay_ms(10);
        if(P15 == 0)
        {
            button_state = BUTTON_1;
        }
        while(P15 == 1);
        delay_ms(10);
    }
    if(P17 == 0)
    {
        delay_ms(10);
        if(P17 == 0)
        {
            button_state = BUTTON_2;
        }
        while(P17 == 1);
        delay_ms(10);
    }
    if(P50 == 0)
    {
        delay_ms(10);
        if(P50 == 0)
        {
            button_state = BUTTON_3;
        }
        while(P50 == 1);
        delay_ms(10);
    }
    if(P51 == 0)
    {
        delay_ms(10);
        if(P51 == 0)
        {
            button_state = BUTTON_4;
        }
        while(P51 == 1);
        delay_ms(10);
    }
}

void u_button_state(void)
{
    switch(button_state)
    {
        case BUTTON_1:
            // Handle button 1 press
            break;
        case BUTTON_2:
            // Handle button 2 press
            break;
        case BUTTON_3:
            // Handle button 3 press
            break;
        case BUTTON_4:
            // Handle button 4 press
            break;
        default:
            break;
    }
    // 注意清空按键状态
}
