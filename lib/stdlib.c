/*
 * stdlib.c
 *
 *  Created on: Jan 10, 2021
 *      Author: dhpark
 */

#include "stdlib.h"
#include "../HalTimer.h"

void delay(uint32_t ms)
{
    uint32_t goal = Hal_timer_get_1ms_counter() + ms; // 현재 값 + 지연 시키고 싶은 시간
    
    while(goal != Hal_timer_get_1ms_counter());
}

void memclr(void *dst, uint32_t count)
{
    uint8_t *d = (uint8_t*)dst;
    while(count--)
    {
        *d++ = 0;   
    }
}
