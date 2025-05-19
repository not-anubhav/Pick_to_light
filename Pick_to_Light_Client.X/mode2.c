#include "pl.h"

void mode2() // Function for handling mode 2 operations
{
    
    mode2_keypress = edge_dkp(); // Detect the keypress on Digital keypad
    
    if(mode2_once == 0) // For the first time after entering the mode 2 display the SSD with P_ID values with dp pointing to 4th SSD
    {
        mode2_once = 1;
        ssd[0] = disp_num[c5];
        ssd[1] = disp_num[c6];
        ssd[2] = disp_num[c7];
        ssd[3] = disp_num[c8] | 0x10;
    }
    
    
    switch (dp_select) { // Based on the Dp position in SSD we will increment the Value displaying at that particular SSD
        case 1: // If Dp is pointing at the 1st SSD
            if(mode2_keypress == 0x0E) // If switch 1 is pressed in the Digital Keypad
            {
                c5++; // Increment the Value of the Variable Displaying at 1st SSD i.e c5
                if (c5 == 10) { // When c5 value reaches 10 reset the value to 0
                    c5 = 0;
                }
            }
            /* Display the present values on SSDs with Dp at 1st SSD */
            ssd[0] = disp_num[c5] | 0x10;
            ssd[1] = disp_num[c6];
            ssd[2] = disp_num[c7];
            ssd[3] = disp_num[c8];
            break;
        case 2: // If Dp is pointing at the 2nd SSD
            if(mode2_keypress == 0x0E) // If switch 1 is pressed in the Digital Keypad
            {
                c6++; // Increment the Value of the Variable Displaying at 2nd SSD i.e c6
                if (c6 == 10) { // When c6 value reaches 10 reset the value to 0
                    c6 = 0;
                }
            }
            /* Display the present values on SSDs with Dp at 2nd SSD */
            ssd[0] = disp_num[c5];
            ssd[1] = disp_num[c6] | 0x10;
            ssd[2] = disp_num[c7];
            ssd[3] = disp_num[c8];
            break;
        case 3: // If Dp is pointing at the 3rd SSD
            if(mode2_keypress == 0x0E) // If switch 1 is pressed in the Digital Keypad
            {
                c7++; // Increment the Value of the Variable Displaying at 3rd SSD i.e c7
                if (c7 == 10) { // When c7 value reaches 10 reset the value to 0
                    c7 = 0;
                }
            }
            /* Display the present values on SSDs with Dp at 3rd SSD */
            ssd[0] = disp_num[c5];
            ssd[1] = disp_num[c6];
            ssd[2] = disp_num[c7] | 0x10;
            ssd[3] = disp_num[c8];
            break;
        case 4: // If Dp is pointing at the 4th SSD
            if(mode2_keypress == 0x0E) // If switch 1 is pressed in the Digital Keypad
            {
                c8++; // Increment the Value of the Variable Displaying at 4th SSD i.e c8
                if (c8 == 10) { // When c8 value reaches 10 reset the value to 0
                    c8 = 0;
                }
            }
            /* Display the present values on SSDs with Dp at last SSD */
            ssd[0] = disp_num[c5];
            ssd[1] = disp_num[c6];
            ssd[2] = disp_num[c7];
            ssd[3] = disp_num[c8] | 0x10;
            break;
    }
    
    if(mode2_keypress == 0x0D) // If switch 2 is pressed on the digital keypad
    {
        dp_select--; // Decrement and change the Dp position from Right to Left SSDs
        if(dp_select < 1) // After Dp reaches 1st SSD on left, if decrement reset the Dp postion to 4th SSD on right
        {
            dp_select = 4;
        }
    }
    
    display(ssd); // Display the Modified P_ID Value and Dp on SSDs
    
    if (mode2_keypress == 0x0B)  // If Switch 3 is pressed
    {
        
        PORTA = PORTA & 0xF0; // Turn off the SSD

        /* Reset the Flags */
        key_detected = 0;
        
        mode_select = 0;
        
        dp_select = 0;
        
        client_receive_flag = 0;
        
        /* Write the Updated P_ID data on internal EEPROM*/
        
        write_internal_eeprom(ust_addr[0], c1);
        write_internal_eeprom(ust_addr[1], c2);
        write_internal_eeprom(ust_addr[2], c3);
        write_internal_eeprom(ust_addr[3], c4);

        write_internal_eeprom(pid_addr[0], c5);
        write_internal_eeprom(pid_addr[1], c6);
        write_internal_eeprom(pid_addr[2], c7);
        write_internal_eeprom(pid_addr[3], c8);

        can_transmit(); // Transmit the Updated P_ID data to server by calling CAN transmit function
        
        __delay_ms(1000);
    }
}