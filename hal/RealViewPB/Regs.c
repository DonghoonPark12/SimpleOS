#include "stdint.h"
#include "Uart.h"

volatile PL011_t* Uart = (PL001_t*)UART_BASE_ADDRESS0;

/*
Uart->uartdr.DATA = data & 0xFF;
if(Uart->uartde.FE || Uart->uartdr.PE || Uart->uartdr.BE || Uart->uartdr.OE){
  //error
}
*/
