#include <pic18f4520.h>
#include "config.h" 
#include "keypad.h"
#include "bits.h"
#include "lcd.h"
#include "lcdMsg.h"
#include "led.h"
#include "time.h"
#include "ssd.h"
#include "pwm.h"

void main(void) {  
    char msg[32] = "Inicializando...Lava-loucas";
    char msg1[64] = "Pre lavagem?    (*)Aqcua-Spray  (#)Pular etapa";
    
    TRISB = 0x03;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;
    
    initDishWasher();
    
    lcdInit();
    kpInit();
    ssdInit();
    pwmInit();

    printf(msg, 32);
    delay(2000);
    
    printf(msg1, 64);
    delay(2000);
    
    kpOptions1();
}
