#ifndef LEDMATRIX_H
#define LEDMATRIX_H

class LEDMatrix {
  public:
    LEDMatrix(unsigned char dataPin, unsigned char shiftPin, unsigned char latchPin ,unsigned char num);
    void begin();
    void draw(unsigned char *bitmap);

  private:
    void shiftData(unsigned char data);
    unsigned char _matrixNum;
    unsigned char _dataPin;
    unsigned char _latchPin;
    unsigned char _shiftPin;
};

#endif
