#ifndef led_included
#define led_included

#define LED_RED BIT6               // P1.6
#define LED_GREEN BIT0             // P1.0
/* I inverted the bits since they seem to turn on the opposite LED in the controller */
#define LEDS (BIT0 | BIT6)

extern unsigned char red_on, green_on;
extern unsigned char led_changed;

void led_init();   /* Initializes LEDs */
void led_update(); /* Turns off the LEDs we are not using and on the ones we are using */

#endif // included
