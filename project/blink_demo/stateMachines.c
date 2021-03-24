#include <msp430.h>
#include "stateMachines.h"
#include "led.h"

void binary_count()   /* Counts in binary with the leds */
{
  static char ptn1_state = 0;
  
  switch (ptn1_state) {
  case 0:
    red_on = 0;
    green_on = 0;
    break;
  case 1:
    red_on = 1;
    green_on = 0;
    break;
  case 2:
    red_on = 0;
    green_on = 1;
    break;
  default:
    red_on = 1;
    green_on = 1;
    ptn1_state = -1;
  }
  
  ptn1_state++;
}

void double_blink()   /* Blink red, blink green, blink both */
{
  static char ptn2_state = 0;
  
  if (ptn2_state %2 == 0) {
    green_on = 0;
    red_on = 0;
  }
  else if (ptn2_state < 6) {
    green_on = 1;
    red_on = 0;
  }
  else if (ptn2_state < 12) {
    green_on = 0;
    red_on = 1;
  }
  else if (ptn2_state < 16) {
    green_on = red_on = 1;
  }
  else {
    green_on = red_on = 1;
    ptn2_state = -1;
  }
  
  ptn2_state++;
}

void toggle()
{
  static char ptn4_state = 0;

  switch (ptn4_state) {
  case 0:
    red_on = 1;
    green_on = 0;
    ptn4_state = 1;
    break;
  case 1:
    red_on = 0;
    green_on = 1;
    ptn4_state = 0;
  }
}


void state_advance()		/* alternate between toggling red & green */
{
  /*
  switch (pattern) {
  case 1:
    binary_count();
    break;
  case 3:
    double_blink();
    break;
  case 4:
    toggle();
    break;
  default:
    red_on = 1;
    green_on = 1;
  }
  */
  double_blink();

  led_changed = 1;
  led_update();
}
