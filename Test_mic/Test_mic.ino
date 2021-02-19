unsigned int knock;
int ledPin = 9;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  double maxvol = 1024;

  unsigned long start= millis();  // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = maxvol;
  
  knock = analogRead(0);
      
  //peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  double volts = (knock * 5) / maxvol;  // convert to volts
  Serial.print(volts);
  if (volts < 2.2){
    Serial.println("yes");
    digitalWrite(ledPin, HIGH);
    delay(1000);
    Serial.println("Knock Knock");
  } else {
    Serial.println("no");
    digitalWrite(ledPin, LOW);
  }
  
  //Serial.print('\t');
  //Serial.print(volts);
  //Serial.print('\n');
  
  delay(50);
  
}
