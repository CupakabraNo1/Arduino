#include <string.h>
#include <stdlib.h>

#define print2(x,y) (Serial.print(x), Serial.println(y))

#define CR '\r'
#define LF '\n'
#define BS '\b'
#define NULLCHAR '\0'
#define SPACE ' '

#define COMMAND_BUFFER_LENGTH 25
char CommandLine[COMMAND_BUFFER_LENGTH + 1];

const char *delimiters = ", \n";
const char *wordDelimiter = "\n";

//calculations
const char *addCommandToken             = "add";                 
const char *subtractCommandToken        = "sub";
const char *multiplyCommandToken        = "mul";
const char *devideCommandToken          = "dev";

//cmd commands
const char *echoCommandToken            = "echo";
const char *listCommandToken            = "ls";
const char *changeDirectoryCommandToken = "cd";
    

bool getCommandLineFromSerialPort(char * commandLine) {
  static uint8_t charsRead = 0;                      
  //note: COMAND_BUFFER_LENGTH must be less than 255 chars long
  //read asynchronously until full command input
  
  while (Serial.available()) {
    char c = Serial.read();
    
    switch (c) {
      case CR:      
      //likely have full command in buffer now, commands are terminated by CR and/or LS
      case LF:
        commandLine[charsRead] = NULLCHAR;       
        //null terminate our command char array
        
        if (charsRead > 0)  {
          charsRead = 0;                           
          //charsRead is static, so have to reset
          Serial.println(commandLine);
          return true;
        }
        break;
      case BS:                                    
      // handle backspace in input: put a space in last char
        if (charsRead > 0) {                        //and adjust commandLine and charsRead
          commandLine[--charsRead] = NULLCHAR;
//          Serial << byte(BS) << byte(SPACE) << byte(BS);  
          //no idea how this works, found it on the Internet
        }
        break;
      default:
        // c = tolower(c);
        if (charsRead < COMMAND_BUFFER_LENGTH) {
          commandLine[charsRead++] = c;
        }
        commandLine[charsRead] = NULLCHAR;     //just in case
        break;
    }
  }
  return false;
}

int readNumber () {
  char * numTextPtr = strtok(NULL, delimiters);         
  //K&R string.h  pg. 250
  return atoi(numTextPtr);                              
  //K&R string.h  pg. 251
}

char * readWord() {
  char * word = strtok(NULL, delimiters);               
  //K&R string.h  pg. 250
  return word;
}

char * readText() {
  char * text = strtok(NULL, wordDelimiter);
  return text; 
}

void nullCommand(char * ptrToCommandName) {
  print2("Command not found: ", ptrToCommandName);      
  //see above for macro print2
}


// calculations commands
int addCommand() {                                    
  int firstOperand = readNumber();
  int secondOperand = readNumber();
  return firstOperand + secondOperand;
}

int subtractCommand() {                                
  int firstOperand = readNumber();
  int secondOperand = readNumber();
  return firstOperand - secondOperand;
}

int multiplyCommand() {                                
  int firstOperand = readNumber();
  int secondOperand = readNumber();
  return firstOperand * secondOperand;
}

float devideCommand() {
  float firstOperand  = readNumber();
  float secondOperand = readNumber();
  if(secondOperand == 0){
    return 0;
  }
  return (firstOperand / secondOperand);
}

//cmd command
String echoCommand(){
  String text = readText();
  return text;
}

bool DoMyCommand(char * commandLine) {
  //  print2("\nCommand: ", commandLine);
  int result;

  char * ptrToCommandName = strtok(commandLine, delimiters);
  //  print2("commandName= ", ptrToCommandName);

  if (strcmp(ptrToCommandName, addCommandToken) == 0) {                   
    //Modify here
    result = addCommand();
    print2(">    The sum is = ", result);

  } else if(strcmp(ptrToCommandName, multiplyCommandToken) == 0){
    
    result = multiplyCommand();
    print2(">    The product is = ", result);
  } else if(strcmp(ptrToCommandName, devideCommandToken) == 0){
    
    float resultDecimal = devideCommand();
    print2(">    The quotient is = ", resultDecimal);
  }else if(strcmp(ptrToCommandName, echoCommandToken) == 0){
    
    String text = echoCommand();
    print2(">     ", text);
  }else {
    if (strcmp(ptrToCommandName, subtractCommandToken) == 0) {           
      //Modify here
      result = subtractCommand();                                       
      //K&R string.h  pg. 251
      print2(">    The difference is = ", result);

    } else {
      nullCommand(ptrToCommandName);
    }
  }
}
