const int sampleWindow = 5000; // Sample window width in mS (250 mS = 4Hz)
unsigned int knock;
int clapcount = 0;
int ledPinRed = 6;
int ledPinGreen = 7;
int ledPinBlue = 8;


void off() {
  digitalWrite(ledPinRed, LOW);
  digitalWrite(ledPinGreen, LOW);
  digitalWrite(ledPinBlue, LOW);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinBlue, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  double maxvol = 1024;
  unsigned long start = millis(); // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = maxvol;

  // collect data for 250 miliseconds
  /**while (millis() - start < sampleWindow)
    {
      knock = analogRead(0);
        /** if (knock < maxvol)  //This is the max of the 10-bit ADC so this loop will include all readings
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
      delay(50);
      peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude**/

  knock = analogRead(0);
  double volts = (knock * 5) / maxvol;  // convert to volts
  Serial.println(volts);
  if (volts < 2.3) { //might need to change this variable
    clapcount = clapcount + 1;
    Serial.println(clapcount);
    delay(500);
    if (clapcount > 0) {
      if (clapcount == 1) {
        off();
        Serial.print("Red");
        digitalWrite(ledPinRed, HIGH);
        delay(1000);
      }
      else if (clapcount == 2) {
        off();
        digitalWrite(ledPinGreen, HIGH);
        delay(1000);
      }
      else if (clapcount == 3) {
        off();
        digitalWrite(ledPinBlue, HIGH);
        delay(1000);
      }
      else {
        clapcount = 0;
        off();
        delay(1000);
      }
    }
  }
}
