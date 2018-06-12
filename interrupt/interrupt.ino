const byte EXT_INT = 2;

const byte IND0 = 4;
const byte IND1 = 5;
const byte IND2 = 6;

const byte PAD1 = 7;
const byte PAD2 = 8;
const byte PAD3 = 9;
const byte PAD4 = 10;
const byte PAD5 = 11;
const byte PAD6 = 12;
const byte PAD7 = 13;

void event() {
  int value = digitalRead(EXT_INT);
  if(value == HIGH) {
    if(digitalRead(PAD1) == HIGH) {
      digitalWrite(IND0, HIGH);
      digitalWrite(IND1, LOW);
      digitalWrite(IND2, LOW);
    } else if(digitalRead(PAD2) == HIGH) {
      digitalWrite(IND0, LOW);
      digitalWrite(IND1, HIGH);
      digitalWrite(IND2, LOW);
    } else if(digitalRead(PAD3) == HIGH) {
      digitalWrite(IND0, HIGH);
      digitalWrite(IND1, HIGH);
      digitalWrite(IND2, LOW);
    } else if(digitalRead(PAD4) == HIGH) {
      digitalWrite(IND0, LOW);
      digitalWrite(IND1, LOW);
      digitalWrite(IND2, HIGH);
    } else if(digitalRead(PAD5) == HIGH) {
      digitalWrite(IND0, HIGH);
      digitalWrite(IND1, LOW);
      digitalWrite(IND2, HIGH);
    } else if(digitalRead(PAD6) == HIGH) {
      digitalWrite(IND0, LOW);
      digitalWrite(IND1, HIGH);
      digitalWrite(IND2, HIGH);
    } else if(digitalRead(PAD7) == HIGH) {
      digitalWrite(IND0, HIGH);
      digitalWrite(IND1, HIGH);
      digitalWrite(IND2, HIGH);
    }
  }
}

void setup() {
  pinMode(IND0, OUTPUT);
  pinMode(IND1, OUTPUT);
  pinMode(IND2, OUTPUT);

  pinMode(PAD1, INPUT);
  pinMode(PAD2, INPUT);
  pinMode(PAD3, INPUT);
  pinMode(PAD4, INPUT);
  pinMode(PAD5, INPUT);
  pinMode(PAD6, INPUT);
  pinMode(PAD7, INPUT);

  pinMode(EXT_INT, INPUT);
  attachInterrupt(digitalPinToInterrupt(EXT_INT), event, CHANGE);
}

void loop() {

}
