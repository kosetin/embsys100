#include "stdint.h"
#include "subscriber.h"
#include "../../assignment06/stm32f401xe.h"

#define SYS_CLOCK_HZ 16000000
#define MSEC SYS_CLOCK_HZ/1000-1

void SysTick_Init(void);
void LED_Init(void);
void Toggle_LED(void);

void delay(uint32_t delayInMilliseconds, void (*callback)(void));

void SysTick_Init(void)
{
  // After reset, the CPU clock frequency is 16 MHz (RM0368)
  SysTick->LOAD = MSEC;
  SysTick->VAL = 0;
  SysTick->CTRL =  SysTick_CTRL_CLKSOURCE_Msk
                 | SysTick_CTRL_TICKINT_Msk 
                 | SysTick_CTRL_ENABLE_Msk;
}

void LED_Init(void)
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  
  GPIOA->MODER |= GPIO_MODER_MODE5_0;
}

void Toggle_LED(void)
{
  GPIOA->ODR ^= GPIO_ODR_OD5;
}

void delay(uint32_t delayInMilliseconds, void (*callback)(void))
{
  TSubscriber * subscr = Register_Subscriber_SysTick();
  if (subscr)
  {
    subscr->threshold = delayInMilliseconds;
    subscr->current = delayInMilliseconds;
    subscr->callback = callback;
  }
}

void main(void)
{
  LED_Init();
     
  SysTick_Init();
  
  delay(2000, Toggle_LED);
  
  while(1)
  {
    // Event Loop
  }
}
