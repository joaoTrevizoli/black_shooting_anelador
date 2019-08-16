#ifndef I2CDISPLAY
#define  I2CDISPLAY

#include <LiquidCrystal_I2C.h>
#include  <Arduino.h>

class I2CDisplay
{
public:
  I2CDisplay(uint8_t lcdAddr, uint8_t nLine, uint8_t nColumns);
  void begin();

  template<typename T>
  void logSensorReading(uint8_t row, T, float val);


private:
  LiquidCrystal_I2C lcd;
  uint8_t _nLine;
  uint8_t _nColumns;
};

template<typename T>
void I2CDisplay::logSensorReading(uint8_t row, T str, float val)
{
    this->lcd.setCursor(0, row);
    for (size_t i = 0; i < this->_nColumns; i++)
    {
      this->lcd.print(" ");
    }

    this->lcd.setCursor(0, row);
    this->lcd.print(val);
    this->lcd.print(" ");
    this->lcd.print(str);
}
#endif
