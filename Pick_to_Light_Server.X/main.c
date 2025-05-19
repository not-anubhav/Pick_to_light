#include "main.h"
#include "can.h"

void init_config() 
{
    PEIE = 1;
    GIE = 1;
    init_can(); // Initialize CAN protocol
    init_uart(); // Initialize UART interrupt
}

void can_demo()
{ 
    
    if(tx) // When tx flag is set in can receive condition inside main function
    {
        if(flag == 0) // Flag is also set in can receive condition in main function
        {
            if(i <= 3) // If input characters is less than equal to 3 i.e PID value
            {

                puts("\r\n"); // Put a new line on tera term
                ch = '\0'; // Reset the character variable for next character input
                puts("Enter P_ID -> "); // Print prompt for entering PID value
                while(ch != '\r') // Until new line is input i.e enter is pressed
                {
                    if(ch != '\0') 
                    {
                        putch(ch); // Put the entered character on tera term
                        if(i <= 3 && ch != '\r')
                        {
                            send_arr[i] = ch; // Store the input character inside send_arr array
                            i++; // Increment input character count
                        }
                        ch = '\0'; // Reset character variable for next input character
                    }
                }
                puts("\r\n"); // After enter is pressed print a new line on tera term
                if (i < 4) // If input characters are less than 4 
                {
                    /* Add leading zeros in input data to make it 4 characters*/
                    int padding = 4 - i;

                    for (int j = i - 1; j >= 0; j--) {
                        send_arr[j + padding] = send_arr[j];
                    }

                    for (int j = 0; j < padding; j++) {
                        send_arr[j] = '0';
                    }

                    i = 4;
                }

            }
            else // After PID is entered i becomes more than 3 now enter the UST value
            {
                ch = '\0'; // Reset the character variable for next input character
                puts("Enter U_ST -> "); // Print prompt on tera term
                while(ch != '\r') // Until enter is pressed
                {
                    if(ch != '\0') // Check is input character is not a null character i.e wait for input character
                    {
                        putch(ch); // Put the input character on tera term
                        if(i <= 7 && ch != '\r') 
                        {
                            send_arr[i] = ch; // Add the input character inside send_arr array
                            i++;
                        }
                        ch = '\0'; // Reset the character variable ch for next input character
                    }
                }
                puts("\n\r"); // Print a newline on tera term after enter is pressed
                if (i < 8) 
                {
                    /* In case the input characters for UST value is less than 4, Add leading zeros to make it 4*/
                    int padding = 8 - i; 

                    for (int j = i - 1; j >= 4; j--) {
                        send_arr[j + padding] = send_arr[j];
                    }

                    for (int j = 4; j < 4 + padding; j++) {
                        send_arr[j] = '0';
                    }

                    i = 8;
                }
               
				i = 0; // Reset the i value
				flag = 1; // Set the flag for transmission
            }
        }
        
        if(flag == 1) // If flag is set
        {
            /* Fill the can_payload with data to send to client present in send_arr array*/
            can_payload[D0] = send_arr[4];
			can_payload[D1] = send_arr[5];
			can_payload[D2] = send_arr[6];
			can_payload[D3] = send_arr[7];
			can_payload[D4] = send_arr[0];
			can_payload[D5] = send_arr[1];
			can_payload[D6] = send_arr[2];
			can_payload[D7] = send_arr[3];
            
            can_transmit(); // Transmit the entered data to the client
            
            for(int j = 0; j < 9; j++)  // Reset the send_arr with null character for next use
            {
                send_arr[j] = '\0';
            }
            flag = 0; // reset the flag
			tx = 1; // set the tx flag
        }
    }
}

void main(void)
{
    init_config(); // Initialize all the necessary things
    
    while(1)
    {
        can_demo();
        
        if (can_receive()) // If data is received using CAN and the flag is set
		{
			char pid[5] = {'\0'}; // Initialize a pid array with 0
			char ust[5] = {'\0'}; // Initialize a ust array with 0
			
            /* Filter the ust data from received data into separate ust array */
			ust[0] = can_payload[D0];
			ust[1] = can_payload[D1];
			ust[2] = can_payload[D2];
			ust[3] = can_payload[D3];
            ust[4] = '\0'; // convert the ust array to string

            /* Filter the pid data from received data into separate pid array */
			pid[0] = can_payload[D4];
			pid[1] = can_payload[D5];
			pid[2] = can_payload[D6];
			pid[3] = can_payload[D7];
            pid[4] = '\0'; // convert the pid array to string

			puts("\n\r"); // Print a new line on tera term
			puts("P_ID -> "); // Print the received PID value on tera term
			puts(pid);
            puts("\n\r");
			puts("U_ST -> "); // Print the received UST value on tera term
			puts(ust);
			puts("\n\r"); // Print a new line on tera term
            
            for (int j = 0; j < 9; j++) 
            {
                send_arr[j] = '\0'; // Reset all the send_arr values to null character
            }

            enter_flag = 1; // Flag for detecting enter character on tera term
		}
        
        if(ch == '\r') // If enter is pressed
        {
            if(enter_flag == 1) // And enter flag is set
            {
                tx = 1; // Set the tx flag used inside can demo function for further operations
                /* reset all the other flags*/
                flag = 0;
                i = 0;
                enter_flag = 0;
            }
            putch(ch); // Put the enter on tera term to print a newline
            ch = '\0'; // Reset the character variable ch which is used is isr to null character for next input
        }
    }
}