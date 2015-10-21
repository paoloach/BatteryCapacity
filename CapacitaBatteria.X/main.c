/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <xc.h>        /* XC8 General Include File */
#include <stdint.h>        /* For uint8_t definition */
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>       /* For true/false definition */
#include "user.h"          /* User funct/params, such as InitApp */
#include "LCD.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

uint32_t totADC;
uint32_t totCur;

extern uint8_t signalSecond;

void writeCurrentValue(uint32_t current, char unity) {
    static char capacity[20];
    static char strLine1[17];
    static char * iterLine1;
    static char * iterCap;
    static uint8_t i;
    
    ltoa(capacity, current, 10);
    size_t lenCap = strlen(capacity);
    int width = 10 - lenCap;
    iterLine1 = strLine1;
    for (i = 0; i < width; i++) {
        *iterLine1 = ' ';
        iterLine1++;
    }
    for (iterCap = capacity; *iterCap != 0; iterCap++, iterLine1++) {
        *iterLine1 = *iterCap;
    }
    *iterLine1 = unity;
    iterLine1++;
    *iterLine1 = 'A';
    iterLine1++;
    *iterLine1 = '/';
    iterLine1++;
    *iterLine1 = 'h';
    line1();
    writeLCD(strLine1);
}

void main(void) {
    InitApp();

    while (1) {
        if (signalSecond == 1) {
            ADCON0bits.CHS = 0;
            _delay(300);
            PIR1bits.ADIF = 0;
            ADCON0bits.GO = 1;
            while (ADCON0bits.GO == 1);
            // ADRES containt the binary value read from ADC.
            // V = ADRES*5/1024 is the voltage read from ADC
            // A = V/100 is the current passed in the second (100 is the resistence value: 100 Ohm)
            // that is A is the capacity loss in A/s
            // Adding this values for 3600 seconds we have the capacity loss for hour
            // Adding this values until the voltage is 0 (or under a threshold) we have the
            // total capacity cantained in the battery.
            // So every second the total capacity lost is given:
            // sum of (ADRES*5/(1024*100))
            // in the unit of A/s
            // To trasform it in mA/H we have to multiply for 1000 and divide for 3600
            // sum of (ADRES*5*1000/(1024*100*3600) = 
            // sum of ((ADRES*5000)/368640000)( =
            // sum of ((ADRES*5)/368640)
            // and pull out the constant
            // (sum of (ADRES))*5/368640
            totADC += ADRES;
            line1();
            totCur = (totADC*5)/368640;
            if (totCur < 100){
                totCur = (totADC*5000)/368640;
                writeCurrentValue(totCur, 'u');
            } else {
                writeCurrentValue(totCur, 'm');
            }
            
            signalSecond = 0;
        }
    }
}

