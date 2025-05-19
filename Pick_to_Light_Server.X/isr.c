#include "main.h"

extern unsigned char ch;

void __interrupt() isr(void)

{ // When character is input through keyboard the UART interrupt isr will be called to get that character
    if (RCIF == 1)
    {
        
        ch = RCREG;
        
        RCIF = 0;
    }
}
