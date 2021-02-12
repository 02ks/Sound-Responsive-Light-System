// code used from : https://learn.sparkfun.com/tutorials/electret-mic-breakout-board-hookup-guide#hardware-overview
const int sampleWindow = 250; // Sample window width in mS (250 mS = 4Hz)
unsigned int knock;
int ledPin = 9;

void setup() 
{
   Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() 
{
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


Serial.println(volts);
 if (volts >=1.0)
 {
  //turn on LED
  digitalWrite(ledPin, HIGH);
   delay(500);
  Serial.println("Knock Knock");
 }
 else
 {
 //turn LED off
 digitalWrite(ledPin, LOW);
 }             
}
