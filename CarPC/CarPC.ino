#include <Keyboard.h>

  On the 101, MKR1000, Zero, and Micro, "Serial" refers to the USB Serial port
const int pinGPS = 2;
const int pinSwitch = 3;
const int pinLeft = 4;
const int pinRight = 5;
unsigned long timeSwitch = 0;
unsigned long timeScreen = 0;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Keyboard.begin();
  pinMode(pinGPS, OUTPUT);
  digitalWrite(pinGPS, HIGH);
  pinMode(pinSwitch, INPUT);
  pinMode(pinLeft, INPUT); 
  pinMode(pinRight, INPUT);  
}

void loop() { 

//////////////////////////////////
// SerialPassthrough sketch
// Created 23 May 2016 by Erik Nyquist
//  
  if (Serial.available()) {      
    Serial1.write(Serial.read());   
  }

  if (Serial1.available()) {     
    Serial.write(Serial1.read());  
  }
//////////////////////////////////

  if (!digitalRead(pinSwitch)) {
    if (!timeSwitch) {
      Keyboard.releaseAll(); 
      Keyboard.press(KEY_LEFT_GUI);
      delay(100);
      Keyboard.press(KEY_TAB);
      delay(100);
      Keyboard.release(KEY_TAB);
      timeSwitch = millis() + 2000;
    } else {
        Keyboard.releaseAll();    
        timeSwitch = 0;
      }
  }

  if (digitalRead(pinLeft) != digitalRead(pinRight)) {
    if (timeSwitch) {        
      Keyboard.press(KEY_TAB);
      delay(100);
      Keyboard.release(KEY_TAB); 
      timeSwitch = millis() + 2000; 
    } else {
        if (!timeScreen) {
          Keyboard.releaseAll(); 
          Keyboard.press(KEY_LEFT_GUI);
          delay(100);
          timeScreen = millis() + 2000;
        } else {
            if (!digitalRead(pinLeft)) {
               Keyboard.press(KEY_RIGHT_ARROW);
               Keyboard.release(KEY_RIGHT_ARROW);
               Keyboard.press(KEY_RIGHT_ARROW);
               Keyboard.release(KEY_RIGHT_ARROW);
               Keyboard.press(KEY_RIGHT_ARROW);
               Keyboard.release(KEY_RIGHT_ARROW);               
               Keyboard.press(KEY_UP_ARROW);
               Keyboard.release(KEY_UP_ARROW);
               Keyboard.press(KEY_UP_ARROW);
               Keyboard.release(KEY_UP_ARROW);
               delay(100);
               timeScreen = millis() + 2000;             
            } else {
               Keyboard.press(KEY_LEFT_ARROW);
               Keyboard.release(KEY_LEFT_ARROW);
               Keyboard.press(KEY_LEFT_ARROW);
               Keyboard.release(KEY_LEFT_ARROW);
               Keyboard.press(KEY_LEFT_ARROW);
               Keyboard.release(KEY_LEFT_ARROW); 
               Keyboard.press(KEY_UP_ARROW);
               Keyboard.release(KEY_UP_ARROW);
               Keyboard.press(KEY_UP_ARROW);
               Keyboard.release(KEY_UP_ARROW);
               delay(100);
               timeScreen = millis() + 2000;
              }
          }
      }  
  }

  if (timeSwitch && timeSwitch < millis()) {
    Keyboard.releaseAll();    
    timeSwitch = 0;
  }

  if (timeScreen && timeScreen < millis()) {
    Keyboard.releaseAll();    
    timeScreen = 0;
  }
}

