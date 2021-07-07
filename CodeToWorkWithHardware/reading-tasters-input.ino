#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
const String in_1_values = "ABCDEFGH";
const String in_2_values = "IJKLMNOP";
const String in_3_values = "RSTUVWXYZ";
const String in_4_values = "0123456789";
const String in_5_values = ".,:;-/|";
const String in_6_values = "";



LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//pin address
int in_1 = 6;
int in_1_counter = -1;
int in_2 = 7;
int in_2_counter = -1;
int in_3 = 8;
int in_3_counter = -1;
int in_4 = 9;
int in_4_counter = -1;
int in_5 = 10;
int in_5_counter = -1;
int in_6 = 11;
int in_6_counter = -1;
int in_7 = 12;
int in_7_counter = -1;

// variable to store the read value  
int val = 0;  
int ledPin = 13;  // LED connected to digital pin 13    

void setup(){
  Serial.begin(9600);
  Serial.print("System ready!\n");
  lcd.init();                      
  lcd.init();
  lcd.backlight();

  pinMode(ledPin, OUTPUT);
  pinMode(in_1, INPUT); 
  pinMode(in_2, INPUT); 
  pinMode(in_3, INPUT); 
  pinMode(in_4, INPUT); 
  pinMode(in_5, INPUT); 
  pinMode(in_6, INPUT); 
  pinMode(in_7, INPUT); 
}


char message[32];
int messagePos = 0;
char currentChar;


int cursorPosition = 0;
int cursorRow = 0;
void loop(){
    for(int i=6 ; i<=12 ; i++) {
      checkPush(i);
    }
    delay(75);
}

void checkPush(int num){
  val = digitalRead(num);
  if (val == HIGH) {
    switch(num) {
        case 6:
          in_1_counter++;
          printChar(in_1_values[in_1_counter % 8], cursorPosition, cursorRow);
          break;        
      case 7:
          in_2_counter++;
          printChar(in_2_values[in_2_counter % 8], cursorPosition, cursorRow);
          break;  
      case 8:
          in_3_counter++;
          printChar(in_3_values[in_3_counter % 9], cursorPosition, cursorRow);
          break;  
      case 9:
          in_4_counter++;
          printChar(in_4_values[in_4_counter % 10], cursorPosition, cursorRow);
          break;  
      case 10:
          in_5_counter++;
          printChar(in_5_values[in_5_counter % 7], cursorPosition, cursorRow);
          break;  
      case 11:
        if(cursorPosition == 15 && cursorRow == 0 ){
          message[cursorPosition] = currentChar;
          printChar(' ', cursorPosition, cursorRow);
          
          cursorRow++;
          cursorPosition = -1;
        } 
        if (cursorPosition == 15 && cursorRow == 1){
          clearDisplay();
          resetCursor();
        }
        else {
          delay(50);
          message[cursorPosition] = currentChar;
          cursorPosition++;
          printChar(' ', cursorPosition, cursorRow);
          
          delay(50);
          clearCounters();
        }
        break;
      case 12:
          enterWrittenCommand();
          break;  
    }
    digitalWrite(ledPin, HIGH); 
  } else {
    digitalWrite(ledPin, LOW); 
  }
}


//WORK WITH DISPALY
//int cursorPosition = 0;
//int cursorRow = 0;


void printChar(char c, int cursorPosition, int cursorRow) {
  delay(100);
  lcd.setCursor(cursorPosition,cursorRow);
  lcd.print(c);
  currentChar = c;
}

void enterWrittenCommand() {
  clearDisplay();
  resetCursor();
  cursorPosition++;
  Serial.print(message);
  message[32] ;
}

void resetCursor() {
  cursorPosition = -1;
  cursorRow = 0;
  lcd.setCursor(0,0);
}

void resetDisplay() {
  lcd.setCursor(0,0);
  lcd.print("................");
  lcd.setCursor(0,1);
  lcd.print("................");
}
void reserDisplayFade() {
  for (int i = 0; i < 16; i++) {
      lcd.setCursor(i,0);
      lcd.print(".");
      lcd.setCursor(i,1);
      lcd.print(".");
      delay(50);
    } 
}

void clearDisplay() {
  clearCounters();
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");
}
void clearDisplayFade() {
  for (int i = 0; i < 16; i++) {
      lcd.setCursor(i,0);
      lcd.print(" ");
      lcd.setCursor(i,1);
      lcd.print(" ");
      delay(50);
    } 
}
void clearCounters(){
  in_1_counter = -1;
  in_2_counter = -1;
  in_3_counter = -1;
  in_4_counter = -1;
  in_5_counter = -1;
  in_6_counter = -1;
  in_7_counter = -1;
}
