### Describe an embedded device ###
A <a href="https://journals.plos.org/plosone/article/figure?id=10.1371/journal.pone.0218571.g001">thermal controller</a> for thermal cycling in portable <a href="https://en.wikipedia.org/wiki/Polymerase_chain_reaction">polymerase chain reaction (PCR)</a> devices:
- receives/stores a thermal profile
- receives input from temperature detectors (e.g. from resistance temperature detectors - RTD) through an analog-to-digital converter (ADC)
- controls pulse width modulation (PWM) heater modules and fans
- outputs the current temperature, the current step in a thermal profile, elapsed/remaining time in the current step, elapsed/remaining total time.

The temperature must follow a user-specified thermal profile. A <a href="https://i.stack.imgur.com/kWSgk.png">typical PCR thermal profile</a> consists of the initial phase (usually lasts a few minutes at 94-95 °C) followed by a variable number of thermal cycles. Each thermal cycle consists of a denaturation phase (typically 15-60 seconds at 94-95 °C), an annealing phase (typically 15-45 seconds at 45-60 °C), and an extension phase (typically 45-90 seconds at 65-75 °C). After the specified number of cycles, a final elongation phase (typically 7-10 minutes at 70-75 °C) follows. At the end, a low tempreture (typically 4-16 °C) is maintained until a stop signal is received from the user (final hold).
### Describe how its embedded system works ###
A <a href="https://www.semanticscholar.org/paper/Black-Printed-Circuit-Board-based-Micro-Polymerase-Hwang-Kim/62b0a8a11876924e050dcdac1fb3f0607518a490/figure/0">PCR thermal controller</a> is a single-user system. It receives a thermal profile configuration through LCD touch screen, USB or by loading a stored procedure from flash memory. The execution of a thermal profile is started from LCD touch screen or with a push button. The software controls the temperature through PWM heater modules and fans. The progress information about the execution of the thermal profile is displayed on the LCD screen. A user can stop the execution of a thermal profile from LCD touch screen. 
### What design challenges does it present? ###
- *Throughput* - a typical PCR thermal controller can run on a 8-bit microprocessor.
- *Response* - the system must ensure fast step transitions through the thermal profile while standing-by for valid user input (e.g. a command to stop profile execution).
- *Testability* - although the gross output of a thermal controller can be measured with external diagnostic devices (thermometers, timers), simulating and testing all possible unusual situations/corner cases in a laboratory setting would be impossible and/or impractical. An embedded software developer, therefore, must follow specific design patterns (e.g. separating hardware-dependent from hardware-independent code) and rely on manufacturer's toolchain to be able to automate testing the embedded software including testing for possible unusual situations.
- *Debugability* - an embedded software developer must rely on manufacturer's toolchain to debug the software. For example, Microchip Technology provides a trademarked In-Circuit Serial Programming™ (ICSP™) solution, an In-Circuit Debugger (ICD), and an Integrated On-Chip Debugger.
- *Reliability* - an embedded system must be able to handle any situation without human intervention.
- *Memory Space* - A <a href="https://www.microchip.com/wwwproducts/en/PIC18F27Q43">typical microcontroller for PCR thermal controllers</a> features up to 128 KB of Program Flash Memory, up to 8 MB of Data SRAM Memory, and 1024 Bytes Data EEPROM.
- *Program Installation* requires special tools to get the software into the flash memory during development or into EEPROM in production.
- *Power Consumption* - a portable PCR thermal cycler may require additional effort from software developer side to reduce power consumption by the controller.
- *Processor Hogs* - computing that requires large amounts of CPU time can complicate the response problem.
- *Cost* - software often needs to operate on hardware that is barely adequate for the task (to reduce th cost of the hardware)
