#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "stateMachines.h"

char switch0_down, switch1_down, switch2_down, switch3_down;
char button_pressed;

/* Updates the interrupt sense to save battery */
static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

/* Initializes switches */
void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
}

/* Updates switches dependant variables */
void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  button_pressed = (~p2val) & SWITCHES;  /* Siganls what buttons are being pressed */
  switch0_down = (p2val & SW0) ? 0 : 1;  /* True if the switch is not being pressed down */
  switch1_down = (p2val & SW1) ? 0 : 1;
  switch2_down = (p2val & SW2) ? 0 : 1;
  switch3_down = (p2val & SW3) ? 0 : 1;
  switch_state_changed();                /* Updates states of LEDs and buzzer if necessary */
}
