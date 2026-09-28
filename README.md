# Car-Black-Box
Car Black Box is a PIC16F877A-based automotive event logging system developed using Embedded C. The system monitors speed and gear-related events and records them with real-time timestamps.  The project combines multiple microcontroller peripherals to provide event monitoring, user interaction, authentication, and non-volatile event storage.
Developed a PIC16F877A-based automotive event logger to monitor speed and gear events and record them with
real-time timestamps.
• Implemented CLCD/keypad-based menu navigation, password authentication, View Log, Set Time, logout, and timeout
functionality.
• Integrated ADC, GPIO, Timer, interrupts, I²C, RTC, and EEPROM for real-time monitoring and non-volatile event
storage with rollover handling.
• Applied modular driver development and structured application flow and tested the system using the PIC16F877A
simulator in MPLAB X/XC8.

Key Features
Monitors and records speed and gear events.
Records events with real-time timestamps.
Provides CLCD and keypad-based menu navigation.
Implements password authentication.
Supports View Log and Set Time functions.
Includes logout and timeout functionality.
Stores event records in EEPROM.
Implements rollover handling for event storage.
Hardware and Peripherals

The project uses several PIC16F877A peripherals and interfaces:

ADC for input measurement
GPIO for digital interfacing
Timer and interrupts for timing and event handling
I²C for peripheral communication
RTC for real-time timestamps
EEPROM for non-volatile event storage
CLCD for displaying information
Keypad for user interaction
Implementation

The application follows a structured flow with modular peripheral drivers. Event information is processed by the application layer and stored in EEPROM along with timestamp information. The CLCD and keypad provide a menu-driven interface for accessing stored logs and configuring system functions.

The system was tested using the PIC16F877A simulator in MPLAB X with the XC8 compiler.

Technologies
Embedded C
PIC16F877A
MPLAB X IDE
XC8
I²C
RTC
EEPROM
ADC
CLCD
GPIO
Timers
Interrupts
