#include <pic18f4520.h>
#include "config.h"
#include "time.h"

void initDishWasher(void) {
    TRISD = 0x00;
    TRISB = 0x00;
    
    //inicializando lava-louças (ligando leds)
    PORTD = 0x00;
    PORTB = 0x00;

    PORTD = 0x1;
    delay(500);

    PORTD = 0x3;
    delay(500);

    PORTD = 0x7;
    delay(500);

    PORTD = 0xF;
    delay(500);

    PORTD = 0x1F;
    delay(500);

    PORTD = 0x3F;
    delay(500);

    PORTD = 0x7F;
    delay(500);

    PORTD = 0xFF;
    PORTB = 0xFF;
    
    delay(1000);
}