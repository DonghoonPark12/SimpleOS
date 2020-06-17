#include "stdint.h"
#include "../hal/HalUart.h"

#include "stdio.h"

static void Hw_init(void);
static void Printf_test(void);

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
  
	while(1);

  i = 100;
  while(i--)
  {
      uint8_t ch = Hal_uart_get_char();
      Hal_uart_put_char(ch);
  }
}

static void Hw_init(void)
{
    Hal_uart_init();
}

static void Printf_test(void)
{
	char* str = "printf pointer test";
	char* nullptr = 0;
	uint32_t i = 5;

	debug_printf("%s\n", "Hello printf");
	debug_printf("output string pinter: %s\n", str);
	debug_printf("%s is numm pointer, %u number\n", nullptr, 10);
	debug_printf("%u = 5\n", i);
	debug_printf("dec = %u hex=%x\n", 0xff, 0xff);
	debug_printf("print zeroo %u\n", 0);
}