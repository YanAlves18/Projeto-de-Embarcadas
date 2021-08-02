#include "lcd.h"
#include "lcdMsg.h"

#define CLR 0x01
#define L0 0x80

void printf(char msg[64], int j) {
    int i = 0;
    lcdCommand(CLR);
    lcdCommand(L0);
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