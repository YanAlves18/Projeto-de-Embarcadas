#include "time.h"

void delay(unsigned int temp) {
    volatile unsigned char j, k;
    unsigned int i;

    for (i = 0; i < temp; i++) {
        for (j = 0; j < 41; j++) {
            for (k = 0; k < 3; k++);
        }
    }
}

void delayAux(int i) {
    int j;
    for (j = 0; j < i; j++);
}