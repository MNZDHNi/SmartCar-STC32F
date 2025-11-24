#include <STC32G.H>
#include "DIR.h"

/*
    zuo_dir P10
    you_dir P13
*/

void DIR_Init(void)
{
    EAXFR = 1;

    P1M0 |= 0x09;  // 0000 1001
    P1M1 |= ~0x09; // 1111 0110

    P1 &= ~0x09; // 1111 0110
}

void Set_DIR(unsigned char channel, unsigned char dir)
{
    if(channel == 1)
    {
        P10 = dir;
    }
    else if(channel == 2)
    {
        P13 = dir;
    } 
}