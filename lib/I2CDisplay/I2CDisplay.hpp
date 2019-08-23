#ifndef I2CDISPLAY
#define  I2CDISPLAY

#include <LiquidCrystal_I2C.h>
#include  <Arduino.h>

class I2CDisplay
{
public:
  LiquidCrystal_I2C lcd;

  I2CDisplay(uint8_t lcdAddr, uint8_t nLine, uint8_t nColumns);
  void begin();

  template<typename T, typename T2>
  void logValue(uint8_t row, T, T2 val);


private:
  uint8_t _nLine;
  uint8_t _nColumns;
  uint32_t lastUpdate = 0;
  uint32_t updateInterval = 100;
};

template<typename T, typename T2>
void I2CDisplay::logValue(uint8_t row, T str, T2 val)
{
    // if(millis() - lastUpdate > updateInterval)
    // {
      
    this->lcd.setCursor(0, row);
    for (size_t i = 0; i < this->_nColumns; i++)
    {
      this->lcd.print(" ");
    }
    this->lcd.setCursor(0, row);
    this->lcd.print("Velocidade: ");
    this->lcd.print(val);
    this->lcd.print(str);
    lastUpdate = millis();

    // }
    
}
#endif
