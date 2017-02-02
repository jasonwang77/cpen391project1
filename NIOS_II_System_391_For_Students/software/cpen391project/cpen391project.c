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

//variables to hold the gas values
int mq5;
int mq135;

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

/********************************************************************************
 * Functions to get data from Arduino and update the gas values
 */
int getcharSensor( void )
{
 // poll Rx bit in 6850 status register. Wait for it to become '1'
 // read received character from 6850 RxData register.

	while ( (SENSOR_Status & 0x01) == 0x00 ) {}
	return SENSOR_RxData;
}

//updates the gas value
void update(void){
	int control;
	int mq5_b1;
	int mq5_b2;
	int mq135_b1;
	int mq135_b2;
	int mq2_b1;
	int mq2_b2;
	int mq4_b1;
	int mq4_b2;
	int mq5_Val;
	int mq135_Val;
	int mq2_Val;
	int mq4_Val;

	//check control,
	do{
		control = getcharSensor();
	}while(control != 0x80);

	//data for mq5
		mq5_b1 = getcharSensor();
		mq5_b2 = getcharSensor();
		mq5_Val = ((mq5_b1 & 0x1f) << 5) | (mq5_b2 & 0x1f) ;
		printf("mq5 = %d, ", mq5_Val);
	//data for mq135
		mq135_b1 = getcharSensor();
		mq135_b2 = getcharSensor();
		mq135_Val = ((mq135_b1 & 0x1f) << 5) | (mq135_b2 & 0x1f) ;
		printf("mq135 = %d, ", mq135_Val);
	//data for mq2
		mq2_b1 = getcharSensor();
		mq2_b2 = getcharSensor();
		mq2_Val = ((mq2_b1 & 0x1f) << 5) | (mq2_b2 & 0x1f) ;
		printf("mq2 = %d, ", mq5_Val);
	//data for mq4
		mq2_b1 = getcharSensor();
		mq2_b2 = getcharSensor();
		mq2_Val = ((mq2_b1 & 0x1f) << 5) | (mq2_b2 & 0x1f) ;
		printf("mq4 = %d \n", mq5_Val);

}

/********************************************************************************
 * Main function
 *******************************************************************************/

void main()
{
   printf("Starting cpen391 project\n");

   Init_Sensor();
   Init_Touch();

   while(TRUE){
//	   printf("Waiting for data...\n");
	   WaitForData();
//	   printf("data received\n");
	   //determine if the data came from the screen or from SENSOR
	   if(ScreenTouched()){
		   //if the data came from touch screen, decode the coordinates
		   Point p1 = GetPress();
		   Point p2 = GetRelease();
		   printf("Press point: x = %d, y = %d\n", p1.x, p1.y);
		   printf("Release point: x = %d, y = %d\n", p2.x, p2.y);

		   //TODO: What happens when the coordinate is a button?

	   }
	   if(SensorReceivedData()){
		   //if the data is from the Arduino, update gas value 
			update(); 
//			printf("calling update\n");
	   }
   }
}
