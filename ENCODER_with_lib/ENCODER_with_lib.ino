#include<Encoder.h>

#define DIRA1 4 // use for IN3
#define DIRA2 5 // use for IN4
#define ENA 9 // use to control speed
#define ENCODERA 2
#define ENCODERB 3

Encoder knob(ENCODERA, ENCODERB);

int dir = 0;
int encoderCount = 0;
int preCount = -1;
void setup() {
  Serial.begin(9600);
  pinMode(DIRA1, OUTPUT);
  pinMode(DIRA2, OUTPUT);
  pinMode(ENA, OUTPUT);

  setMotor(-1,255);
}

void loop() {
  encoderCount = knob.read();
  if(encoderCount != preCount) {
    Serial.print(encoderCount);
    Serial.print('\n');
    preCount = encoderCount;
  }
  if(encoderCount <= -8000) {
    setMotor(0,0);
  }
}

void setMotor(int d, int s) {
    analogWrite(ENA, s);
    if(d == 1) {
      digitalWrite(DIRA1, HIGH);
      digitalWrite(DIRA2, LOW);
      dir = 1;
    }
    else if (d == -1) {
      digitalWrite(DIRA1, LOW);
      digitalWrite(DIRA2, HIGH);
      dir = -1;
    }
    else {
      digitalWrite(DIRA1, LOW);
      digitalWrite(DIRA2, LOW);
      dir = 0;
    }
}
