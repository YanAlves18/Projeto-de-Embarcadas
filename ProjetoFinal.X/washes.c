#include <pic18f4520.h>
#include "ssd.h"
#include "config.h"
#include "pwm.h"
#include "keypad.h"
#include "lcd.h"
#include "lcdMsg.h"
#include "time.h"
#include "bits.h"
#include "washes.h"

#define ON 0x0F
#define L1 0xC0
#define CLR 0x01

char msg1[32] = "Enchendo de agua";
char msg2[32] = "Lavando...";
char msg3[32] = "Enxaguando...";
char msg4[32] = "Secando...";
char msg5[64] = "Para outra      lavagem         pressione RESET";

void preWash(void) {
    //Liga o cooler --> representa jato de água quente - Pré lavagem
    char msgem[32] = "Iniciando       Pre-Lavagem";
    char msgem1[32] = "Realizando Aqcua-Spray...";
    char msgem2[32] = "Finalizando";

    //iniciando
    printf(msgem, 32);
    delay(2000);
    
    //lavando
    printf(msgem1, 32);
    lcdPosition(1, 9);
    lcdCommand(ON);
    pwmSet1(100);
    ssdTimer(600);
    printf(msgem2, 32);
    lcdPosition(0, 11);
    lcdCommand(ON);

    //Fim da pré-lavagem
    pwmSet1(0);
    bitClr(PORTA, 2);
    lcdCommand(CLR);
    lcdCommand(0x0C);
    delay(100);
    
    //buzzer
    pwmFrequency(10000);
    pwmSet2(50);
    bitSet(TRISC, 1);
    PORTD = 0xFF;
    delay(3000);
    bitClr(TRISC, 1);
    PORTD = 0x00;
    delay(1000);
    bitSet(TRISC, 1);
    pwmFrequency(10000);
    PORTD = 0xFF;
    delay(3000);
    bitClr(TRISC, 1);
    PORTD = 0x00;
    delay(1000);
    bitSet(TRISC, 1);
    pwmFrequency(10000);
    PORTD = 0xFF;
    delay(3000);
    bitClr(TRISC, 1);
    pwmSet2(0);
    PORTD = 0x00;
    
    delay(100);
    
    //Opções de lavagem
    kpOptions2();
}

void washOne(void) {
    float tempo;
    int c, i;
    long int cont = 12000;
    char msg[32] = "Iniciando       Lavagem pesada";

    printf(msg, 32);
    delay(2000);

    printf(msg1, 32);
    lcdPosition(0, 15);
    lcdCommand(ON);

    PORTC = 0x01;

    while (cont >= 0) {
        if (c == 0) {
            cont--;
            c = 12;
        }

        if (cont == 9000) {
            pwmSet1(100);
            PORTC = 0x00;
            printf(msg2, 32);
            lcdPosition(0, 10);
            lcdCommand(ON);
        }

        if (cont == 6000) {
            pwmSet1(0);
            PORTE = 0x01;
            printf(msg3, 32);
            lcdPosition(0, 13);
            lcdCommand(ON);
        }

        if (cont == 3000) {
            PORTE = 0x00;
            pwmSet1(100);
            printf(msg4, 32);
            lcdPosition(0, 10);
            lcdCommand(ON);
        }

        if ((cont / 100) % 10 < 6) {
            ssdDigit(((cont / 10) % 10), 3);
        }
        delayAux(2);
        if ((cont / 100) % 10 < 6) {
            ssdDigit(((cont / 100) % 10), 2);
        }
        if ((cont / 100) % 10 >= 6) {
            for (tempo = 0; tempo < 4; tempo++) {
                for (i = 0; i < 10; i++) {
                    cont--;
                }
            }
        }

        delayAux(2);
        ssdDigit(((cont / 1000) % 10), 1);
        delayAux(2);
        ssdDigit(((cont / 10000) % 10), 0);
        delayAux(2);
        ssdUpdate();
        delayAux(2);
        c--;
    }


    //Lavagem Finalizada
    PORTA = 0x00;
    pwmSet1(0);
    printf("Finalizada!", 10);
    
    //buzzer
    buzzer();
    
    PORTB = 0x00;
    PORTA = 0x00;
    delay(3000);
    //reinicio do programa para outra lavagem
    printf(msg5, 64);
}

