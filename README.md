# Pick_to_light
# Description : 
 * Pick To Light software solutions is a system designed to streamline and automate warehouse or shop floor operations.
 * Automation is mainly done for picking operations thereby increasing efficiency, productivity and picking accuracy. 
 * It primarily uses alphanumeric displays and buttons at storage locations, 
 * to guide the shop floor operator in light-aided manual picking, putting, sorting, and assembling of various components. 
 * 
 * By default, SSD will be turned off and when external interrupt is pressed SSD gets turned ON and U_ST is displayed on the screen.
 * When SWITCH 3 is pressed on Digital Keypad, The mode is switched from U_ST to P_ID.
 * SWITCH 2 is pressed to enter inside any particular mode.
 * When Inside any particular mode, SWITCH 1 is pressed for incrementing the value, SWITCH 2 is pressed for changing the DP position.
 * When SWITCH 3 is pressed from inside any mode, The U_ST and P_ID data is transmitted over using CAN protocol and SSD is turned off.
 * 
 * The Client is also constantly checking for CAN receiving flag, in case the CAN starts receiving the data from any other microcontroller
 * the P_ID data received is compared with the P_ID data stored in CLIENT and if both the same then SSD turns ON.
 * Using SWITCH 1 and SWITCH 2 we can Increment and decrement the received U_ST data and Using SWITCH 3 we can again store the Updated
 * U_ST data inside the External EEPROM.
