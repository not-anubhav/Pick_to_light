#include "pl.h"

void client_receive() // Function for handling CAN receive operations
{
    if(client_receive_once_flag == 0) // After data is received using CAN, execute this condtions only once(because of superloop)
    {
        client_receive_once_flag = 1; // Immediately set this flag, so that in next interation it won't get executed
        P_ID_rx[4] = '\0'; // Convert the received P_ID into string
        U_ST_rx[4] = '\0'; // Convert the received U_ST into string
        for (int i = 0; i < 4; i++) // Read the P_ID value from internal EEPROM
        {
            orig_PID[i] = read_internal_eeprom(pid_addr[i]) + 48;
        }
        orig_PID[4] = '\0'; // Convert the read P_ID into string
        
        if(mystrcmp(P_ID_rx, orig_PID) == 0) // Compare if both P_ID matches or not
        //As we have to only update the U_ST data if received P_ID from server is same as the original P_ID stored in Client
        {   /* If both P_ID matches */
            client_receive_compare_flag = 1; // Set the Compare flag as High as it denotes the P_ID is same.
            /* Convert the received U_ST into Integer format */
            U_ST = ((U_ST_rx[0] - '0') * 1000) + ((U_ST_rx[1] - '0') * 100) + ((U_ST_rx[2] - '0') * 10) + ((U_ST_rx[3] - '0') * 1);
        }
    }
     
    if(client_receive_compare_flag == 1) // If comparision is true
    {
        client_receive_key = edge_dkp(); // Detect the keypress
        
        /* Display the received U_ST from server into SSDs*/
        ssd[0] = disp_num[(U_ST / 1000) % 10];
        ssd[1] = disp_num[(U_ST / 100) % 10];
        ssd[2] = disp_num[(U_ST / 10) % 10];
        ssd[3] = disp_num[U_ST % 10];

        display(ssd);
    
        if (client_receive_key == 0x0E) { // If switch 1 is pressed on digital keypad
            U_ST++; // Increment the received U_ST value
        }

        if (client_receive_key == 0x0D) { // if switch 2 is pressed on digital keypad
            U_ST--; // Decrement the received U_ST value
        }
        
        if (client_receive_key == 0x0B) // If switch 3 is pressed on digital keypad
        {
            /* Write the received and Modified U_ST value onto internal EEPROM of client */
            write_internal_eeprom(ust_addr[0], ((U_ST / 1000) % 10));
            write_internal_eeprom(ust_addr[1], ((U_ST / 100) % 10));
            write_internal_eeprom(ust_addr[2], ((U_ST / 10) % 10));
            write_internal_eeprom(ust_addr[3], (U_ST % 10));
            
            __delay_ms(1000);
            
            PORTA = PORTA & 0xF0; // Turn off the SSD

            /* Reset all flags used for client receive part */
            key_detected = 0;

            mode_select = 0;

            dp_select = 4;
            
            client_receive_flag = 0;
        }
    }
    else // If received P_ID is different from the original P_ID i.e stored inside client
    {
        /* Restore the state to previous working state */
        key_detected = prev_key; 
        mode_select = prev_mode;
        /* Reset the client receive flags for next receiving */
        client_receive_flag = 0;
        client_receive_once_flag = 0;
        client_receive_compare_flag = 0;
    }
}

int mystrcmp(unsigned char *str1, unsigned char *str2) // Function for comparing original and Received P_IDs
{
        int i = 0;
        
        while(str1[i] != '\0' && str2[i] != '\0')
        {
            if(str1[i] != str2[i])
            {
                return 1;
            }
            i++;
        }
        
        if(str1[i] == '\0' && str2[i] == '\0')
        {
            return 0;
        }
        else
        {
            return 1;
        }
}