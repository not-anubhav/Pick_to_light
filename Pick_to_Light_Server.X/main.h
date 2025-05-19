#ifndef MAIN_H
#define MAIN_H

#include <xc.h>
#include "uart.h"
#include "can.h"

#define _XTAL_FREQ 20000000

#define TRUE			1
#define FALSE			0


unsigned char can_payload[13];
int i = 0, flag = 0, tx = 0;
unsigned char send_arr[9] = {'\0'};
unsigned char ch;
volatile unsigned char enter_flag = 0;

void can_demo();


#endif