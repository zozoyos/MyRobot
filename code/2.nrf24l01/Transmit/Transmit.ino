/* -----------------------------------------------------------------------------
 - File:      nRF24l01 Transmit Test
 - Copyright: Copyright (C) 2015 SunFounder. For details, check License folder.
 - Date:      2015/7/21
 * -----------------------------------------------------------------------------
 - Overview
  - This project was written to test nRF24l01 module. If it runs, arduino will 
    reads Analog values on A0, A1 and transmits them over a nRF24L01 Radio Link 
    to another transceiver.
 - Request
   - FR24 library
 - Connections
   - nRF24L01 to Arduino
     1 GND   	 GND
     2 VCC	 3V3
     3 CE	 D9
     4 CSN	 D10
     5 SCK	 D13
     6 MOSI	 D11
     7 MISO	 D12
     8 UNUSED	
   - Joystick to Arduino
     GND         GND
     VCC         5V
     X           A0
     Y           A1
 * ---------------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
/* Ports ---------------------------------------------------------------------*/
//#define CE_PIN   9
//#define CSN_PIN 10
#define JOYSTICK_X A0
#define JOYSTICK_Y A1
/* nRF24l01 ------------------------------------------------------------------*/
// NOTE: the "LL" at the end of the constant is "LongLong" type
const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe
//RF24 radio(CE_PIN, CSN_PIN); // Create a Radio
/* Joystick ------------------------------------------------------------------*/
int joystick[6]; // 2 element array holding Joystick readings
/* ---------------------------------------------------------------------------*/
#define B_UP 2
#define B_DOWN 4
#define B_LEFT 5
#define B_RIGHT 3

int E1 = 11;  
int M1 = 12;
int E2 = 9;  
int M2 = 10;

/*
 - setup function
 * ---------------------------------------------------------------------------*/
void setup()
{
  //radio.begin();
  //radio.setRetries(0, 15);
  //radio.setPALevel(RF24_PA_HIGH);
  //radio.openWritingPipe(pipe);
  Serial.begin(9600);

  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
}

/*
 - loop function
 * ---------------------------------------------------------------------------*/
void loop()
{
  joystick[0] = analogRead(JOYSTICK_X);
  joystick[1] = analogRead(JOYSTICK_Y);
  
  joystick[2] = digitalRead(B_UP);
  joystick[3] = digitalRead(B_DOWN);
  joystick[4] = digitalRead(B_LEFT);
  joystick[5] = digitalRead(B_RIGHT);

  int valueX = map(joystick[0],0,1024,-101,99);
  int valueY = map(joystick[1],0,1024,-101,99);
  //Serial.print("X = ");
  //Serial.print(valueX);
  //Serial.print(", Y = ");
  //Serial.println(valueY);
  int swapY;
  
  if (valueY > 2) {
    swapY = map(valueY,2,99,200,2);
    Serial.print("Y = ");
    Serial.println(swapY);
    digitalWrite(M1,HIGH);
    digitalWrite(M2,HIGH);
    analogWrite(E1, swapY);
    analogWrite(E2, swapY);
  }
  if (valueY >= -2 && valueY <= 2 && valueX >= -2 && valueX <= 2) {
    digitalWrite(M1,LOW);
    digitalWrite(M2,LOW);
    analogWrite(E1, 0);
    analogWrite(E2, 0);
  }
  if (valueY < -2) {
    swapY = map(valueY,-2,-99,200,2);
    Serial.print("Y = ");
    Serial.println(swapY);
    digitalWrite(E1,HIGH);
    digitalWrite(E2,HIGH);
    analogWrite(M1, -swapY);
    analogWrite(M2, -swapY);
  }
  
  
  //radio.write( joystick, sizeof(joystick) );
}
