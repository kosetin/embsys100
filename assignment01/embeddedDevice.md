### Describe an embedded device ###
A <a href="https://journals.plos.org/plosone/article/figure?id=10.1371/journal.pone.0218571.g001">thermal controller</a> for thermal cycling in portable polymerase chain reaction devices. Receives input from temperature detectors (e.g. resistance temperature detectors - RTD), controls pulse width modulation (PWM) heater modules and fans.
### Describe how its embedded system works ###

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
