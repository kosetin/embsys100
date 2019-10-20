1. Inject 0x1FFFFFFF for the “counter” value in the variable window, then step thru the program only once to increment “counter”.

   a. What is the value of the “counter” from the “Locals” window?

	0x20000000

   b. What is the value of the “counter” in the “Register” window?

	0x20000000

   c. Which flags are set in the APSR register? Explain why?

	No flags are set because the resulting value of the counter is a positive (N flag not set), non-zero (Z flag not set) value that fits into the signed int range (C and V flags are not set).

2. If your write all Fs (0XFFFFFFFF) in the Register value for “counter” then step thru the program once to increment “counter”

   a. What happens to the value of “counter” in the “Locals” window?

	counter becomes zero

   b. What flags, if any, are set in the APSR?

	Z flag is set because the result of ADDS instruction is zero. C flag is set because incrementing the value 0xFFFFFFFF overflows the 32-bit register but does not wrap the decimal value around (V flag is not set).

3. Change the “counter” variable type in your code to “unsigned”. Inject the values “0x1FFFFFFF” then step thru the program to increment the “counter” once:

   a. What is the value of “counter” in the “Locals” window after incrementing for each value?

	0x20000000

   b. What flags, if any, are set in the APSR? Explain why?

	No flags are set because the resulting value of the counter is a positive (N flag not set), non-zero (Z flag not set) value that fits into the unsigned int range (C and V flags are not set).

4. Change the “counter” variable type in your code to “unsigned”. Inject the values “0xFFFFFFFF” then step thru the program to increment the “counter” once:

   a. What is the value of “counter” in the “Locals” window after incrementing for each value?

	0x00000000

   b. What flags, if any, are set in the APSR? Explain why?

	Z flag is set because the result of ADDS instruction is zero. C flag is set because incrementing the value 0xFFFFFFFF overflows the 32-bit register.

5. Move the “counter’ variable outside of main (at the top of the file):

   a. What is the scope of the variable “counter”?

	File scope

   b. Is it still visible in the “Locals” view?

	No

   c. In which window view can we track “counter” now?

	In Watch view

   d. What is the address of the “counter” variable in memory?

	0x20000000

6. Change the source code to the following, then run the program still in the simulator:
```c
int counter = 0x0;

int main() {
  int *p_int = (int *)0x20000000;
  ++(*p_int);
  ++(*p_int);
  ++(*p_int);
  counter ++;
  return 0;
}
```

   a. What is the value of “counter” at the end of the program (halting at the return 0 statement)

	4

   b. Explain why the counter value has changed?

	The local variable p\_int is assigned the address of the counter in memory. Incrementing the value pointed to by p\_int results in incrementing the value stored at the memory address holding the counter value (3 times). The final post-increment operation on the counter increments the counter value one more time.

7. Change the setting of IAR to run the same program on the evaluation board:

   a. What is the address where “counter” is stored?

   b. Is the “counter” variable stored in RAM or ROM?

   c. What is the value of “counter” at the end of the program (halting at the return 0
statement).
