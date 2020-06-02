#include "stdint.h"
#include "Uart.h"
#include "../HalUart.h"

extern volatile PL011_t* Uart;

void Hal_uart_init()
{
  //Enable Uart
  Uart->uartcr.bits.UARTEN = 0;
  
