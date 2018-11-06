int zerocross, dim, TRIAC_OUT =4;
// dim level is from 1 to 90. It should be 100 but a larger number than 90 might cause bad effect, since arduino takes time to execute command
void setup() {
  Serial.begin(9600);
   // Since Serial.parseInt uses timeout to find the end of data on serial so it will cause a delay. Delete this and you will see the difference
  Serial.setTimeout(10);   
  pinMode(TRIAC_OUT, OUTPUT);
  digitalWrite(TRIAC_OUT, LOW);
  pinMode(2, INPUT); // set pin 2 for zero cross int. In Arduino Uno, we have 2 interrupt pin (pin 2 and 3)
  attachInterrupt(0, zero_cross, FALLING); 
}
void zero_cross()
{
  zerocross=1;    
}
// We do not put delay in interrupt function, it will cause some bad effect.
void loop() {
  if (zerocross==1)
  {
    while (Serial.available() > 0)
    {
      dim = Serial.parseInt();
    }
    /* Normal electricity has a frequency of 50 Hz, so each second, we have 50 full cycles ~20ms per full cycle
     Adjust dim level if you are using others
     10 milisec = 10000 micro sec per cycle
     So if we have 100 level, we have to time it to 100 to get exact dimming level
     */
    delayMicroseconds(dim*100); // 83 if 60Hz
    digitalWrite(TRIAC_OUT, HIGH);
    delayMicroseconds(100);
    digitalWrite(TRIAC_OUT,LOW);
    zerocross=0;
  }
}
