/*
 * Kernel.c
 *
 *  Created on: Jan 17, 2021
 *      Author: dhpark
 */


#include "stdint.h"
#include "stdbool.h"

#include "Kernel.h"


void Kernel_start(void)
{
    Kernel_task_start();
}

void Kernel_yield(void)
{
    Kernel_task_scheduler();
}

void Kernel_send_events(uint32_t event_list)
{
    KernelEventFlag_t sending_event = KernelEventFlag_Empty;
    for(uin32_t i = 0; i < 32; i++)
    {
        if((event_list >> i) & 1)
        {
            SET_BIT(sending_event, i);
            Kernel_event_flag_set(sending_event);
        }
    }    
}

KernelEventFlag_t  Kernel_wait_event(uint32_t waiting_list)
{
    KernelEventFlag_t waiting_event = KernelEventFlag_Empty;
    for(uin32_t i = 0; i < 32; i++)
    {
        if((waiting_list >> i) & 1)
        {
            SET_BIT(waiting_event, i);
            if(Kernel_event_flag_check(waiting_event))
            {
                return waiting_event;   
            }
        }
    }
    return KernelEventFlag_Empty;
}
