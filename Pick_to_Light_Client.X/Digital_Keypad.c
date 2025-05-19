#include "pl.h"


void init_dkp() // Initialize Digital Keypad
{
    TRISC = TRISC | 0x0F;
}


unsigned char edge_dkp() // Function for Digital Keypad Edge Triggering
{
    static unsigned char once = 1;
    
    if(((PORTC & 0x0F) != 0x0F) && once)
    {
        once = 0;
        return (PORTC & 0x0F);
    }
    else if((PORTC & 0x0F) == 0x0F)
    {
        once = 1;
    }
    
    return 0x0F;
}