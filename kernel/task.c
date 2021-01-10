/*
 * task.c
 *
 *  Created on: Jan 10, 2021
 *      Author: dhpark
 */
 
#include "stdint.h"
#include "stdbool.h"

#include "ARMv7AR.h"
#include "task.h"

static KernelTcb_t  sTask_list[MAX_TASK_NUM];
static KernelTcb_t* sCurrent_tcb;
static KernelTcb_t* sNext_tcb;

static uint32_t     sAllocated_tcb_index;
static uint32_t     sCurrent_tcb_index;

void Kernel_task_init(void)
{
    sAllocated_tcb_index = 0;
    sCurrent_tcb_index = 0;
    
    for(uint32_t i = 0; i < MAX_TASK_NUM; i++)
    {
       // sFree_task_pool[i].spsr = ARM_MODE_BIT_SYS;
       // sFree_task_pool[i].lr = 0;
       // sFree_task_pool[i].pc = 0;
        
        // 스택 베이스 주소를 USR_STACK_SIZE 크기 만큼 늘려가며 설정
        sTask_list[i].stack_base = (uint8_t*)(TASK_STACK_START + (i * USR_STACK_SIZE));
        // 스택 포인터 항당, 스택 포인터는 USR_TASK_STACK_SIZE 끝부분에서 시작한다.
        sTask_list[i].sp = (uint32_t)sTask_list[i].stack_base + USR_TASK_STACK_SIZE - 4;
        
        //해당 OS는 '테스크 컨택스트'를 테스크 Stack에 저장.
        // '테스크 컨택스트'를 다른 곳에 저장해도 된다.
        sTack_list[i].sp -= sizeof(KernelTaskContext_t);
     
        //[Optional] SimpleOS 만의 구조. 테스크 스택안에, 테스크 컨택스트가 같이 들어가 있다.
        KernelTaskContext_t* ctx = (KernelTaskContext_t*)sTask_list[i].sp;
        ctx->pc = 0;
        ctx->spsr = ARM_MODE_BIT_SYS;
    }
}

/*
    테스크로 동작할 함수를 TCB에 등록
*/
uint32_t Kernel_task_create(KernelTaskFunc_t startFunc)
{
    KernelTcb_t* new_tcb = &sTask_list[sAllocated_tcb_index++];
    
    if (sAllocated_tcb_index > MAX_TASK_NUM)
    {
        return NOT_ENOUGH_TASK_NUM;
    }
    
    //new_tcb->pc = (uint32_t)startFunc;
    
    // 현재 테스트 스택에 저장되어 있는 테스크 컨텍스트 주소 포인트(SP)를 가져오는 코드
    KernelTaskContext_t* ctx = (KernelTaskContext_t*)new_tcb->sp;
    // 함수 시작주소를 PC에 넣어준다
    ctx->pc = (uint32_t)startFunc;
    
    return (sAllocated_tcb_index - 1);
}
