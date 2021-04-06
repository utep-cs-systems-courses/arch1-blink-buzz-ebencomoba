#ifndef switches_included
#define switches_included

#define SW0 BIT0
#define SW1 BIT1
#define SW2 BIT2
#define SW3 BIT3
#define SWITCHES (SW0 | SW1 | SW2 | SW3)	/* only 1 switch on this board */

void switch_init();
void switch_interrupt_handler();

extern char switch0_down, switch1_down, switch2_down, switch3_down;
extern char button_pressed; /* effectively boolean */

#endif // included
