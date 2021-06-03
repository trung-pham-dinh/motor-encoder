#define DIRB 7
#define DIRA 4
#define PWB 6
#define PWA 5
int n = 200;
double period = 0;
double fre = 0;


void forward(int n=255)
{
  analogWrite(PWB, n);
  digitalWrite(DIRB, HIGH);
 
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2,INPUT);
  pinMode(DIRB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(PWB, OUTPUT);
  pinMode(PWA, OUTPUT);
  attachInterrupt(0,encoder,FALLING);
  forward(255);
}

void loop() {
  
  Serial.print(period);
  Serial.print(' ');
  Serial.print(fre);
  Serial.print(' ');
  n = map(analogRead(0),0,697,0,255);
  Serial.println(n);
  forward(255);
  
}

void encoder(void) {
  static bool first = 1;
  static long long tim = 0;
  if(first) {
    tim = millis();
    first = 0;
  }
  else{
    period = (millis() - tim)*20;
    fre = 1000/period;
    tim = millis();
  }
}
