#ifndef PL_H
#define PL_H

#include <xc.h>
#include "can.h"

#define _XTAL_FREQ 20000000

#define TRUE			1
#define FALSE			0

unsigned int key_detected = 0;
unsigned int key_press;
unsigned int mode1_keypress;
unsigned int mode2_keypress;
unsigned int client_receive_key;

unsigned char mode1_once = 0;
unsigned char mode2_once = 0;
unsigned char client_receive_once_flag = 0;

unsigned char mode_switch = 0;
unsigned char mode_select = 0;
char dp_select = 4;

unsigned char disp_mode1[] = {0xE5, 0x40, 0x6E, 0xCC};
unsigned char disp_mode2[] = {0x8F, 0x40, 0x84, 0xE9};
unsigned char disp_num[] = {0xE7, 0x21, 0xCB, 0x6B, 0x2D, 0x6E, 0xEE, 0x23, 0xEF, 0x6F};
unsigned char ssd[4];
unsigned char ust_addr[4] = {0x00, 0x01, 0x02, 0x03};
unsigned char pid_addr[4] = {0x04, 0x05, 0x06, 0x07};
unsigned char can_payload[5];
unsigned char U_ST_rx[5];
unsigned char P_ID_rx[5];
unsigned char orig_PID[5];

unsigned char c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0, c7 = 0, c8 = 0;
unsigned int U_ST;

unsigned char client_receive_flag = 0;
unsigned char client_receive_compare_flag = 0;

unsigned int prev_key;
unsigned char prev_mode;


void init_external_interrupt();
void __interrupt() isr(void);
void init_dkp();
unsigned char edge_dkp();
void init_SSD();
void display(unsigned char *ssd);
void mode1();
void mode2();
unsigned char read_internal_eeprom(unsigned char addr);
void write_internal_eeprom(unsigned char addr, unsigned char data);
void client_receive();
int mystrcmp(unsigned char *str1, unsigned char *str2);

#endif