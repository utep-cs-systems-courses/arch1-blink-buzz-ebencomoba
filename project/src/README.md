## Description
This interrupt-driven program is in a standby mode where both LEDs (red and
green) are on. When a button is pressed, the LED will turn on and off
intermittenly with a pattern for each button. This pattern will remain until
another button is pressed. Additionally, each button has a tune that will
sound while it is being pressed. An exception is the second button, that will
not make sound and will send back to the standyby mode.

## How to use
The Makefile contains the rules to compile and clean the program. To load it
into the MSP430 you need to type:
**make load**

## Structure
The program is divided according to the functions on the controller. It is
mainly directed towards the input of the switches to change states, the output
of the LEDs that blinks in specific patterns with a timer, and the sounds produced by a little
buzzer.

### main
main.c contains the main program that it is executed when running. It
inititializs the buzzer, switches, leds and timer.

### led
Contains how the leds should be initialized and updating the led by turning
them on or off as requested.

### buzzer
Contains how to initialize the buzzer and what sound will be produced based on
the period of the wavelength.

### switches
Contains how to initialize the switches, it updates the interrupt sense and
other variables depending on the state of the buttons.

### stateMachines
It updates the buzzer and the led states. It contains three patterns for the
leds and one to reset them. Each pattern will keep control of the previous
state to output the next led state. Similarly, while a button is being
pressed, depending on which of them, a musical melody will sound. Both, buzzer
and led updates depend on a timer to go to the next state.

### wInterruptHandler
Contains the timers for buzzer and the leds. They are independient of each
other, and once a certain interval of time has passed they will call the
function to update states. It also contains the second port used for the
switches, to update their states each time input changes.

