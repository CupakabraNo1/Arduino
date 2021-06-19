
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include "CommandLine.h"



LiquidCrystal_I2C lcd(0x27,20,4);


void setup() {
  Serial.begin(9600);
  lcd.init(); 
  lcd.backlight();

}

void loop() {
  bool recived = getCommandLineFromSerialPort(CommandLine);
  if(recived) DoMyCommand(CommandLine);
}
