/*
 * stdlib.c
 *
 *  Created on: Jan 10, 2021
 *      Author: dhpark
 */
 
#include "stdint.h"
#include "stdbool.h"
#include "../HalTimer.h"

void delay(uint32_t ms)
{
    uint32_t goal = Hal_timer_get_1ms_counter() + ms; // 현재 값 + 지연 시키고 싶은 시간
    
    while(goal != Hal_timer_get_1ms_counter());
}
