#include <stdio.h>
#include <assert.h>

// Bit-band Alias Base Address:
#define BIT_BAND_ALIAS_BASE 0x42000000

#define BIT_BAND_ALIAS(reg) (((BIT_BAND_ALIAS_BASE) + (((reg) - BIT_BAND_BASE) * 32)))
#define SET_BIT(alias, bit) (*((unsigned int*)((alias) + ((bit) * 4))) = 0x1)
#define RESET_BIT(alias, bit) (*((unsigned int*)((alias) + ((bit) * 4))) = 0x0)

// Bit-band Base Address:
#define BIT_BAND_BASE 0x40000000

// RCC Base Address:
#define RCC_BASE 0x40023800

// RCC AHB1 peripheral clock enable register (RCC_AHB1ENR): 
//      address offset: 0x30
#define RCC_AHB1ENR (*((unsigned int*)(RCC_BASE + 0x30)))
#define RCC_AHB1ENR_BIT_BAND_ALIAS BIT_BAND_ALIAS(RCC_BASE + 0x30)

// GPIOA Base Address
#define GPIOA_BASE 0x40020000

// GPIO port mode register (GPIOx_MODER) (x = A..E and H): 
//      address offset: 0x00
#define GPIOA_MODER (*((unsigned int*)(GPIOA_BASE + 0x00)))
#define GPIOA_MODER_BIT_BAND_ALIAS BIT_BAND_ALIAS(GPIOA_BASE + 0x00)

// GPIO port output data register (GPIOx_ODR) (x = A..E and H): 
//      address offset: 0x14
#define GPIOA_ODR (*((unsigned int*)(GPIOA_BASE + 0x14)))
#define GPIOA_ODR_BIT_BAND_ALIAS BIT_BAND_ALIAS(GPIOA_BASE + 0x14)

#define GPIOA (1<<5)

volatile int counter=0;
int flags[5] = {0};

int isLittleEndian(void); 
void delay(int delay);
void setFlags(int arg1, int arg2, int arg3, int arg4, int arg5);

// PROBLEM 2: Create a function with multiple arguments (e.g. 5 arguments) 
//            and call that function from within another function.
void setFlags(int arg1, int arg2, int arg3, int arg4, int arg5)
{
  flags[0] = arg1;
  flags[1] = arg2;
  flags[2] = arg3;
  flags[3] = arg4;
  flags[4] = arg5;
}

void delay(int delay)
{
  counter=0;
  while (counter < delay)
  {
     counter++;
  }
  
  // PROBLEM 2: Call a function with multiple arguments from within another function.
  setFlags(1, 2, 3, 4, 5);
}

// PROBLEM 4 (BONUS): create a function that can determine if a computer is big-endian or little-endian.
int isLittleEndian() 
{
  int probe = 0x1;
  char * lsb = (char*)&probe;
  int isLittleEndian = *lsb == 0x1;
  assert(isLittleEndian == __LITTLE_ENDIAN__);
  return isLittleEndian;
}

void main(void)
{
  // PROBLEM 4 (BONUS): create a function that can determine if a computer is big-endian or little-endian.
  printf("The system is %s!\n", isLittleEndian() ? "little-endian" : "big-endian");
    
  // PROBLEM 1: Use bit-band region for peripherals:
  {    
    // 1. Enable clock to Peripheral - set bit[0] to 1
    SET_BIT(RCC_AHB1ENR_BIT_BAND_ALIAS, 0);
 
    // 2. Enable Port5 as output - set bit[11:10] to 0x01
    RESET_BIT(GPIOA_MODER_BIT_BAND_ALIAS, 11);
    SET_BIT(GPIOA_MODER_BIT_BAND_ALIAS, 10);
 
    while(1)
    {        
        // 3a. Turn LED ON - set bit[5] to 1
        //GPIOA_ODR |= GPIOA;
        //*((unsigned int*)((0x42000000) + (0x20014 * 32) + (5 * 4))) = 0x1;
        SET_BIT(GPIOA_ODR_BIT_BAND_ALIAS, 5);

        delay(1000000);
        
        // 3b. Turn LED OFF - set bit[5] to 0
        //GPIOA_ODR &= ~GPIOA;
        //*((unsigned int*)((0x42000000) + (0x20014 * 32) + (5 * 4))) = 0x0;
        RESET_BIT(GPIOA_ODR_BIT_BAND_ALIAS, 5);
 
        delay(1000000);
    }
  }
}
