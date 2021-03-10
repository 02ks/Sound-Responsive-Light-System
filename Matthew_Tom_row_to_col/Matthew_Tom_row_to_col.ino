#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN    6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 49

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800); // declares strip
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  #if defined(_AVR_ATtiny85_) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif

  strip.begin();
  strip.show();
  strip.setBrightness(50);
  
}

int getLEDpos(int x, int y) {
  int pos;
  if (x & 0x1) { // is X odd
    pos = x * 7 + (6 - y) ;
  } else { // x is even
    pos = x * 7 + y;
  }
  return pos;
}

void transition_RowToCol(uint32_t color, int wait) {
  int row[7][7] = {
    {0,1,2,3,4,5,6},
   {13,12,11,10,9,8,7},
   {14,15,16,17,18,19,20},
   {27,26,25,24,23,22,21},
   {28,29,30,31,32,33,34},
   {41,40,39,38,37,36,35},
   {42,43,44,45,46,47,48}
   };
  int col[7][7] = {
    {0,13,14,27,28,41,42},
    {1,12,15,26,29,40,43},
    {2,11,16,25,30,39,44},
    {3,10,17,24,31,38,45},
    {4,9,18,23,32,37,46},
    {5,8,19,22,33,36,47},
    {6,7,20,21,34,35,48}
  };
  
  
  //row escalation
  
  for( int i = 0; i < 7; i++) {
    int rand_row = random(0,6);
    int rand_col = random(0,6);
    for( int j = 0; j < 7; j++) {
      strip.setPixelColor(row[rand_row][j], color); 
      Serial.println(row[i][j]);
      strip.setPixelColor(col[rand_col][j], color); 
      Serial.println(col[i][j]);
      if (getLEDpos(rand_row+1, j+1) == getLEDpos(j+1, rand_col+1)) {
        strip.setPixelColor(row[rand_row][j], strip.Color(50,0,0)); 
        strip.setPixelColor(col[rand_col][j], strip.Color(50,0,0));
      }
      
    }
    strip.show();
    delay(wait);
    strip.clear();
  }
  
  /**
  for( int i = 0; i < 7; i++) { //version 2.0
    for( int j = 6; j >= 0; j--) {
      strip.setPixelColor(col[i][j], color); 
      Serial.println(col[i][j]);
    }
    strip.show();
    delay(wait);
    strip.clear();
  }
  //col de-escalation
  for( int i = 6; i >= 0; i--) {
    for( int j = 6; j >= 0; j--) { //version 2.0
      strip.setPixelColor(col[i][j], color); 
      Serial.println(col[i][j]);
    }
    strip.show();
    delay(wait);
    strip.clear();
  }

  //row de-escalation
  for( int i = 6; i >= 0; i--) { 
    for( int j = 6; j >= 0; j--) {
      strip.setPixelColor(row[i][j], color); 
      Serial.println(row[i][j]);
    }
    strip.show();
    delay(wait);
    strip.clear();
  }
  delay(wait);**/
  
  
  
} 

void loop() {
  // put your main code here, to run repeatedly:
  transition_RowToCol(strip.Color(50,50,50), 500); //new color
  delay(100);
} 
