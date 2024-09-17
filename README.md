# Traffic System - Embedded Systems Final Project

This project was part of the **Embedded Systems** course and was developed using **Embedded C** on the **PIC18F4331 microcontroller**. The system controls a 4-way traffic light, including pedestrian walk buttons and interrupt-based light changes.

## Overview
The project simulates a real-world 4-way traffic light system. The traffic lights are controlled by external interrupts and peripherals such as LEDs and timers. Although left turns are not included, the system features pedestrian buttons to trigger walk signals.

## Project Features
- **Traffic Light Simulation**: Implemented a 4-way traffic light control using the PIC18F4331 microcontroller.
- **Peripheral Management**: Controlled general I/O for LEDs, TIMERO module, INT0 external interrupt, and INT1 external interrupt.
- **Interrupt-Driven Logic**: Used external interrupts to handle pedestrian inputs and system responses in real-time.
  
## Technologies Used
- Embedded C
- PIC18F4331 Microcontroller
- Peripherals: LEDs, external interrupts, TIMERO module

## Key Takeaways
This project helped solidify my knowledge in embedded systems, particularly in using interrupts to manage real-time inputs. It also provided a deep understanding of how microcontroller peripherals like LEDs and timers are controlled programmatically.

## Files Included
- **Configuration.h**: Microcontroller configuration and setup.
- **Final_Project_Main.c**: Main C file containing the logic for the traffic system.
- **Embedded Systems Project Report.docx**: Project documentation and detailed explanation of the system.
