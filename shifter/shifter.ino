/*
  shifter

  Use 74HC595 to control LED


*/

// 74HC595 OE_BAR => GND
// 74HC595 SRCLR_BAR => 5V
// 74HC595 RCLK
int RCLK = 8;
// 74HC595 SRCLK
int SRCLK = 12;
////Pin connected to DS of 74HC595
int SER = 11;

int calc(int val) {
  int data;
  data = (1 << val - 1);
  return data;
}

void setup() {
  //set pins to output so you can control the shift register
  pinMode(RCLK, OUTPUT);
  pinMode(SRCLK, OUTPUT);
  pinMode(SER, OUTPUT);
}

void loop() {

  int data;
  for (int i = 0; i < 8; i++) {
    data = calc(i);
    digitalWrite(RCLK, LOW);
    shiftOut(SER, SRCLK, MSBFIRST, data);
    digitalWrite(RCLK, HIGH);
    delay(500);
  }
}
