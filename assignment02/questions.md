1. *Inject **0x7FFFFFFF** for the “counter” value in the variable window, then step thru the program only once to increment “counter”*.

   *a. What is the value of the “counter” from the “Locals” window?*

	`0x80000000 corresponding to a signed int value of -2147483648 in decimal.`

   *b. What is the value of the “counter” in the “Register” window?*

	`The same - 0x80000000 or -2147483648 in signed int decimal.`

   *c. Which flags are set in the APSR register? Explain why?*

	`N and V flags are set because the ADDS instruction results in setting the sign bit, which corresponds
to a sign overflow from 2147483647 to -2147483648 in decimal when the value is a signed int.`

2. *If your write all Fs (0XFFFFFFFF) in the Register value for “counter” then step thru the program once to increment “counter”*

   *a. What happens to the value of “counter” in the “Locals” window?*

	`counter becomes zero`

   *b. What flags, if any, are set in the APSR?*

	`Z flag is set because the result of ADDS instruction is zero. C flag is set because incrementing the value 0xFFFFFFFF overflows the 32-bit register.`

3. *Change the “counter” variable type in your code to “unsigned”. Inject the values “**0x7FFFFFFF**” then step thru the program to increment the “counter” once:*

   *a. What is the value of “counter” in the “Locals” window after incrementing for each value?*

	`0x80000000 corresponding to an unsigned int value of 2147483648 in decimal.`

   *b. What flags, if any, are set in the APSR? Explain why?*

	`N and V flags are set because the ADDS instruction results in setting the sign bit.`

4. *Change the “counter” variable type in your code to “unsigned”. Inject the values “0xFFFFFFFF” then step thru the program to increment the “counter” once:*

   *a. What is the value of “counter” in the “Locals” window after incrementing for each value?*

	`0x00000000`

   b. *What flags, if any, are set in the APSR? Explain why?*

	`Z flag is set because the result of ADDS instruction is zero. C flag is set because incrementing the value 0xFFFFFFFF overflows the 32-bit register.`

5. *Move the “counter’ variable outside of main (at the top of the file):*

   *a. What is the scope of the variable “counter”?*

	`File scope`

   *b. Is it still visible in the “Locals” view?*

	`No`

   *c. In which window view can we track “counter” now?*

	`In Watch view`

   *d. What is the address of the “counter” variable in memory?*

	`0x20000000`

6. *Change the source code to the following, then run the program still in the simulator:*

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


   a. *What is the value of “counter” at the end of the program (halting at the return 0 statement)*

	4

   b. *Explain why the counter value has changed?*

	The local variable p\_int is assigned the memory address of the global counter variable. Incrementing the value pointed to by p_int results in incrementing the value stored at the memory address holding the counter value (3 times). The final post-increment operation on the counter increments the counter value one more time.

7. *Change the setting of IAR to run the same program on the evaluation board:*

   a. *What is the address where “counter” is stored?*
		
	`0x20000000`

   b. *Is the “counter” variable stored in RAM or ROM?*

	Table 2-11 "Memory access behavior" in Section 2.2.3 Behavior of memory accesses of the <a href="http://infocenter.arm.com/help/topic/com.arm.doc.dui0553b/DUI0553.pdf">Cortex-M4 Devices Generic User Guide</a> states that direct access to 0x20000000 address behaves as SRAM memory access. The counter variable is stored in RAM then. 

   c. What is the value of “counter” at the end of the program (halting at the return 0 statement).

	`4`
