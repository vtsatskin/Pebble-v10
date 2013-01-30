#include <LiquidCrystal.h>
#include <Time.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int COLUMNS = 16;
const int ROWS = 2;
const int BUFFER_SIZE = 140;
char buffer[BUFFER_SIZE];
int bytesRead = 0;
int usingBuffer = false;

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(COLUMNS, ROWS);
  
  lcd.print("Pebble v10.0");
  lcd.setCursor(0, 1);
  lcd.print("GIVE ME DATA!");
  lcd.home();
  
  cleanBuffer();
  
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}
  
void loop() { 
  if(bytesRead = Serial.readBytesUntil('\\', buffer, BUFFER_SIZE-1)) {
    // Debugging stuff
    Serial.println("String read: ");
    Serial.println(buffer);
    Serial.println("Characters read: ");
    Serial.println(bytesRead);
    
    printStringDoubleLine(buffer, bytesRead);
  }
}

void cleanBuffer() {
  for(int i = 0; i < BUFFER_SIZE; ++i)
    buffer[i] = ' ';
}

void printStringSingleWithScroll(char string[], int bytesRead){
  lcd.clear();
  lcd.print(string);

  if(bytesRead > COLUMNS) {    
    for(int i = 1; i < bytesRead; ++i) {     
      delay(500);
      lcd.scrollDisplayLeft();
    }
  }
}

void printStringDoubleLine(char string[], int bytesRead){
  lcd.clear();
    
  int col;
  int row;
  int pages = (bytesRead / (COLUMNS*ROWS)) + 1;
  
  Serial.println("Pages to display: ");
  Serial.println(pages);
  
  for(int p = 0; p < pages; ++p){
    lcd.clear();
    
    Serial.println("page: ");
    Serial.println(p);
    
    col = 0;
    row = 0;
    
    for(int i = 0; i < COLUMNS*ROWS ; ++i) {
      if(i < COLUMNS) {
        col = i;
        row = 0;
      } else {
        col = i - COLUMNS;
        row = 1;
      }
      lcd.setCursor(col, row);
      lcd.print(string[(p*COLUMNS*ROWS) + i]);
    }
    delay(3000);
  }

  cleanBuffer();
}

