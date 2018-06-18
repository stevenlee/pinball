/*
  Arduino Pinball
*/
#include "LedControl.h" // MAX7219 Driver
const byte i_RST = 1;
const byte i_INT = 2;
const byte i_LANE[7] = {4,5,6,7,8,9,10};
// Interface of MAX7219
const byte DIN = 13;
const byte CS = 12;
const byte CLK = 11;
LedControl lc = LedControl(DIN,CLK,CS, 1);  // Pins: DIN,CLK,CS, # of Display connected
// Global Variable
int lane_cnt[7] = {0,0,0,0,0,0,0};
int lane_disp[7] = {0,0,0,0,0,0,0};
int busy = 0;
const byte zeros[] = {0,0,0,0,0,0,0,0};
const byte heart5[] = {
  B00110000,
  B01111000,
  B01111100,
  B00111110,
  B00111110,
  B01111100,
  B01111000,
  B00110000
};
void showInitBitmap()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0,i,heart5[i]);
  }
  delay(2000);
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0,i,zeros[i]);
  }
}

// Handle interrupt form RESET Button
void int_reset() {
  for(int i = 0; i<7; i++) {
    lane_cnt[i] = 0;
    lane_disp[i] = 0;
  }
  show_something();
}

// Handle interrupt from photo diode
void int_handler() {
  if(busy > 0) {
    return;
  }
  int value = digitalRead(i_INT);
  if(value == HIGH) { // Rising Edge
    busy = 15;
    for(int i=0; i < 7; i++) {
      if(digitalRead(i_LANE[i]) == HIGH) {
        lane_cnt[i] ++;
      }
    }
    show_something();
  }
}

void show_something() {
  for(int i=0; i<7; i++) {
    lane_disp[i] = lane_cnt[i];
    lc.setRow(0,i,lane_disp[i]);
  }
}

void setup() {
  pinMode(i_RST, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(i_RST), int_reset, LOW);
  pinMode(i_INT, INPUT);
  attachInterrupt(digitalPinToInterrupt(i_INT), int_handler, CHANGE);
  for(int i = 0; i<7; i++) {
    pinMode(i_LANE[i], INPUT);
  }
  // Initialize MAX7214
  lc.shutdown(0,false);  // Wake up displays
  lc.setIntensity(0,5);  // Set intensity levels
  lc.clearDisplay(0);  // Clear Displays
  showInitBitmap();
}

// Main Loop
void loop() {
  if(busy > 0) {
    busy = busy - 1;
  }
  delay(10);
}
