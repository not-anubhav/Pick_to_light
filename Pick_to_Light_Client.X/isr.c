#include "pl.h"

extern unsigned int key_detected;

void __interrupt() isr(void)
{
	if (INT0F == 1)
	{
		key_detected = !key_detected; // Toggle flag value for turning on and off SSD
        
        /* Read values from internal eeprom and initialize variables */
        c1 = read_internal_eeprom(ust_addr[0]);
        c2 = read_internal_eeprom(ust_addr[1]);
        c3 = read_internal_eeprom(ust_addr[2]);
        c4 = read_internal_eeprom(ust_addr[3]);

        c5 = read_internal_eeprom(pid_addr[0]);
        c6 = read_internal_eeprom(pid_addr[1]);
        c7 = read_internal_eeprom(pid_addr[2]);
        c8 = read_internal_eeprom(pid_addr[3]);
        
        /* Reset all the flag values */
        mode_switch = 0;
        mode_select = 0;
        dp_select = 4; // 4 because initially dp starts from 4th ssd
        mode1_once = 0;
        mode2_once = 0;
        client_receive_flag = 0;
        client_receive_once_flag = 0;
        client_receive_compare_flag = 0;
        
		INT0F = 0;
	}
}
