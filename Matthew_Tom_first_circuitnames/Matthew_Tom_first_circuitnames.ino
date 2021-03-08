#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN    6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 60

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

void namecallout(uint32_t color, int wait) {
<<<<<<< Updated upstream
  int Kogan[] = {9,11,17,18,23,31,32,37,39}; //Length 0 to 8
  int Matthew[] = {8,12,15,19,22,24,26,29,30,32,33,36,40};//length 0 to 12
=======
  int Kogan[] = {9,11,17,18,25,31,32,37,39}; //Length 0 to 8
  int Matthew[] = {8,12,15,19,22,24,26,29,30,32,33,36,40};//length 0 to 11
>>>>>>> Stashed changes
  int Ethan[] = {9,10,11,18,23,24,25,32,37,38,39}; // length 0 to 10

  for( int i = 0; i < 9; i++) {
    strip.setPixelColor(Kogan[i], color);
  }
  strip.show();
  delay(wait);
  strip.clear();
  for( int i = 0; i < 13; i++) {
    strip.setPixelColor(Matthew[i], color); 
  }
  strip.show();
  delay(wait);
  strip.clear();
  for( int i = 0; i < 11; i++) {
    strip.setPixelColor(Ethan[i], color);
  }
  strip.show();
  delay(wait);
  strip.clear(); 
  
}

void loop() {
  // put your main code here, to run repeatedly:
  namecallout(strip.Color(50,50,50), 1000);
  delay(500);
}
