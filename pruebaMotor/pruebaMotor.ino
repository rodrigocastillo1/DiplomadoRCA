int Mot1 = 2;         // Derecha giro adelante
int Mot1_n = 3;       // Derecha giro atrás
int Mot2 = 4;         // Izquierda giro adelante
int Mot2_n = 5;       // Derecha giro atrás
int pwmPin1 = 11;     // Señal PWM para motor 1
int pwmPin2 = 10;     // Señal PWM para motor 2
                      // Motor 1 avanza con PWM: 25 - 29
                      // Motor 2 avanza con PWM: 33 -35


void setup() {
  Serial.begin(9600);
  pinMode(Mot1, OUTPUT);
  pinMode(Mot1_n, OUTPUT);
  pinMode(Mot2, OUTPUT);
  pinMode(Mot2_n, OUTPUT);  
}

void loop() {
  digitalWrite(Mot1, HIGH);
  digitalWrite(Mot1_n, LOW);
  digitalWrite(Mot2, HIGH);
  digitalWrite(Mot2_n, LOW); 
  
  analogWrite(pwmPin1,120);
  analogWrite(pwmPin2,120);

  stop1();

}

void stop1(){
  while(1){
    
  }
}

