### 1. Using bit-band region for peripherals: ###

a. Convert the Blinking Led demo to use the corresponding bit-band address instead of the register address used in the peripheral region.

b. What instructions does the compiler produce in assembly for the “writing” to the GPIO bit when using bit-band address?
   
```assembly
								;     Bit-band alias base   GPIO		   GPIO5
   0x800'008c: 0x4d0b         LDR.N     R5, [PC, #0x2c]         ; 0x42400294 = 0x42000000 + 0x20014 * 32 + 5 * 4
   0x800'008e: 0x2001         MOVS      R0, #1
   0x800'0090: 0x6028         STR       R0, [R5]
```

c. What were the instructions produced when writing to the GPIOx_ODR bit[5] directly?
   
```assembly		
   0x800'0084: 0x4d0b         LDR.N     R5, [PC, #0x2c]         ; GPIOA_ODR
   0x800'0086: 0x6828         LDR       R0, [R5]
   0x800'0088: 0xf050 0x0020  ORRS.W    R0, R0, #32             ; 0x20
   0x800'008c: 0x6028         STR       R0, [R5]
```

### 2. Create a function with multiple arguments (5 arguments for example) and call that function from within another function. Trace thru the assembler and note: ###

a. How does the calling function pass the values to the called function?

	Before the function call with 5 parameters, 4 parameters are stored to R0-R3. 
	The 5th parameter is stored to the top of the stack. 
	In the body of the called function, the 5th parameter is loaded from the top of the stack to R4.`

b. What extra code did the compiler generate before calling the function with the multiple arguments?

```assembly
   0x800'1d6c: 0x2005         MOVS      R0, #5		; move the 5th parameter to R0
   0x800'1d6e: 0x9000         STR       R0, [SP]	; store the 5th parameter to the top of the stack
   0x800'1d70: 0x2304         MOVS      R3, #4		; store the 1-4th parameters to R0-R3
   0x800'1d72: 0x2203         MOVS      R2, #3
   0x800'1d74: 0x2102         MOVS      R1, #2
   0x800'1d76: 0x2001         MOVS      R0, #1		; Before the function call, 
							; 4 function parameters are in R0-R3 registers, 
							; the remaining parameter is on the top of the stack
```
	
c. What extra code did the compiler generate inside the called function with the multiple list of arguments?

```assembly
   0x800'1d40: 0xb430         PUSH      {R4, R5}
   0x800'1d42: 0x9c02         LDR       R4, [SP, #0x8]	; The fifth function parameter 
							; is loaded from the stack to R4	
```
   
d. Any other observations?

### 3. Following the queue data structure approach, design, implement and test a stack data structure: ###

a. The following is the list of requirements:
   
   i. The stack should have a predefined size
		
   ii. The stack supports “int” data types.
		
   iii. Provide a function to initialize the stack internals.

   iv. Provide a function to push an element onto the stack
	
   v. Provide a function to pop an element off the stack.
		
   vi. Provide a function that returns 1 if stack is empty.
		
   vii. Provide a function that returns 1 if stack is full.

b. Provide a list of the test cases and their implementation inside of main.c

c. Separate the stack code from the rest of the test code (create stack.h & stack.c)

### 4. Bonus: Using the power of pointers and type casting, create a function that can determine if a computer is big-endian or little-endian. Test your function in the simulator (Hint: modify the Project Options) against: ###

a. Device STM32F401RE

b. Cortex M4 (Little endian option)
   
c. Cortex M4 (Big Endian option)