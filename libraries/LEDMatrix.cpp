#include "Arduino.h"
#include "LEDMatrix.h"

LEDMatrix::LEDMatrix(unsigned char dataPin, unsigned char shiftPin, unsigned char latchPin ,unsigned char num) {
  _matrixNum = num;
  _dataPin   = dataPin;
  _shiftPin  = shiftPin;
  _latchPin  = latchPin;
}

void LEDMatrix::begin() {
  pinMode(_latchPin, OUTPUT);
  pinMode(_shiftPin, OUTPUT);
  pinMode(_dataPin, OUTPUT);
}

void LEDMatrix::shiftData(unsigned char data) {
  
  //clear shift register read for sending data
  digitalWrite(_dataPin, LOW);

  // for each bit in dataOut send out a bit
  for (int i=0; i<8; i++) 
  {
    //set shiftPin to LOW prior to sending bit
    digitalWrite(_shiftPin, LOW);

    //sets dataPin to HIGH or LOW depending on pinState
    digitalWrite(_dataPin, data & (1<<i) ? HIGH : LOW);

    //send bit out on rising edge of clock
    digitalWrite(_shiftPin, HIGH);
    digitalWrite(_dataPin, LOW);
  }

  //stop shifting
  digitalWrite(_shiftPin, LOW);
}

void LEDMatrix::draw(unsigned char *bitmap) {
  byte row = B10000000;

  for (byte k = 0; k < 8; k++) {
    // Open up the latch ready to receive data      
    digitalWrite(_latchPin, LOW);
    for(byte m = _matrixNum; m>0; m--) {
      shiftData(row);
      shiftData(~bitmap[_matrixNum*k+m-1]);
    }
    // Close the latch, sending the data in the registers out to the matrix
    digitalWrite(_latchPin, HIGH);
    row = row >> 1;
  }
  
  // eliminate flick in last row
  digitalWrite(_latchPin, LOW);
  for(byte m = _matrixNum; m>0; m--) {
    shiftData(B00000001);
    shiftData(~0);
  }
  // Close the latch, sending the data in the registers out to the matrix
  digitalWrite(_latchPin, HIGH);
}
