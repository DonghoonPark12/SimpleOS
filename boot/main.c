#include "stdint.h"
#include "../hal/HalUart.h"

#include "stdio.h"

static void Hw_init(void);

void main(){
  Hw_init();
  
  uint32_t i = 100;
  while(i--)
  {
    Hal_uart_put_char('N');  
  }
  Hal_uart_put_char('\n');
  
  putstr("Hellow World\n");
}

static void Hw_init(void)
{
    Hal_Uart_init();
}
