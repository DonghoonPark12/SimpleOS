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

#include "MemoryMap.h"

static KernelTcb_t  sTask_list[MAX_TASK_NUM];
static KernelTcb_t* sCurrent_tcb;
static KernelTcb_t* sNext_tcb;

static uint32_t     sAllocated_tcb_index; //테스크 크기 
static uint32_t     sCurrent_tcb_index;

static void Save_context(void);
static void Restore_context(void);
static KernelTcb_t* Scheduler_round_robin_algorithm(void);
static KernelTcb_t* Scheduler_priority_algorithm(void);

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
        sTask_list[i].stack_base = (uint8_t*)(TASK_STACK_START + (i * USR_TASK_STACK_SIZE));
        // 스택 포인터 항당, 스택 포인터는 USR_TASK_STACK_SIZE 끝부분에서 시작한다.
        sTask_list[i].sp = (uint32_t)sTask_list[i].stack_base + USR_TASK_STACK_SIZE - 4;
        
        //해당 OS는 '테스크 컨택스트'를 테스크 Stack에 저장.
        // '테스크 컨택스트'를 다른 곳에 저장해도 된다.
        sTask_list[i].sp -= sizeof(KernelTaskContext_t);
     
        //[Optional] SimpleOS 만의 구조. 테스크 스택안에, 테스크 컨택스트가 같이 들어가 있다.
        KernelTaskContext_t* ctx = (KernelTaskContext_t*)sTask_list[i].sp;
        ctx->pc = 0;
        ctx->spsr = ARM_MODE_BIT_SYS;
    }
}

/*
    커널 시작할 때 한번만 호출되는 함수
    sCurrent_tcb_index는 '0'이어야 한다.
*/
void Kernel_task_start(void)
{
    sNext_tcb = &sTask_list[sCurrent_tcb_index];
    //스케줄러 호출 생략. e.g. sNext_tcb = Scheduler_round_robin_algorithm();
    Restore_context();
}

/*
    테스크로 동작할 함수를 TCB에 등록
*/
uint32_t Kernel_task_create(KernelTaskFunc_t startFunc, uint32_t priority)
{
    KernelTcb_t* new_tcb = &sTask_list[sAllocated_tcb_index++];
    
    if (sAllocated_tcb_index > MAX_TASK_NUM)
    {
        return NOT_ENOUGH_TASK_NUM;
    }
    
    //new_tcb->pc = (uint32_t)startFunc;
    new_tcb->priority = priority;
 
    // 현재 테스트 스택에 저장되어 있는 테스크 컨텍스트 주소 포인트(SP)를 가져오는 코드
    KernelTaskContext_t* ctx = (KernelTaskContext_t*)new_tcb->sp;
    // 함수 시작주소를 PC에 넣어준다
    ctx->pc = (uint32_t)startFunc;
    
    return (sAllocated_tcb_index - 1);
}

void Kernel_task_scheduler(void)
{
    sCurrent_tcb = &sTask_list[sCurrent_tcb_index];
    sNext_tcb = Scheduler_round_robin_algorithm();
    
    //disable_irq();
    Kernel_task_context_switching();
    //enable_irq();
}

__attribute__ ((naked)) void Kernel_task_context_switching(void)
{
    __asm__ ("B Save_context");
    __asm__ ("B Restore_context");
}

static __attribute__ ((naked)) void Save_context(void)
{
    // save current task context into the current task stack
    __asm__("PUSh  {lr}");     //LR을 스택에 푸시, LR은 KernelTaskContext_t의 pc 멤버 변수에 저장된다(?)
    __asm__("PUSH  {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}"); //범용 레지스터 스택에 푸시
    __asm__ ("MRS  r0, cpsr"); // cpsr을 KernelTaskContext_t의 spsr 멤버 변수 위치에 저장(?)
    __asm__ ("PUSH {r0}");        
    // save current task stack pointer into the current TCB
    __asm__ ("LDR   r0, =sCurrent_tcb"); // 현재 동작중인 TCB의 포인터 변수를 읽어 들인다.
    __asm__ ("LDR   r0, [r0]"); //포인터에 저장된 값을 읽는다.
    __asm__ ("STMIA r0!, {sp}"); //위의 라인에서 읽은 값을 베이스 메모리 주소로 해서, SP를 저장한다.
                                 //sCurrent->sp ='ARM_코너_SP_레지스터값' 과 동일 의미
}

static __attribute__ ((naked)) void Restore_context(void)
{
    // restore next task stack pointer from the next TCB
    __asm__ ("LDR   r0, =sNext_tcb"); //TCB의 sp 멤버 변수 값을 읽어 ARM 코어의 SP에 값을 쓰는 작업
    __asm__ ("LDR   r0, [r0]");
    __asm__ ("LDMIA r0!, {sp}");
    // restore next task context from the next task stack
    __asm__ ("POP  {r0}");            //스택에 저장되어 있는 cpsr의 값을 꺼내서, ARM의 CPSR에 값을 쓰는 작업
    __asm__ ("MSR   cpsr, r0");
    __asm__ ("POP  {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}");
    __asm__ ("POP  {pc}");
}

static KernelTcb_t* Scheduler_round_robin_algorithm(void)
{
    sCurrent_tcb_index++;
    sCurrent_tcb_index %= sAllocated_tcb_index;
    
    return &sTask_list[sCurrent_tcb_index];
}

static KernelTcb_t* Scheduler_priority_algorithm(void)
{
    for(uint32_t i = 0; i < sAllocated_tcb_index; i++)
    {
        KernelTcb_t* pNextTcb = &sTask_list[i];
        if(pNextTcb != sCurrent_tcb)
        {
            //숫자가 작은 것이 우선순위가 낮다.
            if(pNextTcb->priority <= sCurrent_tcb->priority)
            {
                return pNextTcb;   
            }
        }
    }
    return sCurrent_tcb;
}
