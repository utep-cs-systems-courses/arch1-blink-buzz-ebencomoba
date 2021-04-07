#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */

  /* Each third of a second, the LEDs' state changes */
  static char blink_count = 0;
  if (++blink_count == 83) {
    led_state_advance();
    blink_count = 0;
  }

  /* Each quarter of a second, the buzzer's state changes */
  static char buzz_count = 0;
  if (++buzz_count == 62) {
    buzzer_state_advance();
    buzz_count = 0;
  }
}

/* Switch on P2 (S2), we use the second Port for the switches */
void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;        /* clear pending sw interrupts */
    switch_interrupt_handler();/* single handler for all switches */
  }
}
