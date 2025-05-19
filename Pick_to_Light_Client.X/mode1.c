#include "pl.h"

void mode1() // Function for handling mode 1 operations
{                                                                   
    mode1_keypress = edge_dkp(); // Detect the keypress on Digital keypad
    
    if(mode1_once == 0) // For the first time after entering the mode 1 display the SSD with U_ST values with dp pointing to 4th SSD
    {
        mode1_once = 1;
        ssd[0] = disp_num[c1];
        ssd[1] = disp_num[c2];
        ssd[2] = disp_num[c3];
        ssd[3] = disp_num[c4] | 0x10;
    }
    
    
    switch (dp_select) { // Based on the Dp position in SSD we will increment the Value displaying at that particular SSD
        case 1: // If Dp is pointing at the 1st SSD
            if(mode1_keypress == 0x0E) // If switch 1 is pressed in the Digital Keypad
            {
                c1++; // Increment the Value of the Variable Displaying at 1st SSD i.e c1
                if (c1 == 10) { // When c1 value reaches 10 reset the value to 0
                    c1 = 0;
                }
            }
            /* Display the present values on SSDs with Dp at 1st SSD */
            ssd[0] = disp_num[c1] | 0x10;
            ssd[1] = disp_num[c2];
            ssd[2] = disp_num[c3];
            ssd[3] = disp_num[c4];
            break;
        case 2: // If Dp is pointing at the 2nd SSD
            if(mode1_keypress == 0x0E) // If switch 1 is pressed in the Digital Keypad
            {
                c2++; // Increment the Value of the Variable Displaying at 2nd SSD i.e c2
                if (c2 == 10) { // When c2 value reaches 10 reset the value to 0
                    c2 = 0;
                }
            }
            /* Display the present values on SSDs with Dp at 2nd SSD */
            ssd[0] = disp_num[c1];
            ssd[1] = disp_num[c2] | 0x10;
            ssd[2] = disp_num[c3];
            ssd[3] = disp_num[c4];
            break;
        case 3: // If Dp is pointing at the 3rd SSD
            if(mode1_keypress == 0x0E) // If switch 1 is pressed in the Digital Keypad
            {
                c3++; // Increment the Value of the Variable Displaying at 3rd SSD i.e c3
                if (c3 == 10) { // When c3 value reaches 10 reset the value to 0
                    c3 = 0;
                }
            }
            /* Display the present values on SSDs with Dp at 3rd SSD */
            ssd[0] = disp_num[c1];
            ssd[1] = disp_num[c2];
            ssd[2] = disp_num[c3] | 0x10;
            ssd[3] = disp_num[c4];
            break;
        case 4: // If Dp is pointing at the 4th SSD
            if(mode1_keypress == 0x0E) // If switch 1 is pressed in the Digital Keypad
            {
                c4++; // Increment the Value of the Variable Displaying at 4th SSD i.e c4
                if (c4 == 10) { // When c4 value reaches 10 reset the value to 0
                    c4 = 0;
                }
            }
            /* Display the present values on SSDs with Dp at last SSD */
            ssd[0] = disp_num[c1];
            ssd[1] = disp_num[c2];
            ssd[2] = disp_num[c3];
            ssd[3] = disp_num[c4] | 0x10;
            break;
    }
    
    if(mode1_keypress == 0x0D) // If switch 2 is pressed on the digital keypad
    {
        dp_select--; // Decrement and change the Dp position from Right to Left SSDs
        if(dp_select < 1) // After Dp reaches 1st SSD on left, if decrement reset the Dp postion to 4th SSD on right
        {
            dp_select = 4;
        }
    }
    
    
    display(ssd); // Display the Modified Value and Dp on SSDs
    
    if (mode1_keypress == 0x0B) // If Switch 3 is pressed
    {
        PORTA = PORTA & 0xF0; // Turn off the SSD
        
        /* Reset the Flags */
        key_detected = 0;
        
        mode_select = 0;
        
        dp_select = 0;
        
        client_receive_flag = 0;
        
        /* Write the Updated U_ST data on internal EEPROM*/
        write_internal_eeprom(ust_addr[0], c1);
        write_internal_eeprom(ust_addr[1], c2);
        write_internal_eeprom(ust_addr[2], c3);
        write_internal_eeprom(ust_addr[3], c4);

        write_internal_eeprom(pid_addr[0], c5);
        write_internal_eeprom(pid_addr[1], c6);
        write_internal_eeprom(pid_addr[2], c7);
        write_internal_eeprom(pid_addr[3], c8);

        can_transmit(); // Transmit the Updated U_ST data to server by calling CAN transmit function
        
        __delay_ms(1000);

    }
}