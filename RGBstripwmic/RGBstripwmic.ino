#include <Adafruit_NeoPixel.h>

#define LED_PIN    6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 49
#define NUM_LEDS 49

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


// setup() function -- runs once at startup --------------------------------
const int sampleWindow = 5000; // Sample window width in mS (250 mS = 4Hz)
unsigned int knock1;
unsigned int knock2;
unsigned int knock3;
unsigned int knock4;
unsigned int knock5;
unsigned int knocktotal;
int clapcount = 0;
int fun = 0;
void setup() {

  Serial.begin(9600);

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}


// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {
  double maxvol = 1024;
  unsigned long start = millis(); // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = maxvol;

  // collect data for 250 miliseconds

  knock1 = analogRead(0);
  knock2 = analogRead(0);
  knock3 = analogRead(0);
  knock4 = analogRead(0);
  knock5 = analogRead(0);

  knocktotal = knock1 + knock2 + knock3 + knock4 + knock5;
  double volts = (knocktotal) / maxvol;  // convert to volts
  Serial.println(volts);
  if (volts < 2.2) { //might need to change this variable

    clapcount = clapcount + 1;
    Serial.println(clapcount);
    delay(500);
    if (clapcount > 0) {
      if (clapcount == 1) {
        boxINboxOUT(strip.Color(100,0,0), 50);
      }
      /**else if (clapcount == 2) {
        rainbow(50);
      }
      /**else if (clapcount == 3) {
        delay(1000);
        }**/
      else {
        clapcount = 0;
        //colorWipe(strip.Color(  0,   0,  0), 10); // Blue
      }
    }
  }
}


// Some functions of our own for creating animated effects -----------------

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void showStrip() {
   strip.show();
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));

}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}

void FadeInOut(int layer){
  float r, g, b;
  int red1 = random(0,255);
  int green1 = random(0,255);
  int blue1 = random(0,255);
  for(int k = 0; k < 256; k=k+1) {
    r = (k/256.0)*red1;
    g = (k/256.0)*green1;
    b = (k/256.0)*blue1;
    strip.setPixelColor(layer, strip.Color(r,g,b));
    showStrip(); 
  }
  
  for(int k = 255; k >= 0; k=k-2) {
    r = (k/256.0)*red1;
    g = (k/256.0)*green1;
    b = (k/256.0)*blue1;
    strip.setPixelColor(layer, strip.Color(r,g,b));
    showStrip();
  }
  
}
void boxINboxOUT(uint32_t color, int wait) {
  int layer1 = 24;
  int layer2 [] = { 16,17,18,23,25,30,31,32 }; //length 0 to 8
  int layer3 [] = { 8,9,10,11,12,15,19,22,26,29,33,36,37,38,39,40 }; //length 0 to 15
  int layer4 [] = { 0,1,2,3,4,5,6,7,13,14,20,21,27,28,34,35,41,42,43,44,45,46,47,48 }; //length 0 to 23
  strip.setPixelColor(layer1, color);
  strip.show();
  delay(wait);
  FadeInOut(layer2);
  for( int i = 0; i < 9; i++){
     
  }
  strip.show();
  delay(wait);
  for( int i = 0; i < 16; i++) {
    FadeInOut(layer3[i]);
  }
  strip.show();
  delay(wait);
  for( int i = 0; i < 24; i++) {
    FadeInOut(layer4[i]);
  }
  strip.show();
  delay(wait);
  for( int i = 0; i < 24; i++) {
    FadeInOut(layer4[i]);
  }
  strip.show();
  delay(wait);
  for( int i = 0; i < 16; i++) {
    FadeInOut(layer3[i]);
  }
  strip.show();
  delay(wait);
  for( int i = 0; i < 9; i++) {
    FadeInOut(layer2[i]);
  }
  strip.show();
}
void colorOn(int wait) {
  while (fun < 50) {
    fun = fun + 1;
    int i = rand() % 59 + 1;
    int i2 = rand() % 59 + 1;
    int i3 = rand() % 59 + 1;
    int i4 = rand() % 59 + 1;
    int r = rand() % 255;
    int g = rand() % 255;
    int b = rand() % 255;
    uint32_t color = strip.Color(  r,   g,  b);
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();   //  Update strip to match
    strip.setPixelColor(i2, color);         //  Set pixel's color (in RAM)
    strip.show();   //  Update strip to match
    strip.setPixelColor(i3, color);         //  Set pixel's color (in RAM)
    strip.show();   //  Update strip to match
    strip.setPixelColor(i4, color);         //  Set pixel's color (in RAM)
    strip.show();   //  Update strip to match
    delay(50);
    strip.clear();         //  Set pixel's color (in RAM)
    strip.show();   //  Update strip to match
    delay(wait);
  }
  if (fun >= 50) { 
    fun = 0;
  }
  }
  void colorWipe(uint32_t color, int wait) {
    for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
      strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
      strip.show();                          //  Update strip to match
      delay(wait);                           //  Pause for a moment
    }
  }

  // Theater-marquee-style chasing lights. Pass in a color (32-bit value,
  // a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
  // between frames.
  void theaterChase(uint32_t color, int wait) {
    for (int a = 0; a < 10; a++) { // Repeat 10 times...
      for (int b = 0; b < 3; b++) { //  'b' counts from 0 to 2...
        strip.clear();         //   Set all pixels in RAM to 0 (off)
        // 'c' counts up from 'b' to end of strip in steps of 3...
        for (int c = b; c < strip.numPixels(); c += 3) {
          strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
        }
        strip.show(); // Update strip with new contents
        delay(wait);  // Pause for a moment
      }
    }
  }

  // Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
  void rainbow(int wait) {
    // Hue of first pixel runs 5 complete loops through the color wheel.
    // Color wheel has a range of 65536 but it's OK if we roll over, so
    // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
    // means we'll make 5*65536/256 = 1280 passes through this outer loop:
    for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
      for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
        // Offset pixel hue by an amount to make one full revolution of the
        // color wheel (range of 65536) along the length of the strip
        // (strip.numPixels() steps):
        int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
        // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
        // optionally add saturation and value (brightness) (each 0 to 255).
        // Here we're using just the single-argument hue variant. The result
        // is passed through strip.gamma32() to provide 'truer' colors
        // before assigning to each pixel:
        strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }

  // Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
  void theaterChaseRainbow(int wait) {
    int firstPixelHue = 0;     // First pixel starts at red (hue 0)
    for (int a = 0; a < 30; a++) { // Repeat 30 times...
      for (int b = 0; b < 3; b++) { //  'b' counts from 0 to 2...
        strip.clear();         //   Set all pixels in RAM to 0 (off)
        // 'c' counts up from 'b' to end of strip in increments of 3...
        for (int c = b; c < strip.numPixels(); c += 3) {
          // hue of pixel 'c' is offset by an amount to make one full
          // revolution of the color wheel (range 65536) along the length
          // of the strip (strip.numPixels() steps):
          int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
          uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
          strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
        }
        strip.show();                // Update strip with new contents
        delay(wait);                 // Pause for a moment
        firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
      }
    }
  }
