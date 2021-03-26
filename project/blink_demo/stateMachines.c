#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

void binary_count()   /* Counts in binary with the leds */
{
  static char ptn1_state = 0;
  switch (ptn1_state) {
  case 0: red_on = 0; green_on = 0; break;
  case 1: red_on = 1; green_on = 0; break;
  case 2: red_on = 0; green_on = 1; break;
  default: red_on = 1; green_on = 1; ptn1_state = -1;
  }
  ptn1_state++;
}

void double_blink()   /* Blink green, blink red, blink both */
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
  static char ptn3_state = 0;
  switch (ptn3_state) {
  case 0: red_on = 1; green_on = 0; ptn3_state = 1; break;
  case 1: red_on = 0; green_on = 1; ptn3_state = 0;
  }
}


void led_state_advance()      	/* Advances */
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

void melody_1()
{
  static short mel1_state = 0;
  switch(mel1_state) {
  case 0: buzzer_set_period(30576); break;
  case 1: buzzer_set_period(15289); break;
  case 2: buzzer_set_period(7644); break;
  default: buzzer_set_period(3822); mel1_state = -1;
  }
  mel1_state++;
}

void melody_2()
{
  static short mel2_state = 0;
  switch(mel2_state) {
  case 0: buzzer_set_period(2727); break;
  case 1: buzzer_set_period(4545); break;
  case 2: buzzer_set_period(9090); break;
  default: buzzer_set_period(18181); mel2_state = -1;
  }
  mel2_state++;
}

void melody_3()
{
  static short mel3_state = 30000;
  buzzer_set_period(mel3_state);
  mel3_state = 0 ? 30000 : (mel3_state - 5000);
}

void buzzer_state_advance()
{
  melody_3();
}
