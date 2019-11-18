// PROBLEM 3: Design a stack data structure

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STACK_H__
#define __STACK_H__

// A function to initialize the stack internals
void stack_init(void);

// A function to push an element onto the stack
int stack_put(int data);

// A function to pop an element off the stack
int stack_pop(int* data);

// A function that returns 1 if stack is empty
int stack_isEmpty(void);

// A function that returns 1 if stack is full
int stack_isFull(void);

#endif
