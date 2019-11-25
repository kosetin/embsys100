/*******************************************************************************
File name       : swapCharsAsm.s
Description     : Assembly language function for swapping two chars
*******************************************************************************/   

    EXTERN PrintString  // PrintString is defined outside this file.
    EXTERN myCstr       // myCstr defined outside this file.
    
    PUBLIC swapCharsAsm       // Exports symbols to other modules
                              // Making swapCharsAsm available to other modules.
    
// Code is split into logical sections using the SECTION directive.
// Source: http://ftp.iar.se/WWWfiles/arm/webic/doc/EWARM_AssemblerReference.ENU.pdf
// SECTION  section  :type [:flag] [(align)]
//      The data section is used for declaring initialized data or constants. This data does not change at runtime
//      The bss section is used for declaring variables. The syntax for declaring bss section is -
//      The text section is used for keeping the actual code.

// CODE: Interprets subsequent instructions as Arm or Thumb instructions, 
// depending on the setting of related assembler options.

// NOREORDER (the default mode) starts a new fragment in the section
// with the given name, or a new section if no such section exists.
// REORDER starts a new section with the given name.

// NOROOT means that the section fragment is discarded by the linker if
// no symbols in this section fragment are referred to. Normally, all
// section fragments except startup code and interrupt vectors should
// set this flag.

// The (2) is for the (align)
// The power of two to which the address should be aligned.
// The permitted range is 0 to 8. 
// Code aligned at 4 Bytes.

    SECTION .text:CODE:REORDER:NOROOT(2)
    
    THUMB               // Indicates THUMB code is used
                        // Subsequent instructions are assembled as THUMB instructions
    
/*******************************************************************************
Function Name   : swapCharsAsm
Description     : Calls C code to print a string; 
                  swaps 
C Prototype     : int swapCharsAsm(char* char0, char* char1)
                : Where char* char0 and char* char1 are pointers to characters to swap
Parameters      : R0 and R1: Addresses of char0 and char1
Return value    : R0
*******************************************************************************/  
  
swapCharsAsm
    PUSH {R0,R1,LR}     // save the input argument and return address
    LDR R0,=myCstr      // load (global) address of address of string into R0
    BL  PrintString     // call PrintString to print the string
    POP {R0,R1,LR}      // Restore R0 and LR
    LDRB R2, [R0]       // R2 = value of the first parameter passed through R0
    LDRB R3, [R1]       // R3 = value of the second parameter passed through R1
    CMP R2, R3          // Compare the characters passed as parameters
    ITT EQ              // If the characters are identical
    MOVEQ R0, #0        // Return 0 through R0
    BXEQ LR             // Exit from the function
    STRB R2, [R1]       // Store the first character to the address of the second function parameter
    STRB R3, [R0]       // Store the second character to the address of the first function parameter
    MOV R0, #1          // Return 1 through R0
    BX LR               // return (with function result in R0)

    END
