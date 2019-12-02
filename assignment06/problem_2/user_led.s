/*******************************************************************************
File name       : user_led.s
Description     : Assembly language function for controlling the user LED
*******************************************************************************/   

    EXTERN delay  // delay() is defined outside this file.

    PUBLIC control_user_led         // Exports symbols to other modules

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
Function Name   : control_user_led
Description     : - Uses Peripheral registers at base 0x4000.0000
                    to set GPIOA Output Data Register.
                  - Calls another assembly function delay to insert
                    delay loop

C Prototype     : void control_user_led(uint8_t state, uint32_t duration)
                : Where state indicates if LED should be on or off.
Parameters      : R0: uint8_t state
                : R1: uint32_t duration
Return value    : None
*******************************************************************************/  

control_user_led
    MOV R2, #0x4002     ; GPIOA Base Address is bigger than 2^16 and cannot be produced by shifting a 8-bit value
    LSL R2, R2, #16     ; Shift the value in the R2 left to yield 0x40020000
    ADD R2, R2, #0x14   ; Add GPIOA_ODR offset to GPIOA base stored in R2
    LDR R3, [R2]        ; Load the GPIOA_ODR value to R3
    CMPS R0, #1         ; If the state passed through R0 is ON=1
    ITE EQ
    ORREQ R3, R3, R0, LSL #5    ; THEN Set GPIOA_ODR_5
    BICNE R3, R3, #0x20         ; ELSE Reset GPIO_ODR_5
    STR R3, [R2]        ; Write the modified GPIOA_ODR_5 value back to GPIO_ODR
    MOV R0, R1          ; Move the duration passed through R1 to R0 to pass it to the delay function
    PUSH {LR}       // Save the input arguments as needed and LR
    BL delay
    POP {LR}        // Restore Risgters and LR
    BX LR           // Return

    END
