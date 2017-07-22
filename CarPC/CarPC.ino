#include <Keyboard.h>

// seleção dos pinos do Leonardo.
const int pinGPS = 2;
const int pinSwitch = 3;
const int pinLeft = 4;
const int pinRight = 5;
const int pinKeyOFF = 6;

// variáveis de estado.
bool stateLeft = false;
bool stateRight = false;
int timeControl = 0;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Keyboard.begin();
  pinMode(pinGPS, OUTPUT);
  digitalWrite(pinGPS, HIGH);
  pinMode(pinSwitch, INPUT_PULLUP);
  pinMode(pinLeft, INPUT_PULLUP);
  pinMode(pinRight, INPUT_PULLUP);
  pinMode(pinKeyOFF, INPUT_PULLUP); // para interromper o loop em caso de perda de controle. Ligar o pino no GND.
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

  while (!digitalRead(pinKeyOFF));

  if (digitalRead(pinLeft) != digitalRead(pinRight)) {
    if (!digitalRead(pinLeft)) {
      if (stateRight) {
        Keyboard.releaseAll();
        stateRight = false;
      }
      if (stateLeft) {
        Keyboard.press(KEY_TAB);
        delay(200);
      } else {
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_TAB);
        delay(200);
        stateLeft = true;
      }
    } else {
      if (stateLeft) {
        Keyboard.releaseAll();
        stateLeft = false;
      }
      if (stateRight) {
        Keyboard.press(KEY_LEFT_ARROW);
        delay(200);

      } else {
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_ARROW);
        delay(200);
        stateLeft = true;
      }
    }
    timeControl = 1;
  }

  if (timeControl) {
    timeControl++;
  }

  if (!digitalRead(pinSwitch) || timeControl > 2000) {
    stateLeft = false;
    stateRight = false;
    Keyboard.releaseAll();
    timeControl = 0;
  }
}
