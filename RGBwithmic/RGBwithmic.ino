const int sampleWindow = 250; // Sample window width in mS (250 mS = 4Hz)
unsigned int knock;
int ledPinRed = 6;
int ledPinGreen = 7;
int ledPinBlue = 8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPinRed, OUTPUT)
  pinMode(ledPinGreen, OUTPUT)
  pinMode(ledPinBlue, OUTPUT)
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long start= millis();  // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  // collect data for 250 miliseconds
 while (millis() - start < sampleWindow)
  {
    knock = analogRead(0);
       if (knock < 1024)  //This is the max of the 10-bit ADC so this loop will include all readings
       {
          if (knock > signalMax)
          {
            signalMax = knock;  // save just the max levels
          }
          else if (knock < signalMin)
          {
          signalMin = knock;  // save just the min levels
          }
      }
  }
 peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
 double volts = (peakToPeak * 3.3) / 1024;  // convert to volts
}
