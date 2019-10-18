<style type="text/css">
    ol ol { list-style-type: upper-alpha; }
</style>
<ol type="1">
  <li>Inject 0x1FFFFFFF for the “counter” value in the variable window, then step thru the program only once to increment “counter”.
    <ol type="a"> 
      <li>What is the value of the “counter” from the “Locals” window?</li>
      <li>What is the value of the “counter” in the “Register” window?</li>
      <li>Which flags are set in the APSR register? Explain why?</li>
    </ol>
  </li>
  <li>If your write all Fs (0XFFFFFFFF) in the Register value for “counter” then step thru the program once to increment “counter”
    <ol type="a">
       <li>What happens to the value of “counter” in the “Locals” window?</li>
       <li>What flags, if any, are set in the APSR?</li>
    </ol>

3. Change the “counter” variable type in your code to “unsigned”. Inject the values “0x1FFFFFFF” then step thru the program to increment the “counter” once:

a) What is the value of “counter” in the “Locals” window after incrementing for each value?
b) What flags, if any, are set in the APSR? Explain why?

4. Change the “counter” variable type in your code to “unsigned”. Inject the values “0xFFFFFFFF” then step thru the program to increment the “counter” once:

a) What is the value of “counter” in the “Locals” window after incrementing for each value?
b) What flags, if any, are set in the APSR? Explain why?

5. Move the “counter’ variable outside of main (at the top of the file):

a) What is the scope of the variable “counter”?
b) Is it still visible in the “Locals” view?
c) In which window view can we track “counter” now?
d) What is the address of the “counter” variable in memory?

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

a) What is the value of “counter” at the end of the program (halting at the return 0 statement)
b) Explain why the counter value has changed?

7. Change the setting of IAR to run the same program on the evaluation board:

a) What is the address where “counter” is stored?
b) Is the “counter” variable stored in RAM or ROM?
c) What is the value of “counter” at the end of the program (halting at the return 0
statement).
</ol>
