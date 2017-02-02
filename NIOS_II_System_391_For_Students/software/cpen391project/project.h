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






// #defined constants representing values we write to the graphics 'command' register to get
// it to do something. You will add more values as you add hardware to the graphics chip
// Note DrawHLine, DrawVLine and DrawLine at the moment do nothing - you will modify these

#define DrawHLine		1
#define DrawVLine		2
#define DrawLine		3
#define PutAPixel		0xA
#define GetAPixel		0xB
#define ProgramPaletteColour   	0x10

/*******************************************************************************************
** This macro pauses until the graphics chip status register indicates that it is idle
*******************************************************************************************/

//#define WAIT_FOR_GRAPHICS		while((GraphicsStatusReg & 0x0001) != 0x0001);

//Predefined Colour Values
//Use the symbolic constants below as the values to write to the Colour Register
//When you ask the graphics chip to draw something. These values are also returned
//By the read pixel command

// the header file "Colours.h" contains symbolic names for all 256 colours e.g. RED
// while the source file ColourPaletteData.c contains the 24 bit RGB data
// that is pre-programmed into each of the 256 palettes




#define GraphicsCommandReg   		(*(volatile unsigned short int *)(0x84000000))
#define GraphicsStatusReg   		(*(volatile unsigned short int *)(0x84000000))
#define GraphicsX1Reg   		(*(volatile unsigned short int *)(0x84000002))
#define GraphicsY1Reg   		(*(volatile unsigned short int *)(0x84000004))
#define GraphicsX2Reg   		(*(volatile unsigned short int *)(0x84000006))
#define GraphicsY2Reg			(*(volatile unsigned short int *)(0x84000008))
#define GraphicsColourReg		(*(volatile unsigned short int *)(0x8400000E))
#define GraphicsBackGroundColourReg   		(*(volatile unsigned short int *)(0x84000010))



#define MENU	0
#define CH4 	1
#define SMOKE 	2
#define NGAS	3
#define AIRQ	4
int current_state;


/* a data type to hold a point/coord */
typedef struct{
int x, y; } Point;

//initial.c
/**************************************************************************
* Initialization functions
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

//Graphics.c
/*****************************************************************************
* Graphics
*****************************************************************************/
void graph_updateGasValue(int val);
void graph_showGasFrame(int gas);
void graph_goto_menu(void);

//Bresenhams_Line_Drawing_Algorithm.c
void Line(int x1, int y1, int x2, int y2, int Colour);

//OutGraphicsCharFont2.c
void OutGraphicsCharFont2a(int x, int y, int colour, int backgroundcolour, int c, int Erase);


//arduino.c
/*
 * Functions to get data from Arduino and update the gas values
 */
int getcharSensor( void );
//updates the gas value
void update(void);
