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
