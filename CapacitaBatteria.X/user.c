/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <xc.h>         /* XC8 General Include File */
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include "user.h"
#include "LCD.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    initLCD();
    ADCON1bits.VCFG1=0;
    ADCON1bits.VCFG0=0;
    ADCON1bits.PCFG = 0xE;

    ADCON0bits.CHS = 0;

    ADCON2bits.ACQT = 0;
    ADCON2bits.ADCS = 0x7;
    ADCON2bits.ADFM=1;

    ADCON0bits.ADON=1;
    
    INTCONbits.GIE=0;
    
    T0CONbits.T08BIT=0;
    T0CONbits.T0CS=0;
    T0CONbits.PSA=1;
    T0CONbits.T0PS=0;
    T0CONbits.TMR0ON=1;
    INTCONbits.T0IF=0;
    INTCONbits.T0IE=1;
    
    INTCONbits.GIE=1;
}

