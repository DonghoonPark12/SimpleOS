#include "stdint.h"
#include "../hal/HalUart.h"
#include "../hal/HalInterrupt.h"
#include "../hal/HalTimer.h"
#include "../kernel/task.h"
#include "../kernel/Kernel.h"

#include "stdio.h"
#include "stdlib.h"

static void Hw_init(void);
static void Kernel_init(void);

static void Printf_test(void);
static void Timer_test(void);

void User_task0(void);
void User_task1(void);
void User_task2(void);

void main(){
	Hw_init();

	uint32_t i = 20;
	while(i--)
	{
	Hal_uart_put_char('N');  
	}
	Hal_uart_put_char('\n');

	putstr("Hellow World\n");

	Printf_test();
	Timer_test();
	Kernel_init();
	//while(1);

	i = 100;
	while(i--)
	{
	  uint8_t ch = Hal_uart_get_char();
	  Hal_uart_put_char(ch);
	}
}

static void Hw_init(void)
{
    Hal_interrupt_init();
    Hal_uart_init();
	Hal_timer_init();
}

static void Kernel_init(void)
{
	uint32_t taskId;
	Kernel_evnent_flag_init();

	taskId = Kernel_task_create(User_task0);
	if(NOT_ENOUGH_TASK_NUM == taskID)
	{
		putstr("Task0 creation fail\n");
	}

    taskId = Kernel_task_create(User_task1);
    if (NOT_ENOUGH_TASK_NUM == taskId)
    {
        putstr("Task1 creation fail\n");
    }

    taskId = Kernel_task_create(User_task2);
    if (NOT_ENOUGH_TASK_NUM == taskId)
    {
        putstr("Task2 creation fail\n");
    }	
	
	Kernel_start();
}

void User_task0(void)
{
	uint32_t local = 0;
	
	//debug_printf("User Task #0\n");
	//while(true); //[21.01.10] 현재는 테스크의 종료를 보장하는 기능이 없기 때문에, 테스크는 종료되면 안된다.
	
	while(true)
	{
		debug_printf("User Task #0 SP=0x%x\n", &local);
		Kernel_yield();
	}
}

void User_task1(void)
{
	uint32_t local = 0;
	
	//debug_printf("User Task #1\n");
	//while(true);
	
	while(true)
	{
		debug_printf("User Task #1 SP=0x%x\n", &local);
		Kernel_yield();
	}
}

void User_task2(void)
{
	uint32_t local = 0;
	
	//debug_printf("User Task #2\n");
	//while(true);
	
	while(true)
	{
		debug_printf("User Task #2 SP=0x%x\n", &local);
		Kernel_yield();
	}
}

static void Printf_test(void)
{
	char* str = "printf pointer test";
	char* nullptr = 0;
	uint32_t i = 5;
	uint32_t* sysctrl0 = (uint32_t*)0x10001000;
	
	debug_printf("%s\n", "Hello printf");
	debug_printf("output string pointer: %s\n", str);
	debug_printf("%s is null pointer, %u number\n", nullptr, 10);
	debug_printf("%u = 5\n", i);
	debug_printf("dec = %u hex=%x\n", 0xff, 0xff);
	debug_printf("print zero %u\n", 0);
	
	debug_printf("--------Chap7---------\n");
	debug_printf("SYSCTRL0 %x\n", *sysctrl0);
}

static void Timer_test(void)
{
	while(true)
	{
        debug_printf("current count : %u\n", Hal_timer_get_1ms_counter());
        delay(1000);		
	}
}
