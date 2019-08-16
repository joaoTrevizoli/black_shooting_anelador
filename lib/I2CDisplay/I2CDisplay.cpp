#include "I2CDisplay.hpp"

I2CDisplay::I2CDisplay(uint8_t lcdAddr, uint8_t nLine,
  uint8_t nColumns):
    lcd(lcdAddr, nLine, nColumns)
{
  this->_nLine = nLine;
  this->_nColumns = nColumns;
}

void I2CDisplay::begin()
{
  this->lcd.init();
  this->lcd.setBacklight(HIGH);
  this->lcd.clear();
  this->lcd.setCursor(0, 0);
}
