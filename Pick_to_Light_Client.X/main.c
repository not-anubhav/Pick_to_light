#include "pl.h"

void init_config()
{
    init_external_interrupt(); // Initialize the Interrupt
    init_SSD(); // Initialize the SSD
    init_dkp(); // Initialize the Digital Keypad
    init_can(); // Initialize the CAN protocol
}


void main(void)
{
    init_config();
    
    while(1)
    {
        if (can_receive()) // Check for CAN receive flag
        {
            /* If high set the flag values */
            prev_key = key_detected; // Store the Interrupt flag in buffer 
            key_detected = 0; // reset the Interrupt flag
            prev_mode = mode_select; // Store the mode in buffer 
            mode_select = 0; // Reset the mode flag
            
            /* Set Client receive flag values */
            client_receive_flag = 1;
            client_receive_once_flag = 0;
            client_receive_compare_flag = 0;
        }
        
        if(key_detected) // when the external interrupt key is pressed
        {
            
            key_press = edge_dkp(); // Detect the keypress
            
            if(key_press == 0x0B) // switch modes between U_ST and P_ID when switch 3 is pressed on digital keypad
            {
                mode_switch = !mode_switch;
            }
            
            if(mode_switch == 0) // When mode is U_ST
            {
                if(key_press == 0x0D) // If switch 2 is pressed on digital keypad enter the U_ST mode
                {
                    mode_select = 1; // Mode select flag 1 represents mode 1 i.e U_ST
                    dp_select = 4; // Dp first displays from 4th SSD
                    key_detected = 0; // Reset the key detected flag
                }
                
                
                if(mode_select == 0) // If still didn't enter inside the mode keep displaying U_ST on SSD
                {
                    ssd[0] = disp_mode1[0];
                    ssd[1] = disp_mode1[1];
                    ssd[2] = disp_mode1[2];
                    ssd[3] = disp_mode1[3];
                    display(ssd);
                }
            }
            
            else if(mode_switch) // When mode is P_ID
            {
                if(key_press == 0x0D) // If switch 2 is pressed on digital keypad enter the P_ID mode
                {
                    mode_select = 2; // Mode select flag 2 represents mode 2 i.e P_ID
                    dp_select = 4; // Dp first displays from 4th SSD
                    key_detected = 0; // Reset the key detected flag
                }
                
                if(mode_select == 0) // If still didn't enter inside the mode keep displaying P_ID on SSD
                {
                    ssd[0] = disp_mode2[0];
                    ssd[1] = disp_mode2[1];
                    ssd[2] = disp_mode2[2];
                    ssd[3] = disp_mode2[3];
                    display(ssd);
                }
            }
        }
        
        if(key_detected == 0 && mode_select == 1) // If mode 1 is selected enter inside mode 1
        {
            mode1(); // Function for handling mode 1 operations
        }
        else if(key_detected == 0 && mode_select == 2) // If mode 2 is selected enter inside mode 2
        {
            mode2(); // Function for handling mode 2 operations
        }
        else if(key_detected == 0 && client_receive_flag == 1) // If client receive flag is 1 i.e data is received via CAN Protocol
        {
            client_receive(); // Function for handling CAN receive operations
        }
        else
        {
            PORTA = PORTA & 0xF0; // Turn off the SSD
        }
    }
}
