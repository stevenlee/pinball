/*
  Pitch follower

  Plays a pitch that changes based on a changing analog input

  circuit:
  - 8 ohm speaker on digital pin 9
  - photoresistor on analog 0 to 5V
  - 4.7 kilohm resistor on analog 0 to ground

  created 21 Jan 2010
  modified 31 May 2012
  by Tom Igoe, with suggestion from Michael Flynn

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Tone2
*/

void setup() {
}

void loop() {
  // read the sensor:
  int sensorReading = analogRead(A0);
  if (sensorReading < 10)
    sensorReading = 10;
  int thisPitch = map(sensorReading, 0, 819, 0, 4000);

  // play the pitch:
  tone(9, thisPitch, 10);
  delay(1);        // delay in between reads for stability
}
