#ifndef stateMachine_included
#define stateMachine_included

void binary_count();         /* Counts in binary with LEDs */
void double_blink();         /* Blinks green, blinks red, blink both */
void toggle();               /* Toggles between red and green */
void led_state_advance();    /* Advances state of LEDs */
void melody_1();             /* Simple melodies */
void melody_2();
void melody_3();
void buzzer_state_advance(); /* Advances state of buzzer */
void switch_state_changed(); /* Updates states if a different button is pressed */

#endif // included