void washTwo(void) {
    float tempo;
    int c, i;
    long int cont = 8000;
    
    char msg[32] = "Iniciando       Lavagem diaAdia";

    printf(msg, 32);

    delay(2000);

    printf(msg1, 32);
    lcdPosition(0, 15);
    lcdCommand(ON);

    PORTC = 0x01;
    while (cont >= 0) {
        if (c == 0) {
            cont--;
            c = 12;
        }
        
        if (cont == 6000) {
            pwmSet1(75);
            PORTC = 0x00;
            printf(msg2, 32);
            lcdPosition(0, 10);
            lcdCommand(ON);
        }

        if (cont == 4000) {
            pwmSet1(0);
            PORTE = 0x01;
            printf(msg3, 32);
            lcdPosition(0, 13);
            lcdCommand(ON);
        }

        if (cont == 2000) {
            PORTE = 0x00;
            pwmSet1(75);
            printf(msg4, 32);
            lcdPosition(0, 10);
            lcdCommand(ON);
        }
        
        if ((cont / 100) % 10 < 6) {
            ssdDigit(((cont / 10) % 10), 3);
        }
        delayAux(2);
        if ((cont / 100) % 10 < 6) {
            ssdDigit(((cont / 100) % 10), 2);
        }
        if ((cont / 100) % 10 >= 6) {
            for (tempo = 0; tempo < 4; tempo++) {
                for (i = 0; i < 10; i++) {
                    cont--;
                }
            }
        }

        delayAux(2);
        ssdDigit(((cont / 1000) % 10), 1);
        delayAux(2);
        ssdDigit(((cont / 10000) % 10), 0);
        delayAux(2);
        ssdUpdate();
        delayAux(2);
        c--;
    }

    //Lavagem Finalizada
    PORTA = 0x00;
    pwmSet1(0);
    
    printf("Finalizada!", 10);

    //buzzer de aviso
    buzzer();
    
    PORTB = 0x00;
    PORTD = 0x00;

    delay(3000);
    //reinicio do programa para outra lavagem
    printf(msg5, 64);
}

void washThree(void) {
    float tempo;
    int c, i;
    long int cont = 4000;
    
    char msg[32] = "Iniciando       Lavagem rapida";

    printf(msg, 32);
    delay(2000);

    printf(msg1, 32);
    lcdPosition(0, 15);
    lcdCommand(ON);

    PORTC = 0x01;
    while (cont >= 0) {
        if (c == 0) {
            cont--;
            c = 12;
        }
        
        if (cont == 3000) {
            pwmSet1(50);
            PORTC = 0x00;
            printf(msg2, 32);
            lcdPosition(0, 10);
            lcdCommand(ON);
        }

        if (cont == 2000) {
            pwmSet1(0);
            PORTE = 0x01;
            printf(msg3, 32);
            lcdPosition(0, 13);
            lcdCommand(ON);
        }

        if (cont == 1000) {
            PORTE = 0x00;
            pwmSet1(50);
            printf(msg4, 32);
            lcdPosition(0, 10);
            lcdCommand(ON);
        }
        
        if ((cont / 100) % 10 < 6) {
            ssdDigit(((cont / 10) % 10), 3);
        }
        delayAux(2);
        if ((cont / 100) % 10 < 6) {
            ssdDigit(((cont / 100) % 10), 2);
        }
        if ((cont / 100) % 10 >= 6) {
            for (tempo = 0; tempo < 4; tempo++) {
                for (i = 0; i < 10; i++) {
                    cont--;
                }
            }
        }

        delayAux(2);
        ssdDigit(((cont / 1000) % 10), 1);
        delayAux(2);
        ssdDigit(((cont / 10000) % 10), 0);
        delayAux(2);
        ssdUpdate();
        delayAux(2);
        c--;
    }
    //Lavagem Finalizada
    PORTA = 0x00;
    pwmSet1(0);
    
    printf("Finalizada!", 10);
    //buzzer de aviso
    buzzer();
    
    PORTB = 0x00;
    PORTD = 0x00;
    delay(3000);
    
    //reinicio do programa para outra lavagem
    printf(msg5, 64);
}

void washFour(void) {
    float tempo;
    int c, i;
    long int cont = 5000;
    
    char msg[48] = "Iniciando       Lavagem economica";

    printf(msg, 32);
    delay(2000);
    
    printf(msg1, 32);
    lcdPosition(0, 15);
    lcdCommand(ON);

    PORTC = 0x01;
    while (cont >= 0) {
        if (c == 0) {
            cont--;
            c = 12;
        }
        
        if (cont == 4000) {
            pwmSet1(25);
            PORTC = 0x00;
            printf(msg2, 32);
            lcdPosition(0, 10);
            lcdCommand(ON);
        }

        if (cont == 2000) {
            pwmSet1(0);
            PORTE = 0x01;
            printf(msg3, 32);
            lcdPosition(0, 13);
            lcdCommand(ON);
        }

        if (cont == 1000) {
            PORTE = 0x00;
            pwmSet1(25);
            printf(msg4, 32);
            lcdPosition(0, 10);
            lcdCommand(ON);
        }
        
        if ((cont / 100) % 10 < 6) {
            ssdDigit(((cont / 10) % 10), 3);
        }
        delayAux(2);
        if ((cont / 100) % 10 < 6) {
            ssdDigit(((cont / 100) % 10), 2);
        }
        if ((cont / 100) % 10 >= 6) {
            for (tempo = 0; tempo < 4; tempo++) {
                for (i = 0; i < 10; i++) {
                    cont--;
                }
            }
        }

        delayAux(2);
        ssdDigit(((cont / 1000) % 10), 1);
        delayAux(2);
        ssdDigit(((cont / 10000) % 10), 0);
        delayAux(2);
        ssdUpdate();
        delayAux(2);
        c--;
    }

    //Lavagem Finalizada
    PORTA = 0x00;
    pwmSet1(0);
    
    
    printf("Finalizada!", 10);
    buzzer();
    
    PORTB = 0x00;
    PORTD = 0x00;

    delay(3000);
    //reinicio do programa para outra lavagem
    printf(msg5, 64);
}