#include <Adafruit_NeoPixel.h>
#define LED_PIN    6
#define LED_COUNT 49
#define NUM_LEDS 49

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);



// variables
const int sampleWindow = 5000; // Sample window width in mS (250 mS = 4Hz)
unsigned int knock1;
unsigned int knock2;
unsigned int knock3;
unsigned int knock4;
unsigned int knock5;
unsigned int knocktotal;
int clapcount = 0;
int fun = 0;
int layer1 [] = { 24 };
int layer2 [] = { 16, 17, 18, 23, 25, 30, 31, 32 }; //length 0 to 8
int layer3 [] = { 8, 9, 10, 11, 12, 15, 19, 22, 26, 29, 33, 36, 37, 38, 39, 40 }; //length 0 to 15
int layer4 [] = { 0, 1, 2, 3, 4, 5, 6, 7, 13, 14, 20, 21, 27, 28, 34, 35, 41, 42, 43, 44, 45, 46, 47, 48 }; //length 0 to 23

void setup() {
  Serial.begin(9600);
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop() {
  double maxvol = 1024;
  unsigned long start = millis(); // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level
  unsigned int signalMax = 0;
  unsigned int signalMin = maxvol;

  knock1 = analogRead(0);
  knock2 = analogRead(0);
  knock3 = analogRead(0);
  knock4 = analogRead(0);
  knock5 = analogRead(0);

  knocktotal = knock1 + knock2 + knock3 + knock4 + knock5;
  double volts = (knocktotal) / maxvol;  // convert to volts
  Serial.println(volts);
  if (volts < 2.3) { //might need to change this variable

    clapcount = clapcount + 1;
    Serial.println(clapcount);
    delay(500);
    if (clapcount > 0) {
      if (clapcount == 1) {
        boxINboxOUT(256, 256, 256, 1);
        delay(100);
        namecallout(strip.Color(100, 100, 100), 1000);
        delay(100);
        ece5(120, 80, 200, 700);
        delay(100);
        heartpattern(150, 30, 30, 800);
        delay(100);
        colorWipe(strip.Color(  0,   0,  0), 10); // Blue
      }
      else if (clapcount == 2) {
        transition_RowToCol(strip.Color(50, 50, 50), 200); //new color
        delay(100);
        transition_RowToCol(strip.Color(50, 50, 50), 200); //new color
        delay(100);
        transition_RowToCol2(strip.Color(50, 50, 50), 200); //new color
        delay(100);
        transition_RowToCol2(strip.Color(50, 50, 50), 200); //new color
        delay(100);
        colorWipe(strip.Color(  0,   0,  0), 10); // Blue
      }
      else if (clapcount == 3) {
        colorOn(50);
        delay(100);
        colorWipe(strip.Color(  0,   0,  0), 10); // Blue
      }
      else if (clapcount == 4) {
        betterRainbow(1);
        colorWipe(strip.Color(  0,   0,  0), 10); // Blue
      }
      else {
        clapcount = 0;
        mood(100);
        delay(100);
        colorWipe(strip.Color(  0,   0,  0), 10); // Blue
      }
    }
  }
}

void mood(uint8_t wait) {
  for (long firstPixelHue = 0; firstPixelHue < 2 * 65536; firstPixelHue += 100) {
    uint32_t ms = millis();
    for ( byte y = 0; y < 7; y++) {
      for ( byte x = 0; x < 7; x++) {
        int pixelHue = firstPixelHue + x * 65536L / 300 + y * 65536L / 300;
        strip.setPixelColor( XYsafe(x, y), strip.gamma32(strip.ColorHSV(pixelHue)));
        
      }
    }
    strip.show();
    delay(wait);  
  }
}
void showStrip() {
  strip.show();
}

uint16_t XYsafe( uint8_t x, uint8_t y)
{
  if ( x >= 7) return -1;
  if ( y >= 7) return -1;
  return getLEDpos(x, y);
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

void setPixel(int Pixel, byte red, byte green, byte blue) {
  strip.setPixelColor(Pixel, strip.Color(red, green, blue));

}

void setAll(byte red, byte green, byte blue) {
  for (int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}



void betterRainbow(int wait) {

  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 100) {
    uint32_t ms = millis();
    for ( byte y = 0; y < 7; y++) {
      for ( byte x = 0; x < 7; x++) {
        int pixelHue = firstPixelHue + x * 65536L / 49 + y * 65536L / 49;
        strip.setPixelColor( XYsafe(x, y), strip.gamma32(strip.ColorHSV(pixelHue)));
      }
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

void namecallout(uint32_t color, int wait) {
  int Kogan[] = {9, 11, 17, 18, 23, 31, 32, 37, 39}; //Length 0 to 8
  int Matthew[] = {8, 12, 15, 19, 22, 24, 26, 29, 30, 32, 33, 36, 40}; //length 0 to 12
  int Ethan[] = {9, 10, 11, 18, 23, 24, 25, 32, 37, 38, 39}; // length 0 to 10

  for ( int i = 0; i < 9; i++) {
    strip.setPixelColor(Kogan[i], color);
  }
  strip.show();
  delay(wait);
  strip.clear();
  for ( int i = 0; i < 13; i++) {
    strip.setPixelColor(Matthew[i], color);
  }
  strip.show();
  delay(wait);
  strip.clear();
  for ( int i = 0; i < 11; i++) {
    strip.setPixelColor(Ethan[i], color);
  }
  strip.show();
  delay(wait);
  strip.clear();

}

void FadeInOut2(int arr[], int size, int red, int green, int blue, int test) {
  float r, g, b;
  if (test == 1) {
    for (int k = 0; k < 256; k = k + 1) {
      r = (k / 256.0) * red;
      g = (k / 256.0) * green;
      b = (k / 256.0) * blue;
      for (int i = 0; i < size; i++ ) {
        setPixel(arr[i], r, g, b);
      }
      showStrip();
    }
  }
  if (test == 2) {
    for (int k = 255; k >= 0; k = k - 1) {
      r = (k / 256.0) * red;
      g = (k / 256.0) * green;
      b = (k / 256.0) * blue;
      for (int i = 0; i < size; i++ ) {
        setPixel(arr[i], r, g, b);
      }
      showStrip();
    }
  }
}

void boxINboxOUT(int red, int green, int blue, int wait) {
  FadeInOut2(layer1, 1, red, green, blue, 1);
  strip.show();
  delay(wait);
  FadeInOut2(layer2, 8, red, green, blue, 1);
  strip.show();
  delay(wait);
  FadeInOut2(layer3, 16, red, green, blue, 1);
  strip.show();
  delay(wait);
  FadeInOut2(layer4, 24, red, green, blue, 1);
  strip.show();
  delay(wait);
  FadeInOut2(layer4, 24, red, green, blue, 2);
  strip.show();
  delay(wait);
  FadeInOut2(layer3, 16, red, green, blue, 2);
  strip.show();
  delay(wait);
  FadeInOut2(layer2, 8, red, green, blue, 2);
  strip.show();
  delay(wait);
  FadeInOut2(layer1, 1, red, green, blue, 2);
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
    strip.setPixelColor(i, color);
    strip.show();
    strip.setPixelColor(i2, color);
    strip.show();
    strip.setPixelColor(i3, color);
    strip.show();
    strip.setPixelColor(i4, color);
    strip.show();
    delay(50);
    strip.clear();
    strip.show();
    delay(wait);
  }
  if (fun >= 50) {
    fun = 0;
  }
}

void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) { 
    strip.setPixelColor(i, color);         
    strip.show();                       
    delay(wait);                    
  }
}
void heartpattern(int red, int green, int blue, int wait) {
  int heart[] = {2, 3, 9, 12, 15, 19, 21, 25, 29, 33, 37, 40, 44, 45};
  FadeInOut2(heart, 14, red, green, blue, 1);
  strip.show();
  delay(wait);
  FadeInOut2(heart, 14, red, green, blue, 2);
  strip.show();
  delay(wait);
}
void ece5(int red, int green, int blue, int wait) {
  int ece5E[] = {0, 1, 2, 3, 4, 5, 6, 7, 20, 21, 22, 23, 24, 25, 26, 27, 34, 35, 42, 43, 44, 45, 46, 47, 48};
  int ece5C[] = {0, 1, 2, 3, 4, 8, 19, 22, 33, 36, 42, 43, 44, 45, 46};
  int ece55[] = {1, 2, 3, 4, 5, 6, 13, 14, 27, 29, 30, 31, 32, 33, 34, 35, 42, 43, 44, 45, 46, 47, 48};
  FadeInOut2(ece5E, 25, red, green, blue, 1);
  strip.show();
  strip.clear();
  delay(500);
  FadeInOut2(ece5C, 15, red, green, blue, 1);
  strip.show();
  strip.clear();
  delay(500);
  FadeInOut2(ece5E, 25 , red, green, blue, 1);
  strip.show();
  strip.clear();
  delay(500);
  FadeInOut2(ece55, 23 , red, green, blue, 1);
  strip.show();
  strip.clear();
  delay(wait);
}

void transition_RowToCol(uint32_t color, int wait) {
  int row[7][7] = {
    {0, 1, 2, 3, 4, 5, 6},
    {7, 8, 9, 10, 11, 12, 13},
    {14, 15, 16, 17, 18, 19, 20},
    {21, 22, 23, 24, 25, 26, 27},
    {28, 29, 30, 31, 32, 33, 34},
    {35, 36, 37, 38, 39, 40, 41},
    {42, 43, 44, 45, 46, 47, 48}
  };
  int col[7][7] = {
    {0, 13, 14, 27, 28, 41, 42},
    {1, 12, 15, 26, 29, 40, 43},
    {2, 11, 16, 25, 30, 39, 44},
    {3, 10, 17, 24, 31, 38, 45},
    {4, 9, 18, 23, 32, 37, 46},
    {5, 8, 19, 22, 33, 36, 47},
    {6, 7, 20, 21, 34, 35, 48}
  };

  //row escalation
  for ( int i = 0; i < 7; i++) {
    for ( int j = 0; j < 7; j++) {
      strip.setPixelColor(row[i][j], color);
      Serial.println(row[i][j]);
    }
    strip.show();
    delay(wait);
    strip.clear();
  }
  //row de-escalation
  for ( int i = 6; i >= 0; i--) {
    for ( int j = 6; j >= 0; j--) {
      strip.setPixelColor(row[i][j], color);
      Serial.println(row[i][j]);
    }
    strip.show();
    delay(wait);
    strip.clear();
  }
  delay(wait);

  //col escalation
  for ( int i = 0; i < 7; i++) { //version 2.0
    for ( int j = 6; j >= 0; j--) {
      strip.setPixelColor(col[i][j], color);
      Serial.println(col[i][j]);
    }
    strip.show();
    delay(wait);
    strip.clear();
  }
  //col de-escalation
  for ( int i = 6; i >= 0; i--) {
    for ( int j = 6; j >= 0; j--) { //version 2.0
      strip.setPixelColor(col[i][j], color);
      Serial.println(col[i][j]);
    }
    strip.show();
    delay(wait);
    strip.clear();
  }
}
void transition_RowToCol2(uint32_t color, int wait) {
  int row[7][7] = {
    {42, 1, 44, 3, 46, 5, 48},
    {35, 8, 37, 10, 39, 12, 41},
    {28, 15, 30, 17, 32, 19, 34},
    {21, 22, 23, 24, 25, 26, 27},
    {14, 29, 16, 31, 18, 33, 20},
    {7, 36, 9, 38, 11, 40, 13},
    {0, 43, 2, 45, 4, 47, 6}
  };
  int col[7][7] = {
    {0, 7, 14, 21, 28, 35, 42},
    {1, 8, 15, 22, 29, 36, 43},
    {2, 9, 16, 23, 30, 37, 44},
    {3, 10, 17, 24, 31, 38, 45},
    {4, 11, 18, 25, 32, 39, 46},
    {5, 12, 19, 26, 33, 40, 47},
    {6, 13, 20, 27, 34, 41, 48}
  };

  //row escalation
  for ( int i = 0; i < 7; i++) {
    for ( int j = 0; j < 7; j++) {
      strip.setPixelColor(row[i][j], color);
      Serial.println(row[i][j]);
    }
    strip.show();
    delay(wait);
    strip.clear();
  }
  //row de-escalation
  for ( int i = 6; i >= 0; i--) {
    for ( int j = 6; j >= 0; j--) {
      strip.setPixelColor(row[i][j], color);
      Serial.println(row[i][j]);
    }
    strip.show();
    delay(wait);
    strip.clear();
  }
  delay(wait);

  //col escalation
  for ( int i = 0; i < 7; i++) { //version 2.0
    for ( int j = 6; j >= 0; j--) {
      strip.setPixelColor(col[i][j], color);
      Serial.println(col[i][j]);
    }
    strip.show();
    delay(wait);
    strip.clear();
  }
  //col de-escalation
  for ( int i = 6; i >= 0; i--) {
    for ( int j = 6; j >= 0; j--) { //version 2.0
      strip.setPixelColor(col[i][j], color);
      Serial.println(col[i][j]);
    }
    strip.show();
    delay(wait);
    strip.clear();
  }
}
