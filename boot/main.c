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
  
  Printf_test();
  
  i = 100;
  while(i--)
  {
      uint8_t ch = Hal_uart_get_char();
    Hal_uart_put_char();
  }
}

static void Hw_init(void)
{
    Hal_Uart_init();
}

static void Printf_test(void)
{
    /*...*/ 
}
