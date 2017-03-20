/*
  Multple Serial test

 Receives from the main serial port, sends to the others.
 Receives from serial port 1, sends to the main serial (Serial 0).

 This example works only with boards with more than one serial like Arduino Mega, Due, Zero etc

 The circuit:
 * Any serial device attached to Serial port 1
 * Serial monitor open on Serial port 0:

 created 30 Dec. 2008
 modified 20 May 2012
 by Tom Igoe & Jed Roach
 modified 27 Nov 2015
 by Arturo Guadalupi

 This example code is in the public domain.

 */
int EN1=2;
int EN2=3;
int i=0;
byte mountup[7]={0xff,0x01,0x00,0x08,0x00,0xff,0x08};//上 
byte mountdown[7]={0xff,0x01,0x00,0x10,0x00,0xff,0x10};//下  
byte mountleft[7]={0xff,0x01,0x00,0x04,0xff,0x00,0x04};//左 
byte mountright[7]={0xff,0x01,0x00,0x02,0xff,0x00,0x02};//右 

void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  Serial1.begin(2400);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
}

void loop() {
    digitalWrite(EN1, HIGH);//使能发送
    digitalWrite(EN2, HIGH);//使能发送
    for(i=0;i<7;i++)
    {
       Serial1.write(mountup[i]);
       Serial.write(mountup[i]);
    }
    delay(30000);
    for(i=0;i<7;i++)
       Serial1.write(mountdown[i]);
    delay(30000);
    for(i=0;i<7;i++)
       Serial1.write(mountleft[i]);
    delay(30000);
    for(i=0;i<7;i++)
       Serial1.write(mountright[i]);
    delay(30000);
    digitalWrite(EN1, LOW);//使能发送
    digitalWrite(EN2, LOW);//使能发送
    delay(6000);
    delay(6000);
  // read from port 1, send to port 0:
  if (Serial1.available()) {
    int inByte = Serial1.read();
    Serial.write(inByte);
  }

  // read from port 0, send to port 1:
  if (Serial.available()) {
    int inByte = Serial.read();
    Serial1.write(inByte);
  }
}
