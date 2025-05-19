#include "pl.h"

unsigned char read_internal_eeprom(unsigned char addr) // Function for reading data from internal EEPROM
{
    EEADR = addr;
    
    EEPGD = 0;
    CFGS = 0;
    
    WREN = 0;
    
    RD = 1;
    
    return EEDATA;
}

void write_internal_eeprom(unsigned char addr, unsigned char data) // Function for writing data to internal EEPROM
{
    EEADR = addr;
    EEDATA = data;
    
    EEPGD = 0;
    CFGS = 0;
    
    WREN = 1;
    
    GIE = 0;
    
    EECON2 = 0x55;
    EECON2 = 0xAA;
    
    WR = 1;
    GIE = 1;
    
    while(WR);
    
    WREN = 0;
}