/*
  Arduino Pinball
  2018.06.12
*/
// Pin define
const byte i_RST = 1;
const byte i_INT = 2;
const byte o_PWM = 3; // Reserve for Audio Out
const byte i_LANE[7] = {4,5,6,7,8,9,10};
const byte o_RCLK = 11;
const byte o_SER = 12;
const byte o_SRCLK = 13;
// Global Variable
int lane_cnt[7] = {0,0,0,0,0,0,0};
int lane_disp[7] = {0,0,0,0,0,0,0};
int total = 0;
float lane_stat[7] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0};
// Handle interrupt form RESET Button
void int_reset() {
  for(int i = 0; i<7; i++) {
    lane_cnt[i] = 0;
    lane_disp[i] = 0;
    lane_stat[i] = 0.0f;
  }
  total = 0;
  stat();
  show_something();
}

// Handle interrupt from photo diode
void int_handler() {
  int value = digitalRead(i_INT);
  if(value == HIGH) { // Rising Edge
    for(int i=0; i < 7; i++) {
      if(digitalRead(i_LANE[0]) == HIGH) {
        lane_cnt[i] ++;
      }
    }
    stat();
    show_something();
  }
}

// Let's do some math
void stat() {
  // Count Total
  total = 0;
  for(int i=0; i < 7; i++) {
    total = total + lane_cnt[i];
  }
  // Calculate Ratio of each lane
  if(total == 0) {
    for(int i=0; i < 7; i++) {
      lane_stat[i] = 0.0f;
    }
  } else {
    for(int i=0; i < 7; i++) {
      lane_stat[i] = (float)lane_cnt[i] / (float)total;
    }
  }
}

// Mapping input to 1,3,7,15,31,63,127,255
int mymap(float fVal) {
  int power = (int)((fVal*8.0)+0.5f);
  return (1 << power) -1;
}

// Let's show something
void show_something() {
  for(int i=0; i<7; i++) {
    lane_disp[i] = mymap(lane_stat[i]);
  }
  digitalWrite(o_RCLK, LOW);
  for(int i=0; i<7; i++) {
    shiftOut(o_SER, o_SRCLK, MSBFIRST, lane_disp[i]);
  }
  digitalWrite(o_RCLK, HIGH);
}

// Setup
void setup() {
  pinMode(i_RST, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(i_RST), int_reset, LOW);

  pinMode(i_INT, INPUT);
  attachInterrupt(digitalPinToInterrupt(i_INT), int_handler, CHANGE);

  for(int i = 0; i<7; i++) {
    pinMode(i_LANE[i], INPUT);
  }
  pinMode(o_RCLK, OUTPUT);
  pinMode(o_SER, OUTPUT);
  pinMode(o_SRCLK, OUTPUT);
}

// Main Loop
void loop() {
}
