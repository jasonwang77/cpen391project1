//TouchScreen.c

#include "project.h"
/*****************************************************************************
   tests for screen touched or data received from SENSOR
*****************************************************************************/
int ScreenTouched(void)
{
	// return TRUE if any data received from 6850 connected to touchscreen
	// or FALSE otherwise
	if ( (TOUCH_Status & 0x01) == 0x00 )
		return FALSE;
	else{
		return TRUE;
	}
}

int SensorReceivedData(void)
{
	// return TRUE if any data received from 6850 connected to touchscreen
	// or FALSE otherwise
	if ( (SENSOR_Status & 0x01) == 0x00 )
		return FALSE;
	else{
		return TRUE;
	}
}

/*****************************************************************************
**   wait for screen or SENSOR
*****************************************************************************/
void WaitForData()
{
	while(!SensorReceivedData() && !ScreenTouched())
				;
}

/*****************************************************************************
* Touch screen get points functions
*****************************************************************************/
Point GetPress(void)
{
	Point p1;
	// wait for a pen down command then return the X,Y coord of the point
	// calibrated correctly so that it maps to a pixel on screen
	int b1;

	do{
		b1 = getcharTouch();
	}while(b1 != 0x81);

	int b2 = getcharTouch();
	int b3 = getcharTouch();
	int b4 = getcharTouch();
	int b5 = getcharTouch();

	p1.x = ((b3 & 0x1f) << 7) | (b2 & 0x7e);
	p1.y = ((b5 & 0x1f) << 7) | (b4 & 0x7e);
	p1.x = p1.x * 100 / 512;
	p1.y = p1.y * 1000 / 8533;
	return p1;
}

Point GetRelease (void)
{
	Point p1;
	// wait for a pen up command then return the X,Y coord of the point
	// calibrated correctly so that it maps to a pixel on screen
		int b1;

		do{
			b1 = getcharTouch();
		}while(b1 != 0x80);

		int b2 = getcharTouch();
		int b3 = getcharTouch();
		int b4 = getcharTouch();
		int b5 = getcharTouch();

		p1.x = ((b3 & 0x1f) << 7) | (b2 & 0x7e);
		p1.y = ((b5 & 0x1f) << 7) | (b4 & 0x7e);
		p1.x = p1.x * 100 / 512;
		p1.y = p1.y * 1000 / 8533;
		return p1;
}

int getcharTouch( void )
{
	while ( (TOUCH_Status & 0x01) == 0x00 ) {}
	return TOUCH_RxData;
}
