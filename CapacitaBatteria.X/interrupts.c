/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#include <xc.h>         /* XC8 General Include File */

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */


/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* High-priority service */

uint8_t counter=0;
uint8_t signalSecond=0;

void interrupt high_isr(void) {
    if (INTCONbits.TMR0IF){
        INTCONbits.TMR0IF=0;
        
        counter++;
        if (counter==45){
            TMR0H=0x39;
            TMR0L=0x40;
        }
        if (counter==46){
            signalSecond=1;
            counter=0;
        }
    }
}

/* Low-priority interrupt routine */
#if defined(__XC) || defined(HI_TECH_C)
void low_priority interrupt low_isr(void)
#elif defined (__18CXX)
#pragma code low_isr=0x18
#pragma interruptlow low_isr
void low_isr(void)
#else
#error "Invalid compiler selection for implemented ISR routines"
#endif
{

    /* This code stub shows general interrupt handling.  Note that these
    conditional statements are not handled within 3 seperate if blocks.
    Do not use a seperate if block for each interrupt flag to avoid run
    time errors. */

#if 0

    /* TODO Add Low Priority interrupt routine code here. */

    /* Determine which flag generated the interrupt */
    if (<Interrupt Flag 1 >) {
        <Interrupt Flag 1 = 0 >; /* Clear Interrupt Flag 1 */
    } else if (<Interrupt Flag 2 >) {
        <Interrupt Flag 2 = 0 >; /* Clear Interrupt Flag 2 */
    } else {
        /* Unhandled interrupts */
    }

#endif

}
