//project.h

#define SENSOR_Control (*(volatile unsigned char *)(0x84000210))
#define SENSOR_Status (*(volatile unsigned char *)(0x84000210))
#define SENSOR_TxData (*(volatile unsigned char *)(0x84000212))
#define SENSOR_RxData (*(volatile unsigned char *)(0x84000212))
#define SENSOR_Baud (*(volatile unsigned char *)(0x84000214))
#define TOUCH_Control (*(volatile unsigned char *)(0x84000230))
#define TOUCH_Status (*(volatile unsigned char *)(0x84000230))
#define TOUCH_TxData (*(volatile unsigned char *)(0x84000232))
#define TOUCH_RxData (*(volatile unsigned char *)(0x84000232))
#define TOUCH_Baud (*(volatile unsigned char *)(0x84000234))
#define TRUE 1
#define FALSE 0



#define switches (volatile char *) 0x0002000
#define hex0_1 (volatile char *) 0x0002030
#define leds (char *) 0x0002010
#define keys (char *) 0x0002060


#define XRES 800
#define YRES 480
#include "OutGraphicsCharFont1.h"
#include "OutGraphicsCharFont2.h"

#define MENU	0
#define CH4 	1
#define SMOKE 	2
#define NGAS	3
#define AIRQ	4
int current_state = MENU;	// initialize it to menu

/* a data type to hold a point/coord */
typedef struct{
int x, y; } Point;

//initial.c
/**************************************************************************
/* Initialization functions
****************************************************************************/
void Init_Sensor(void);
void Init_Touch(void);

//TouchScreen.c
/*****************************************************************************
   tests for screen touched or data received from SENSOR
*****************************************************************************/
int ScreenTouched(void);
int SensorReceivedData(void);
/*****************************************************************************
**   wait for screen or SENSOR
*****************************************************************************/
void WaitForData();
/*****************************************************************************
* Touch screen get points functions
*****************************************************************************/
Point GetPress(void);
Point GetRelease (void);
int getcharTouch( void );

//arduino.c
/*
 * Functions to get data from Arduino and update the gas values
 */
int getcharSensor( void );
//updates the gas value
void update(void);
