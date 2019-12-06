#include "stdint.h"
#include "delay.h"
#include "../assignment06/stm32f401xe.h"

#define SYS_CLOCK_HZ 16000000

void main(void)
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  
  GPIOA->MODER |= GPIO_MODER_MODE5_0;
     
  SysTick->LOAD = SYS_CLOCK_HZ - 1;
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk 
                | SysTick_CTRL_TICKINT_Msk 
                | SysTick_CTRL_ENABLE_Msk;
  SysTick->VAL = 0;
  
  while(1)
  {
    // SysTick interrupt handler blinks the LED!
  }
}
