### Describe an embedded device ###
A <a href="https://journals.plos.org/plosone/article/figure?id=10.1371/journal.pone.0218571.g001">thermal controller</a> for thermal cycling in portable polymerase chain reaction (PCR) devices. Receives input from temperature detectors (e.g. resistance temperature detectors - RTD), controls pulse width modulation (PWM) heater modules and fans.
The temperature must follow a user-specified thermal profile. A <a href="https://i.stack.imgur.com/kWSgk.png">typical PCR thermal profile</a> consists of the initial phase (usually lasts a few minutes at ~94-95 &degC) followed by a variable number of thermal cycles. Each thermal cycle consists of a denaturation phase (typically 15-60 seconds at ~94-95 &degC), an annealing phase (typically ~15-45 seconds at ~45-60 &degC), and an extension phase (typically 45-90 seconds at 65-75 &degC). After the specified number of cycles, a final elongation phase (typically 7-10 minutes at 70-75 &degC) follows. At the end a low tempreture (typically 4-10 &degC) is maintained until a stop signal is received from the user (final hold).
### Describe how its embedded system works ###
The thermal controller loads a thermal profile, e.g. from a serial port. A <a href="https://i.stack.imgur.com/kWSgk.png">typical PCR thermal profile</a> consists of the initial phase (usually lasts a few minutes) followed by a variable number of thermal cycles. Each thermal cycle consists of a denaturation phase (typically 15-60 seconds), an annealing phase (typically ~15-45 seconds), and an extension phase (typically 45-90 seconds). After the specified number of cycles, a final elongation phase (typically 7-10 minutes) follows. At the end a low tempreture (typically 4-10 oc) is maintained until a stop signal is received from the user (final hold).
### What design challenges does it present ###
- Throughput - a system may need to handle a lot of data in a short period of time.
- Response - a system may need to react to events quickly.
- Testability - setting up equipment to test embedded software can be difficult.
- Debugability - without a screen/keyboard finding out what the software is doing wrong is troublesome.
- Reliability - an embedded system must be able to handle any situation without human intervention.
- Memory Space - you must make the software and the data fit into whatever limited memory exists.
- Program Installation - need special tools to get the software into the embedded system.
- Power Consumption - the software on portable systems running on battery must conserve power.
- Processor Hogs - computing that requires large amounts of CPU time can complicate the response problem.
- Cost - software often needs to operate on hardware that is barely adequate for the task (to reduce th cost of the hardware)
