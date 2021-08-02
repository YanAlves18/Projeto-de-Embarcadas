# 1 "time.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "time.c" 2
# 1 "./time.h" 1
# 11 "./time.h"
void delay(unsigned int temp);
void delayAux(int i);
# 1 "time.c" 2


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
