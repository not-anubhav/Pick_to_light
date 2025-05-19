#include "pl.h"

void init_external_interrupt() // Initialize External Interrupt
{
    PEIE = 1;
    GIE = 1;
    INTEDG0 = 1;
	INT0F = 0;
	INT0E = 1;
}

