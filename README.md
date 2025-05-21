# Medicine-remainder-system
Project Overview
The Medicine Reminder System is a microcontroller-based embedded system designed to assist users in taking medicines on time. The system uses a Real-Time Clock (RTC), an LCD, a 4x4 matrix keypad, switches, and a buzzer to schedule and alert users for their medication.

## Objectives
Display current date and time using RTC on an LCD.

Allow the user to set and modify RTC settings using a keypad.

Provide timely alerts when it's time to take medicine.

Allow acknowledgment of alerts using a button press.

## Hardware Requirements
LPC2148 Microcontroller

16x2 LCD Display

4x4 Matrix Keypad

RTC (on-chip)

Buzzer

Switches (Switch1 for setting schedule, Switch2 for acknowledgment)

USB-UART Converter or DB-9 Cable

## Software Requirements
Embedded C (programming language)

Flash Magic (for flashing the code to the microcontroller)

## Working Principle
Setting the Medicine Schedule

User presses Switch1 to enter schedule mode.

Time is input using the keypad.

Schedule is saved in microcontroller memory.

LCD displays saved medicine times and RTC info.

Real-Time Monitoring

The system continuously checks the RTC for current time.

If a match is found between current time and a saved schedule, an alert is triggered.

Alert Mechanism

LCD displays a message like "Take Medicine Now".

Buzzer is toggled on and off to grab the user's attention.

User Acknowledgment

Pressing Switch2 acknowledges the alert.

After acknowledgment, system returns to normal display mode.

## Software Flow
Initialize peripherals: RTC, LCD, Keypad, and Buzzer.

Continuously display current date and time on the LCD.

On Switch1 press, allow the user to input medicine schedule via keypad.

Continuously monitor RTC time.

When time matches any scheduled medicine time:

Display alert message on LCD.

Activate buzzer.

Wait for user to press Switch2.

Upon acknowledgment, return to time display and monitoring.

## Usage Instructions
Power on the system.

The LCD will display current date and time.

Press Switch1 to set medicine time.

Use keypad to enter hours and minutes.

System will display saved schedule.

When time matches a schedule, buzzer will alert.

Press Switch2 to acknowledge alert and stop buzzer.

