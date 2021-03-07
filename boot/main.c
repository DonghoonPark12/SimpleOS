#include "stdint.h"
#include "../hal/HalUart.h"
#include "../hal/HalInterrupt.h"
#include "../hal/HalTimer.h"
#include "../kernel/task.h"
#include "../kernel/Kernel.h"
#include "../kernel/event.h"
#include "../kernel/msg.h"

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
	Kernel_task_init();
	Kernel_event_flag_init();

	taskId = Kernel_task_create(User_task0, 0);
	if(NOT_ENOUGH_TASK_NUM == taskId)
	{
		putstr("Task0 creation fail\n");
	}

    taskId = Kernel_task_create(User_task1, 0);
    if (NOT_ENOUGH_TASK_NUM == taskId)
    {
        putstr("Task1 creation fail\n");
    }

    taskId = Kernel_task_create(User_task2, 0);
    if (NOT_ENOUGH_TASK_NUM == taskId)
    {
        putstr("Task2 creation fail\n");
    }	
	
	Kernel_start();
}

void User_task0(void)
{
	uint32_t local = 0;
	
	uint8_t cmdBuf[16];
	uint32_t cmdBufIdx = 0;
	uint8_t uartch = 0;
	
	//debug_printf("User Task #0\n");
	//while(true); //[21.01.10] 현재는 테스크의 종료를 보장하는 기능이 없기 때문에, 테스크는 종료되면 안된다.
	debug_printf("User Task #0 SP=0x%x\n", &local);
	
	while(true)
	{
		KernelEventFlag_t handle_event = Kernel_wait_events(KernelEventFlag_UartIn|KernelEventFlag_CmdOut);
		switch(handle_event)
		{
			case KernelEventFlag_UartIn:
				debug_printf("\nEvent handled by Task0\n");
				Kernel_recv_msg(KernelMsgQ_Task0, &uartch, 1);
				if(uartch == '\r')
				{
					cmdBuf[cmdBufIdx] = '\0';
					/* 에러 처리 하기 전
					Kernel_send_msg(KernelMsgQ_Task1, &cmdBufIdx, 1);
					Kernel_send_msg(KernelMsgQ_Task1, cmdBug, cmdBufIdx);
					Kernel_send_events(KernelEventFlag_CmdIn);
					*/
					
					/* 에러 처리 한 후 */
					while(true)
					{
						Kernel_send_events(KernelEventFlag_CmdIn);
						if(false == Kernel_send_msg(KernelMsgQ_Task1, &cmdBufIdx, 1))
						{
							Kernel_yield();	// Task1이 메시지 큐를 비워주길 기다린다.
						}
						else if(false == Kernel_send_msg(KernelMsgQ_Task1, cmdBuf, cmdBufIdx))
						{
							uint8_t rollback;
							Kernel_recv_msg(KernelMsgQ_Task1, &rollback, 1); //★ Task1으로 부터 보낸 길이 정보를 빼낸다(돌려 받는다).
							Kernel_yield();
						}
						else
						{
							break;
						}
					}
					cmdBufIdx = 0;
				}
				else
				{
					cmdBuf[cmdBufIdx] =  uartch;
					cmdBufIdx++;
					cmdBufIdx %= 16;
				}
				break;
			case KernelEventFlag_CmdOut:
				debug_printf("\nCmdOut Event by Task0\n");
				break;				
		}
		Kernel_yield();
	}
}

void User_task1(void)
{
	uint32_t local = 0;
	
	//debug_printf("User Task #1\n");
	//while(true);
	
	/*
	while(true)
	{
		debug_printf("User Task #1 SP=0x%x\n", &local);
		Kernel_yield();
	}
	*/
	debug_printf("User Task #1 SP=0x%x\n", &local);
	uint8_t cmdlen = 0;
	uint8_t cmd[16] = {0};
	
	while(true)
	{
		KernelEventFlag_t handle_event = Kernel_wait_events(KernelEventFlag_CmdIn);
		switch(handle_event)
		{
			case KernelEventFlag_CmdIn:
				memclr(cmd, 16);
				Kernel_recv_msg(KernelMsgQ_Task1, &cmdlen, 1);
				Kernel_recv_msg(KernelMsgQ_Task1, cmd, cmdlen);
				debug_printf("\nRecv Cmd: %s\n", cmd);
				break;
		}
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
	
	//debug_printf("--------Chap7---------\n");
	debug_printf("SYSCTRL0 %x\n", *sysctrl0);
}

static void Timer_test(void)
{
	// while(true)
	// {
    //     debug_printf("current count : %u\n", Hal_timer_get_1ms_counter());
    //     delay(1000);		
	// }
	for(uint32_t i = 0; i < 5 ; i++)
    {
        debug_printf("current count : %u\n", Hal_timer_get_1ms_counter());
        delay(1000);
    }
}
