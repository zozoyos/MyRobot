/* -----------------------------------------------------------------------------
 - File:      Servo Test
 - Copyright: Copyright (C) 2015 SunFounder. For details, check License folder.
 - Date:      2015/7/21
 * -----------------------------------------------------------------------------
 - Overview
  - This project was written to test a Servo, if it runs, the Servo will sweep.
 * ---------------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include <Servo.h> 
/* Private variables ---------------------------------------------------------*/
Servo myservo;  // create servo object to control a servo 
int pos = 0;    // variable to store the servo position 
/* ---------------------------------------------------------------------------*/
 
/*
 - setup function
 * ---------------------------------------------------------------------------*/
void setup() 
{ 
  myservo.attach(2);  // attaches the servo on pin 2 to the servo object 
} 
 
/*
 - loop function
 * ---------------------------------------------------------------------------*/
void loop() 
{ 
  myservo.write(0);
} 
