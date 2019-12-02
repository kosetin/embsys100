#include "../stm32f401xe.h"

void delay(int time);

void delay(int time)
{
  int counter = 0;
  while(counter++ < time);
}

// PROBLEM 1: Use the CMSIS to blink the user LED on the STM32 board.
int main()
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  
  GPIOA->MODER |= GPIO_MODER_MODE5_0;
  
  while(1)
  {
    const int time = 2000000;
    
    GPIOA->ODR |= GPIO_ODR_OD5;
    
    delay(time);
    
    GPIOA->ODR &= ~GPIO_ODR_OD5;
    
    delay(time); 
  }
  return 0;
}
