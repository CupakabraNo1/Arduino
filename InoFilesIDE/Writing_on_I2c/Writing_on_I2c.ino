
//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define ARRAYSIZE 10
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  int element = 0;
  String results[ARRAYSIZE] = { "Dovla", "Testiramo", "Petlju" };

  while ( element < 3 ){
     for(int n = 0; n < 16; n++) {
        lcd.setCursor(n,0);
        lcd.print(".");
        lcd.setCursor(n,1);
        lcd.print(".");
     }
     lcd.setCursor(3,0);
     lcd.print(results[element]);
     Serial.println(results[element]);
     delay(2000);
     for(int n = 0; n < 16; n++) {
        delay(50);
        lcd.setCursor(n,0);
        lcd.print(" ");
        lcd.setCursor(n,1);
        lcd.print(" ");
     }
     delay(500);
     element = element +1;
  }
  lcd.setCursor(0,0);
  lcd.print("Ispisivanje je");
  lcd.setCursor(0,1);
  lcd.print("Gotovo");
  
}


void loop()
{
}
