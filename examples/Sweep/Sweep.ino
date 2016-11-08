/* Sweep
 by BARRAGAN <http://barraganstudio.com> 
 This example code is in the public domain.

 modified 28 May 2015
 by Michael C. Miller
 modified 8 Nov 2013
 by Scott Fitzgerald

 http://arduino.cc/en/Tutorial/Sweep
*/ 

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
 

void setup() 
{ 
  myservo.attach(D6);  // attaches the servo on GIO2 to the servo object 
} 
 
void loop() 
{ 
  int pos;
  myservo.write(0);
  delay(1000);  
  myservo.write(90);
  delay(1000);  
  myservo.write(180);
  delay(1000);  
} 

