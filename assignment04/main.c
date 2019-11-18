#include "stack.h"
#include <stdio.h>
#include <limits.h>
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

// PROBLEM 3: Design, implement and test a stack data structure
void RunStackTests(void);

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
  
  // PROBLEM 3: Test the stack data structure
  RunStackTests();
  
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

// PROBLEM 3: Test the stack data structure
void RunStackTests(void)
{
    int result1;
    int result2;
    int testInt;
    
    // *******************************************************************
    // Test1: Pop item from an empty stack
    // *******************************************************************
    // Arrange:
    result1 = 0;
    testInt = 0;
    stack_init();
    
    // Act:
    assert(1 == stack_isEmpty());
    result1 = stack_pop(&testInt);
      
    // Assert:
    assert(-1 == result1);
    assert(0 == testInt);
    
    
    // *******************************************************************
    // Test2: Pop an item from a non-empty stack
    // *******************************************************************
    // Arrange:
    result1 = 42;
    result2 = 42;
    testInt = 10;
    stack_init();
    
    // Act:
    result1 = stack_put(10);
    assert(1 != stack_isEmpty());
    assert(1 != stack_isFull());
    result2 = stack_pop(&testInt);
    
    // Assert:
    assert(0 == result1);
    assert(0 == result2);
    assert(10 == testInt);
    
    
    // *******************************************************************
    // Test3: Fill the stack, then get all items.
    // *******************************************************************
    // Arrange:
    testInt = 0;
    stack_init();
    assert(1 == stack_isEmpty());    
    assert(1 != stack_isFull());
    
    // Act:
    stack_put(-100);
    stack_put(-99);
    stack_put(-98);                                    
    
    // Assert:
    assert(1 == stack_isFull());
    assert(1 != stack_isEmpty());

    assert(0 == stack_pop(&testInt));
    assert(-98 == testInt);

    assert(0 == stack_pop(&testInt));
    assert(-99 == testInt);

    assert(0 == stack_pop(&testInt));
    assert(-100 == testInt);

    
    // *******************************************************************
    // Test4: Fill the stack, then put one more item, should fail
    // *******************************************************************
    // Arrange:
    testInt = 0;
    stack_init();
    
    // Act:
    stack_put(1001);
    stack_put(1002);
    stack_put(INT_MAX);
    
    // Assert:
    assert(-1 == stack_put(1));

    assert(0 == stack_pop(&testInt));
    assert(INT_MAX == testInt);

    assert(0 == stack_pop(&testInt));
    assert(1002 == testInt);

    assert(0 == stack_pop(&testInt));
    assert(1001 == testInt);

    assert(1 == stack_isEmpty());

    // ***********************************************************************
    // Test5: Fill the stack, retrieve one item, then add item, then retieve all
    // ***********************************************************************
    // Arrange:
    testInt = 0;
    stack_init();
    
    // Act:
    stack_put(INT_MIN);
    stack_put(2);
    stack_put(3);
    
    // Assert:
    assert(1 == stack_isFull());

    assert(0 == stack_pop(&testInt));
    assert(3 == testInt);
    
    assert(1 != stack_isFull());    

    assert(0 == stack_put(0));

    assert(0 == stack_pop(&testInt));
    assert(0 == testInt);

    assert(0 == stack_pop(&testInt));
    assert(2 == testInt);

    assert(0 == stack_pop(&testInt));
    assert(INT_MIN == testInt);
    

    // ***********************************************************************
    // Test6: Fill the stack and retrieve all items twice
    // ***********************************************************************
    // Arrange:
    testInt = 0;
    stack_init();
    
    // Act:
    stack_put(3);
    stack_put(2);
    stack_put(1);
    
    // Assert:
    assert(1 != stack_isEmpty());

    assert(0 == stack_pop(&testInt));
    assert(1 == testInt);

    assert(0 == stack_pop(&testInt));
    assert(2 == testInt);

    assert(0 == stack_pop(&testInt));
    assert(3 == testInt);
    
    assert(1 == stack_isEmpty());    

    assert(0 == stack_put(6));
    assert(0 == stack_put(5));
    assert(0 == stack_put(4));
    
    assert(1 == stack_isFull());    
    
    assert(-1 == stack_put(7));

    assert(0 == stack_pop(&testInt));
    assert(4 == testInt);

    assert(0 == stack_pop(&testInt));
    assert(5 == testInt);

    assert(0 == stack_pop(&testInt));
    assert(6 == testInt);
    
    assert(1 == stack_isEmpty());
}
