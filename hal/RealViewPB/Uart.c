#include "stdint.h"
#include "Uart.h"
#include "../HalUart.h"
#include "../HalInterrupt.h"

extern volatile PL011_t* Uart;

static void interrupt_handler(void);

void Hal_uart_init()
{
  //Enable Uart
  Uart->uartcr.bits.UARTEN = 0;
  Uart->uartcr.bits.TXE = 1;
  Uart->uartcr.bits.RXE = 1;
  Uart->uartcr.bits.UARTEN = 1;

  // Enable Input interrupt
  Uart->uartimsc.bits.RXIM = 1;

  // Register UART interupt handler
  Hal_interrupt_enable(UART_INTERRUPT0);
  Hal_interrupt_resiget_handler(interrupt_handler, UART_INTERRUPT0);
};

void Hal_uart_put_char(uint8_t ch)
{
  while(Uart->uartfr.bits.TXFF); /* Wait until output buffer size 0 */ 
  Uart->uartdr.all = (ch & 0xFF);
}

uint8_t Hal_uart_get_char(void)
{
    uint32_t data;
    while(Uart->uartfr.bits.RXFE);
  
    data = Uart->uartdr.all;
    //Check error flag
    if(data & 0xFFFFFF00) // 0x00000F00
    {
        //Clear the error
        Uart->uartsr.all = 0xFF; //0x0000000F
        return 0;
    }
      
    return (uint8_t)(data & 0xFF);
}

static void interrupt_handler(void)
{
  uint8_t ch = Hal_uart_get_char();
  Hal_uart_put_char(ch);
}

// uint8_t Hal_uart_get_char(void)
// {
// 	uint8_t data;

// 	while(Uart->uartfr.bits.RXFE);

// 	//Check for an error flag
// 	if(Uart->uartdr.bits.BE || Uart->uartdr.bits.FE ||
// 	   Uart->uartdr.bits.OE || Uart->uartdr.bits.PE)
// 	{
// 		// Clear the error
// 		Uart->uartsr.bits.BE = 1;
// 		Uart->uartsr.bits.FE = 1;
// 		Uart->uartsr.bits.OE = 1;
// 		Uart->uartsr.bits.PE = 1;
// 		return 0;
// 	}

// 	data = Uart->uartdr.bits.DATA;
// 	return data;
// }