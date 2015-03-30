#include "LEDMatrix.h"

int dataPin = 7;
int shiftPin = 9;
int latchPin = 8;

// initialize an array of 2 led matrix
LEDMatrix matrix(dataPin,shiftPin,latchPin,2);

// bitmap data for 2 matrix
byte bitmap[] = {
  B00000000, B00000000,
  B00001100, B00111100,
  B00011100, B01111110,
  B00111100, B00001100,
  B00001100, B00011000,
  B00001100, B00110000,
  B00111111, B01111110,
  B00111111, B01111110,
};

void setup() {
  matrix.begin();
}

void loop() {
  matrix.draw(bitmap);
}
