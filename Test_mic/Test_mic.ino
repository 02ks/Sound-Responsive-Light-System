void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int maxvol = 1024;

  unsigned long start= millis();  // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = maxvol;
  
  knock = analogRead(0);
  
  
  if (knock < maxvol)  //This is the max of the 10-bit ADC so this loop will include all readings
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
      
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  double volts = (peakToPeak * 3.3) / maxvol;  // convert to volts
  Serial.print(knock);
  Serial.print('\t');
  Serial.print(volts);
  Serial.print('\n');
  
  delay(500);
  
}
