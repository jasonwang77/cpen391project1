//arduino.c


#include "project.h"
/*
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
		printf("mq2 = %d, ", mq2_Val);
	//data for mq4
		mq4_b1 = getcharSensor();
		mq4_b2 = getcharSensor();
		mq4_Val = ((mq4_b1 & 0x1f) << 5) | (mq4_b2 & 0x1f) ;
		printf("mq4 = %d \n", mq4_Val);

}
