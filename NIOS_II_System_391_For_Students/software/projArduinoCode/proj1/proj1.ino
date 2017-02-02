float mq5=A0;
float mq135 = A1; 
float mq2 = A2; 
float mq4 = A3; 
int mq5_raw; //value read from 0-1023 using analog read， value stored in first 10 bits of 16 bit int 
int mq135_raw; 
int mq2_raw; 
int mq4_raw; 

//each 16 bit int value split into two 8 bit bytes 
byte mq5_b1; //contains bits 9-5 of raw in bits 4-0
byte mq5_b2; //contains bits 4-0 of raw in bits 4-0 
byte mq135_b1;
byte mq135_b2; 
byte mq2_b1; 
byte mq2_b2;
byte mq4_b1; 
byte mq4_b2; 

//control bytes to to tell nios which sensor got this value 
byte mq5_control = 0x80;
byte mq135_control = 0xe0;
byte mq2_control = 0x40;
byte mq4_control = 0x60; 

void setup()
{
  pinMode(mq5,INPUT);
  pinMode(mq135, INPUT); 
  pinMode(mq2,INPUT); 
  pinMode(mq4,INPUT); 
  Serial.begin(9600);
}

void loop()
{
  mq5_raw = analogRead(mq5);
  mq135_raw = analogRead(mq135); 
  mq2_raw = analogRead(mq2);
  mq4_raw = analogRead(mq4);
  
/*  Serial.print("mq5 raw value: ");
  Serial.println(mq5_raw, HEX);
  Serial.print("    mq135 raw value: ");
  Serial.println(mq135_raw, HEX); 
*/

  mq5_b1 = (mq5_raw & 0x03e0) >> 5; 
  mq5_b2 = (mq5_raw & 0x001f); 
  
  mq135_b1 = (mq135_raw & 0x03e0) >> 5; 
  mq135_b2 = (mq135_raw & 0x001f); 

  mq2_b1 = (mq2_raw & 0x03e0) >> 5; 
  mq2_b2 = (mq2_raw & 0x001f); 

  mq4_b1 = (mq4_raw & 0x03e0) >> 5; 
  mq4_b2 = (mq4_raw & 0x001f); 
  
/*  Serial.print("mq5 byte 1: ");
  Serial.print(mq5_b1, HEX);
  Serial.print("   mq5 byte 2: ");
  Serial.println(mq5_b2, HEX);
*/
  
  //send control message for mq5 followed by the two bytes containing data 
  Serial.write(mq5_control);
  Serial.write(mq5_b1);
  Serial.write(mq5_b2); 
  
//  Serial.write(mq135_control); 
  Serial.write(mq135_b1);
  Serial.write(mq135_b2);

//  Serial.write(mq2_control);
  Serial.write(mq2_b1);
  Serial.write(mq2_b2); 

//  Serial.write(mq4_control);
  Serial.write(mq4_b1);
  Serial.write(mq4_b2); 
  
  delay(1000); 
}
