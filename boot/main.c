#include "stdint.h"
#include "../hal/HalUart.h"

static void Hw_init(void);

void main(){
  Hw_init();
  
  uint32_t i = 100;
  while(i--)
  {
    Hal_uart_put_char('N');  
  }
}

static void Hw_init(void)
{
    Hal_Uart_init();
}
