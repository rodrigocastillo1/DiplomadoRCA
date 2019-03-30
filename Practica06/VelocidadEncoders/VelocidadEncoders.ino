int motD_A_pin = 3;
int motD_B_pin = 4;
int motI_A_pin = 2;
int motI_B_pin = 1;

int MotI = 12;         // Derecha giro adelante        |||||Mot1 -> motor derecho   Mot2 -> Motor izquierdo|||||
int MotI_n = 13;       // Derecha giro atrás
int MotD = 5;         // Izquierda giro adelante
int MotD_n = 6;       // Izquierda giro atrás
int pwmPin1 = 11;     // Señal PWM para motor 1
int pwmPin2 = 10;     // Señal PWM para motor 2

int D_sA;
int D_sB;
int I_sA;
int I_sB;

unsigned long currentPeriod = 0;
unsigned long currentTime = 0;
unsigned long startTime = 0;
unsigned long period = 1000L*1000;

volatile int DcountA = 0;
volatile int DcountB = 0;
volatile int IcountA = 0;
volatile int IcountB = 0;
float velD = 0;
float velI = 0;

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(motD_A_pin), incDA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(motI_A_pin), incIA, RISING);
  pinMode(motD_A_pin, INPUT);
  pinMode(motD_B_pin, INPUT);
  pinMode(motI_A_pin, INPUT);
  pinMode(motI_B_pin, INPUT);
  pinMode(MotI, OUTPUT);
  pinMode(MotI_n, OUTPUT);
  pinMode(MotD, OUTPUT);
  pinMode(MotD_n, OUTPUT);

  digitalWrite(MotI, HIGH);
  digitalWrite(MotI_n, LOW);
  digitalWrite(MotD, HIGH);
  digitalWrite(MotD_n, LOW);
  analogWrite(pwmPin1, 30);
  analogWrite(pwmPin2, 35);
}

void loop() {
  //checkEncoders();
  currentTime = micros();
  Serial.println((float)currentTime);
  currentPeriod = currentTime - startTime;
  if(currentPeriod >= period){
    Serial.println(IcountA);
    Serial.println((float)currentPeriod/1000000);
    velD = (float)(DcountA/(currentPeriod/1000000));     //Velocidad en giros por segundo
    velI = (float)(IcountA/(currentPeriod/1000000));     //Velocidad en giros por segundo
    DcountA = 0;
    //DcountB = 0;
    IcountA = 0;
    //IcountB = 0;
    startTime = currentTime;
  }
  Serial.print("Velocidad motor derecho: ");
  Serial.println(velD);
  Serial.print("Velocidad motor izquierdo: ");
  Serial.println(velI);
}

void incDA(){
  DcountA+=1;
}

void incIA(){
  IcountA+=1;
}

/*void checkEncoders(){
  if(digitalRead(motD_A_pin) == 1)
    DcountA+=1;
  if(digitalRead(motD_B_pin) == 1)
    DcountB+=1;
  if(digitalRead(motI_A_pin) == 1)
    IcountA+=1;
  if(digitalRead(motI_B_pin) == 1)
    IcountB+=1;
}*/
