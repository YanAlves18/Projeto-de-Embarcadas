# 1 "lcdMsg.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "lcdMsg.c" 2
# 1 "./lcd.h" 1
# 23 "./lcd.h"
 void lcdCommand(unsigned char cmd);
 void lcdData(unsigned char valor);
 void lcdInit(void);
    void lcdPosition(unsigned char lin, unsigned char col);
# 1 "lcdMsg.c" 2

# 1 "./lcdMsg.h" 1
# 11 "./lcdMsg.h"
void printf(char msg[64], int j);
# 2 "lcdMsg.c" 2





void printf(char msg[64], int j) {
    int i = 0;
    lcdCommand(0x01);
    lcdCommand(0x80);
    for (i = 0; i < j; i++) {
        if (i == 16) {
            lcdCommand(0xC0);
        } else if (i == 32) {
            lcdCommand(0x90);
        } else if (i == 48) {
            lcdCommand(0xD0);
        }

        lcdData(msg[i]);
    }
}
