/*
  shifter

  Use 74HC595 to control LED


*/

// 74HC595 OE_BAR => GND
// 74HC595 SRCLR_BAR => 5V
// 74HC595 RCLK
const byte  SER = 9;
const byte  OE_BAR = 10;
const byte  RCLK = 11;
const byte  SRCLK = 12;
const byte  SRCLR_BAR = 13;

////Pin connected to DS of 74HC595

const byte EXT_INT = 2;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 5; //ms


int value = 0;
int old_value = 255;
void addone() {
  // int val;
  // val = digitalRead(EXT_INT);
  /* No debounce
  if(value < 255) {
    value ++;
  } else {
    value = 0;
  }
  */
  /* Debounce Logic */
  unsigned long currentTime = millis();
  if((currentTime - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = currentTime;
    if(value < 255) {
      value = value + 1;
    } else {
      value = 0;
    }
  }

}
// int calc(int val) {
//   int data;
//   data = (1 << val - 1);
//   return data;
// }

void setup() {
  //set pins to output so you can control the shift register
  pinMode(SER, OUTPUT);
  pinMode(OE_BAR, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SRCLK, OUTPUT);
  pinMode(SRCLR_BAR, OUTPUT);

  pinMode(EXT_INT, INPUT);
  attachInterrupt(digitalPinToInterrupt(EXT_INT), addone, LOW);
}

void loop() {
  if(value != old_value) {
    old_value = value;
    digitalWrite(RCLK, LOW);
    shiftOut(SER, SRCLK, MSBFIRST, value);
    digitalWrite(RCLK, HIGH);
  }


  // delay(500)

  // int data;
  // for (int i = 0; i < 8; i++) {
  //   data = calc(i);
  //   digitalWrite(RCLK, LOW);
  //   shiftOut(SER, SRCLK, MSBFIRST, data);
  //   digitalWrite(RCLK, HIGH);
  //   delay(500);
  // }
}
