// PROBLEM 3: Implement a stack data structure
#include "stack.h"

// The stack should have a predefined size
#define STACK_SIZE 3

// The stack supports “int” data types
int StackStore[STACK_SIZE];

// Pointer to the top of the stack
int* top;

// LIFO Stack is Empty if top == StackStore;
int stack_isEmpty()
{
  return top == StackStore;
}

// LIFO Stack is Full if top == StackStore + STACK_SIZE;
int stack_isFull()
{
  return top == StackStore + STACK_SIZE;
}

// Initialize internals of the stack
void stack_init(void)
{
    top = StackStore;
}

// Add data to the stack
// If stack is full return error
// Otherwise return success
int stack_put(int data)
{   
    if (stack_isFull())
    {
        return -1;
    }
    *top = data;
    ++top;
    return 0;
}

// Pop data from the stack
// If stack is empty return error
// Otherwise return success
int stack_pop(int* data)
{   
    if (stack_isEmpty())
    {
        return -1;
    }
    --top;
    *data = *top;
    return 0;
}
