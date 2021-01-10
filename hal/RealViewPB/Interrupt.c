#include "stdint.h"
#include "memio.h"
#include "Interrupt.h"
#include "HalInterrupt.h"
#include "armcpu.h"

extern volatile GicCput_t* GicCpu;
extern volatile GicDist_t* GicDist;

static InterHdlr_fptr sHandlers[INTERRUPT_HANDLER_NUM]; //Function pointer array

void Hal_interrupt_init(void)
{
	GicCpu->cpucontrol.bits.Enable = 1;
	GicCpu->prioritymask.bits.Prioritymask = GIC_PRIORITY_MASK_NONE; //0xF, Allow all of interrupt
	GicDist->distributorctrl.bits.Enable = 1;

	for(uint32_t i = 0; i<INTERRUPT_HANDLER_NUM; i++)
	{
		sHandlers[i] = NULL;
	}

	enable_irq();
}

void Hal_interrupt_enable(uint32_t interrupt_num)
{
	if( (interrupt_num < GIC_IRQ_START) || (GIC_IRQ_END < interrupt_num) )
	{
		return;
	}

	uint32_t bit_num = interrupt_num - GIC_IRQ_START;

	if(bit_num < GIC_IRQ_START) // e.g 44
	{
		SET_BIT(GicDist->setenable1, bit_num);
	}
	else						// e.g 70
	{
		bit_num -= GIC_IRQ_START;
		SET_BIT(GicDist->setenable2, bit_num);
	}
}

void Hal_interrupt_disable(uint32_t interrupt_num)
{
    if ((interrupt_num < GIC_IRQ_START) || (GIC_IRQ_END < interrupt_num))
    {
        return;
    }
	
    uint32_t bit_num = interrupt_num - GIC_IRQ_START;

    if (bit_num < GIC_IRQ_START)
    {
        CLR_BIT(GicDist->setenable1, bit_num);
    }
    else
    {
        bit_num -= GIC_IRQ_START;
        CLR_BIT(GicDist->setenable2, bit_num);
    }	
}

void Hal_interrupt_register_handler(InterHdlr_fptr handler, uint32_t interrupt_num)
{
	sHandlers[interrupt_num] = handler;
}

void Hal_interrupt_run_handler(void)
{
	uint32_t interrupt_num = GicCpu->interruptack.bits.InterruptID; /* Read from Interrupt acknowledge register, IRQ ID */

	if(sHandlers[interrupt_num] != NULL)
	{
		//함수 포인터 실행
		sHandlers[interrupt_num]();
	}
	//인터럽트 컨트롤러에 해당 인터럽트 처리가 끝났다는 것을 알려줌
	GicCpu->endofinterrupt.bits.InterruptID = interrupt_num;
}

