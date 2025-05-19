#include "pl.h"

void init_SSD() // Initialize the SSDs
{
    TRISD = 0x00;
    TRISA = TRISA & 0xF0;
    PORTA = PORTA & 0xF0;
    ADCON1 = 0x0F;
}

void display(unsigned char *ssd) // Function for Displaying Data on SSDs
{
    for(int i = 0; i < 4; i++)
    {
        PORTD = ssd[i];
        PORTA = (PORTA & 0xF0) | (1 << i);
        for(int wait = 500; wait--;);
    }
    
}