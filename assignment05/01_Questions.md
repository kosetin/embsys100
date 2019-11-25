### <em>Problem 1: Create a function that allows swapping of two pointers</em> ###

a. Explain what the “main” function does to the CSTACK in order setup the input arguments prior to calling the swap_pointer() function?

   `The main function stores local variables on the stack. 
   It uses the STR instruction with the Stack Pointer as the base address and an immediate offset value to store the local variables on the stack. 
   The main function loads the addresses of input parameters to R0 and R1 using ADD instruction with SP as the base address and an immediate offset value.`

b. And what are the values in R0 & R1 when swap_pointer() is called?

   `R0 and R1 hold the addresses of the function input parameters in memory.

c. Share a screen shot of the local variables inside of “main” after the function swap_pointer() returns, showing the values of the pointers and what they are pointing to

<a href="#"><img src="https://github.com/kosetin/embsys100/blob/assets/assignment05/assignment_05_1.JPG" /></a>


### <em>Problems 2, 3 and 4: Run your program on the board, and capture a snapshot image of the output from TeraTerm</em> ###

<a href="#"><img src="https://github.com/kosetin/embsys100/blob/assets/assignment05/assignment_05_2.JPG" /></a>