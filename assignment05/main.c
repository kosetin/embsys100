/*******************************************************************************
FILE NAME   : main.c
DESCRIPTION : Where all the magic begins.
	      

Copyright   : David Allegre
            : 2015
	    : All Rights Reserved
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "nucleoboard.h"
#include "hw_init.h"
#include "print.h"
#include <string.h>
#include <stdlib.h>

char clr_scrn[] = { 27, 91, 50, 74, 13, 10, 0 };              // esc[2J
/* Public variables ----------------------------------------------------------*/
__IO uint32_t timer;
PRINT_DEFINEBUFFER();           /* required for lightweight sprintf */
/* Private prototype ---------------------------------------------------------*/

extern int sqrAsm(int);
extern int div2Asm(int);
extern int swapCharsAsm(char* char0, char* char1);
void swapPointers(void* ptr0, void* ptr1, size_t size);

// PROBLEM 1: Create a function that allows swapping of two pointers
void swapPointers(void* ptr0, void* ptr1, size_t size)
{
  void* tmp = malloc(size);
  memmove(tmp, ptr0, size);
  memmove(ptr0, ptr1, size);
  memmove(ptr1, tmp, size);
}

enum {BUFFER_SIZE = 100};
char myCstr[BUFFER_SIZE];
/*******************************************************************************
Function Name   : main
Description     : 
Parameters      :
Return value    :               */
void main() {

  Hw_init();

  PrintString(clr_scrn); /* Clear entire screen */
  
  snprintf(myCstr, BUFFER_SIZE, "%s", "Konstantin's Nucleo STM32401RE is alive ...");
  PrintString(myCstr);
  
  int a = 8;
  int b = 10;
  
  int* ptrA = &a;
  int* ptrB = &b;
  
  long c = 789L;
  long d = 1001L;
  
  long* ptrC = &c;
  long* ptrD = &d;
  
  char aLhs[] = {'a', 'G'};
  char aRhs[] = {'z', 'G'};
  
  snprintf(myCstr, BUFFER_SIZE, "\n\n%s", "Using swapPointers: ");
  PrintString(myCstr);
  
  snprintf(myCstr, BUFFER_SIZE, "\nBefore: LHS='%p', RHS='%p'", ptrA, ptrB);
  PrintString(myCstr);

  swapPointers(&ptrA, &ptrB, sizeof(ptrA));
    
  snprintf(myCstr, BUFFER_SIZE, "\n After: LHS='%p', RHS='%p'", ptrA, ptrB);
  PrintString(myCstr);
  
  snprintf(myCstr, BUFFER_SIZE, "\nBefore: LHS='%p', RHS='%p'", ptrC, ptrD);
  PrintString(myCstr);

  swapPointers(&ptrC, &ptrD, sizeof(ptrC));
    
  snprintf(myCstr, BUFFER_SIZE, "\n After: LHS='%p', RHS='%p'", ptrC, ptrD);
  PrintString(myCstr);
  
  snprintf(myCstr, BUFFER_SIZE, "\nBefore: LHS='%p', RHS='%p'", ptrA, ptrD);
  PrintString(myCstr);

  swapPointers(&ptrA, &ptrD, sizeof(ptrD));
    
  snprintf(myCstr, BUFFER_SIZE, "\n After: LHS='%p', RHS='%p'", ptrA, ptrD);
  PrintString(myCstr);
  
  snprintf(myCstr, BUFFER_SIZE, "\nBefore: LHS='%p', RHS='%p'", aLhs, aRhs);
  PrintString(myCstr);

  // Does not work with pointers to arrays of chars
  swapPointers(&aLhs, &aRhs, sizeof(aLhs));
    
  snprintf(myCstr, BUFFER_SIZE, "\n After: LHS='%p', RHS='%p'", aLhs, aRhs);
  PrintString(myCstr);
  
  // PROBLEM 2: Run sqrAsm code from the class demo
  snprintf(myCstr, BUFFER_SIZE, "\n\n%s", "Using sqrAsm: ");
  PrintString(myCstr);
  const int aValues[] = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 10, 100};

  for( size_t index = 0; index < sizeof(aValues)/sizeof(aValues[0]); ++index) 
  { 
    const int value = aValues[index];
    snprintf(myCstr, BUFFER_SIZE, "\n%3d squared is ", value);
    const int square = sqrAsm(value);
    
    snprintf(myCstr, BUFFER_SIZE, "%5d", square);
    PrintString(myCstr);
  }
  
  // PROBLEM 3: Create a new file div2Asm.s and run div2Asm code from the class demo
  snprintf(myCstr, BUFFER_SIZE, "\n\n%s", "Using div2Asm: ");
  PrintString(myCstr);
  const int aDivValues[] = {-100, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 10, 101};

  for( size_t index = 0; index < sizeof(aDivValues)/sizeof(aDivValues[0]); ++index) 
  { 
    const int value = aDivValues[index];
    snprintf(myCstr, BUFFER_SIZE, "\n%4d divided by 2 is ", value);
    const int square = div2Asm(value);
    
    snprintf(myCstr, BUFFER_SIZE, "%5d", square);
    PrintString(myCstr);
  }

  // PROBLEM 4: Implement a swap function in assembly and call it “swapCharsAsm”:
  snprintf(myCstr, BUFFER_SIZE, "\n\n%s", "Using swapCharsAsm: ");
  PrintString(myCstr);

  for( size_t index = 0; index < sizeof(aLhs)/sizeof(aLhs[0]); ++index) 
  {   
    snprintf(myCstr, BUFFER_SIZE, "\nBefore: LHS='%c', RHS='%c'", aLhs[index], aRhs[index]);
    int isNotEqual = swapCharsAsm(aLhs+index, aRhs+index);
    
    snprintf(myCstr, BUFFER_SIZE, "\n After: LHS='%c', RHS='%c'", aLhs[index], aRhs[index]);
    PrintString(myCstr);
    
    snprintf(myCstr, BUFFER_SIZE, "\nLHS equals RHS: %s", isNotEqual ? "false" : "true");
    PrintString(myCstr);
  }
  
  while(1)
  {
  }
}

void SystemInit(void) {
  // System init is called from the assembly .s file
  // We will configure the clocks in hw_init
  asm("nop");
}