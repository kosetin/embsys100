<ol>
<li>*Using bit-band region for peripherals:*<li>

   a. Convert the Blinking Led demo to use the corresponding bit-band address instead of the register address used in the peripheral region.

   b. What instructions does the compiler produce in assembly for the “writing” to the GPIO bit when using bit-band address?
   
```assembly
   0x800'008c: 0x4d0b         LDR.N     R5, [PC, #0x2c]         ; 0x4240'0294
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
</ol>
2. *Create a function with multiple arguments (5 arguments for example) and call that function from within another function. Trace thru the assembler and note:*

   a. How does the calling function pass the values to the called function?

	` `

   b. What extra code did the compiler generate before calling the function with the multiple arguments?

	` `
	
   c. What extra code did the compiler generate inside the called function with the multiple list of arguments?
   
   d. Any other observations?

3. *Following the queue data structure approach, design, implement and test a stack data structure:*

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

4. *Bonus: Using the power of pointers and type casting, create a function that can determine if a computer is big-endian or little-endian. Test your function in the simulator (Hint: modify the Project Options) against:*

   a. Device STM32F401RE

   b. Cortex M4 (Little endian option)
   
   c. Cortex M4 (Big Endian option)