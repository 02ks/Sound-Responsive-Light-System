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

void transition_RowToCol(uint32_t color, int wait) {
  int row[7][7] = {
    {42,1,44,3,46,5,48},
    {35,8,37,10,39,12,41},
    {28,15,30,17,32,19,34},
    {21,22,23,24,25,26,27},
    {14,29,16,31,18,33,20},
    {7,36,9,38,11,40,13},
    {0,43,2,45,4,47,6}
   };
  int col[7][7] = {
    {0,7,14,21,28,35,42},
    {1,8,15,22,29,36,43},
    {2,9,16,23,30,37,44},
    {3,10,17,24,31,38,45},
    {4,11,18,25,32,39,46},
    {5,12,19,26,33,40,47},
    {6,13,20,27,34,41,48}
  };
  
  //row escalation
  for( int i = 0; i < 7; i++) {
    for( int j = 0; j < 7; j++) {
      strip.setPixelColor(row[i][j], color); 
      Serial.println(row[i][j]);
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
  delay(wait);
  
  //col escalation
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
  
  
  
} 

void loop() {
  // put your main code here, to run repeatedly:
  transition_RowToCol(strip.Color(50,50,50), 500); //new color
  delay(10000);
} 
