#include "project.h"

//variables to hold the gas values
int mq5;
int mq135;

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
