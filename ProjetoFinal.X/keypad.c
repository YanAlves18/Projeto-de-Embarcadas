// -----------------------------------------------------------------------
//   Copyright (C) Rodrigo Almeida 2014
// -----------------------------------------------------------------------
//   Arquivo: keypad.c
//            Biblioteca de opera��o de um teclado matricial
//   Autor:   Rodrigo Maximiano Antunes de Almeida
//            rodrigomax at unifei.edu.br
//   Licen�a: GNU GPL 2
// -----------------------------------------------------------------------
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; version 2 of the License.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
// -----------------------------------------------------------------------

#include "keypad.h"
#include <pic18f4520.h>
#include "io.h"
#include "bits.h"
#include "lcd.h"
#include "lcdMsg.h"
#include "washes.h"
#include "time.h"
#include "ssd.h"

#define CLR 0x01

static unsigned int valor = 0x0000;

#define LIN0 PIN_D0
#define LIN1 PIN_D1
#define LIN2 PIN_D2
#define LIN3 PIN_D3
#define COL0 PIN_B0 
#define COL1 PIN_B1
#define COL2 PIN_B2

unsigned int kpRead(void) {
    return valor;
}

void kpDebounce(void) {
    unsigned char i, j;
    static unsigned char tempo;
    static unsigned int valorNovo = 0x0000;
    static unsigned int valorAntigo = 0x0000;

    //store D to avoid mess with other periphels
    unsigned char old_D;
    old_D = PORTD;

    //PORTD � compartilhado, ent�o tem
    //que garantir que � entrada
    TRISD |= 0x0f;

    for (i = 0; i < 3; i++) {
        //desabilita todas as colunas
        TRISB &= 0xF8;
        //Habilita apenas a coluna desejada
        bitSet(TRISB, i);
        //coloca nivel alto s� na coluna desejada
        PORTB |= 0x07;
        bitClr(PORTB, i);

        //delay pra estabilizar os sinais
        for (int k = 0; k < 10; k++);

        //realiza o teste para cada bit e atualiza a vari�vel
        for (j = 0; j < 4; j++) {
            if (!bitTst(PORTD, j)) {
                bitSet(valorNovo, (i * 4) + j);
            } else {
                bitClr(valorNovo, (i * 4) + j);
            }
        }
    }
    if (valorAntigo == valorNovo) {
        tempo--;
    } else {
        tempo = 10;
        valorAntigo = valorNovo;
    }
    if (tempo == 0) {
        valor = valorAntigo;
    }
    PORTD = old_D;
    TRISD = 0x00;
}

void kpInit(void) {
    //coloca 0-2 como sa�da
    TRISB &= 0x07;
    //coloca 0-3 como entrada
    TRISD |= 0x0f;
}

void kpOptions1(void) {
    unsigned int tecla = 0;

    while(tecla == 0) {
        kpDebounce();
        if (kpRead() != tecla) {
            tecla = kpRead();
            if (bitTst(tecla, 0)) {
                lcdCommand(CLR);
                preWash();
            } else if (bitTst(tecla, 8)) {
                kpOptions2();
            }
        }
    }
}

void kpOptions2(void) {

    unsigned int tecla1 = 0;

    char msg2[32] = "Escolha uma     opcao de lavagem";
    char msg3[64] = "1-Pesada        2-Dia a dia     3-Rapida        4-Economica";
    
    printf(msg2, 32);
    delay(3000);
    
    printf(msg3, 64);
    
    while(1) {
        kpDebounce();
        if (kpRead() != tecla1) {
            tecla1 = kpRead();
            if (bitTst(tecla1, 3)) {
                lcdCommand(CLR);
                washOne();
            } else if (bitTst(tecla1, 7)) {
                lcdCommand(CLR);
                washTwo();
            } else if (bitTst(tecla1, 11)) {
                lcdCommand(CLR);
                washThree();
            } else if (bitTst(tecla1, 2)) {
                lcdCommand(CLR);
                washFour();
            }
        }
    }
}