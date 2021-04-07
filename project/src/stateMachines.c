#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"

static char curr_state = 1;

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

void toggle() /* Toggles between red and green */
{
  static char ptn3_state = 0;
  switch (ptn3_state) {
  case 0: red_on = 1; green_on = 0; ptn3_state = 1; break;
  case 1: red_on = 0; green_on = 1; ptn3_state = 0;
  }
}

void led_state_advance()      	/* Advances state of LEDs */
{
  switch(curr_state) {
  case 0: binary_count(); break;
  case 2: double_blink(); break;
  case 3: toggle(); break;
  default: red_on = 1; green_on = 1;
  }
  led_changed = 1;
  led_update();
}

void melody_1()                 /* Simple melody 1 */
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

void melody_2()                 /* Simple melody 2 */
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

void melody_3()                  /* Simple melody 3 */
{
  static short mel3_state = 30000;
  buzzer_set_period(mel3_state);
  mel3_state = 0 ? 30000 : (mel3_state - 5000);
}

void buzzer_state_advance()      /* Advances state of buzzer */
{
  if (switch0_down)
    melody_1();
  else if (switch2_down)
    melody_2();
  else if (switch3_down)
    melody_3();
  else
    buzzer_set_period(0);
}

void switch_state_changed()      /* Updates states if a different button is pressed */
{
  if (button_pressed) {
    if (switch0_down)
      curr_state = 0;
    else if (switch2_down)
      curr_state = 2;
    else if (switch3_down)
      curr_state = 3;
    else
      curr_state = 1;
  }
  led_state_advance();
  buzzer_state_advance();
}
