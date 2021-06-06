#define DIRA1 4 // use for IN3
#define DIRA2 5 // use for IN4
#define ENA 9 // use to control speed
#define ENCODERA 2
#define ENCODERB 3

// These variables are for ISR
volatile int encoderCount = 0;
volatile uint8_t oldState = 0;
int encodeTable[16] = {
  0,  1, -1,  2,
 -1,  0, -2,  1,
  1, -2,  0, -1,
  2, -1,  1,  0
};


int dir = 0; // for program to know motor direction (we can also read EncoderA,B to figure out the direction)
void setup() {
  Serial.begin(9600);
  
  pinMode(DIRA1, OUTPUT);
  pinMode(DIRA2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENCODERA, INPUT_PULLUP); 
  pinMode(ENCODERB, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ENCODERA), encoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODERB), encoder, CHANGE);

  if(digitalRead(ENCODERA)) oldState |= 1;
  if(digitalRead(ENCODERB)) oldState |= 2;

  setMotor(1,255);
}

void loop() {
  Serial.println(encoderCount);
}

void setMotor(int d, int s) {
  if(abs(s) < 36) {
    analogWrite(ENA, 0);
  }
  else {
    analogWrite(ENA, abs(s));
  }
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

// reference: https://github.com/PaulStoffregen/Encoder/blob/master/Encoder.h
//https://www.best-microcontroller-projects.com/rotary-encoder.html
void encoder(void) {  // 8600 counts/cycle
  uint8_t A = digitalRead(ENCODERA);
  uint8_t B = digitalRead(ENCODERB);
  uint8_t thisState = oldState & 3;
  if(A) thisState |= 4; // 0b-1--
  if(B) thisState |= 8; // 0b1---
  
  oldState = (thisState>>2);
  encoderCount += encodeTable[thisState];
}

// this function cannot work
//void encoder(void) {
//  int8_t A = digitalRead(ENCODERA);
//  int8_t B = digitalRead(ENCODERB);
//
//  int8_t thisState = (A<<1)|B;
//  
//  int8_t thisCode = (thisState<<2) | oldState;
//    
//  if(thisCode != oldCode) {
//    if(dir == 1 && encodeTable[thisCode] == 1) {
//      Serial.print(encoderCount);
//      Serial.print('\n');
//      encoderCount++;
//      oldCode = thisCode;
//    }
//    else if(dir == -1 && encodeTable[thisCode] == -1) {
//      Serial.print(encoderCount);
//      Serial.print('\n');
//      encoderCount--;  
//      oldCode = thisCode;
//    }
//  }
//  oldState = thisState;
//}
