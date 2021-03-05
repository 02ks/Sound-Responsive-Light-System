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
void boxINboxOUT(uint32_t color, int wait) {
  int layer1 = 24;
  int layer2 [] = { 16,17,18,23,25,30,31,32 }; //length 0 to 8
  int layer3 [] = { 8,9,10,11,12,15,19,22,26,29,33,36,37,38,39,40 }; //length 0 to 15
  int layer4 [] = { 0,1,2,3,4,5,6,7,13,14,20,21,27,28,34,35,41,42,43,44,45,46,47,48 }; //length 0 to 23
  strip.setPixelColor(layer1, color);
  strip.show();
  delay(wait);
  for( int i = 0; i < 9; i++){
    strip.setPixelColor(layer2[i], color); 
  }
  strip.show();
  delay(wait);
  for( int i = 0; i < 16; i++) {
    strip.setPixelColor(layer3[i], color);
  }
  strip.show();
  delay(wait);
  for( int i = 0; i < 24; i++) {
    strip.setPixelColor(layer4[i], color);
  }
  strip.show();
  delay(wait);
  for( int i = 0; i < 24; i++) {
    strip.setPixelColor(layer4[i], strip.Color(0,0,0));
  }
  strip.show();
  delay(wait);
  for( int i = 0; i < 16; i++) {
    strip.setPixelColor(layer3[i], strip.Color(0,0,0));
  }
  strip.show();
  delay(wait);
  for( int i = 0; i < 9; i++) {
    strip.setPixelColor(layer2[i], strip.Color(0,0,0));
  }
  strip.show();
  
}
void loop() {
  // put your main code here, to run repeatedly:
  boxINboxOUT(strip.Color(123,100,50), 500);
  delay(1000);
}
