#define DIRA1 4
#define DIRA2 5
#define DIRB1 6
#define DIRB2 7
#define ENA 9
#define ENB 10
#define ENCODERA 2 // 2200 pulse per cycle
#define ENCODERB 3

String dir = "unknown";

volatile int countA = 0;
volatile int countB = 0;

long long int pre_tim = 0;
long long int dif_tim = 0;

double Rpm  = 0;
int tim = 0;
double acce = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(DIRB1, OUTPUT);
  pinMode(DIRA1, OUTPUT);
  pinMode(DIRB2, OUTPUT);
  pinMode(DIRA2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(ENCODERA, INPUT);
  pinMode(ENCODERB, INPUT);

  attachInterrupt(0,encoderA,RISING); //pin 2


  digitalWrite(DIRA1,LOW);
  digitalWrite(DIRA2,HIGH);
  analogWrite(ENA,255);
  
}
void loop() {
//  Serial.print("A: ");
//  Serial.print(countA);
//  Serial.print("     ");
//  Serial.print(dir);
//  Serial.print("  ");
//  Serial.println(rpm());
//  delay(100);
  rpm();
}

void encoderA(void) {
  static int stopp = 0;
  countA++;
  
  dif_tim = micros() - pre_tim;
  pre_tim = micros();
  
  if(digitalRead(ENCODERB)) {
    dir = "counterclockwise";
  }
  else {
    dir = "clockwise";
  }
  float X = 2500;
//  if(10.0*rpm() >= 2500 - countA)
//    analogWrite(ENA,0);
  if(countA >= 2200 && stopp == 0) {
      stopp = 1;
      analogWrite(ENA,0);
      Rpm = rpm();
      tim = millis();
  }
}

double rpm() {
  static bool endd = 0;
  if(dif_tim == 0)
    return 0;
  else {
    if(micros() - pre_tim <= 26000) 
      return 1.0/2200.0/dif_tim*60000000;
    else if(endd == 0){
      endd = 1;
      Serial.println(Rpm);
      Serial.println(millis()-tim);
      Serial.print(countA);
      return 0;
    }
  }
}
