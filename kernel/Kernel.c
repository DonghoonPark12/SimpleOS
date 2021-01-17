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
