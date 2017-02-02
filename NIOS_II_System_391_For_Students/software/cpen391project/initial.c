// initial.c

/*
* Hardware Initialization
*/

#include "project.h"
/**************************************************************************
/* Initialization functions
****************************************************************************/
void Init_Sensor(void)
{
	SENSOR_Control = 0x15; // binary 00010101 - divide by 16 clock, set RTS low, use 8 bits of data, no parity, 1 stop bit,
	SENSOR_Baud = 0x05;	// program for 9600 baud
}
void Init_Touch(void)
{
	//setup 6850 controller
	TOUCH_Control = 0x15;

	//set touch screen baud rate to 9600
	TOUCH_Baud = 0x05;

	//send enable touch command
	TOUCH_TxData = 0x12;
}
