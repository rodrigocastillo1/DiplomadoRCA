int Mot1 = 2;         // Derecha giro adelante        |||||Mot1 -> motor derecho   Mot2 -> Motor izquierdo|||||
int Mot1_n = 3;       // Derecha giro atrás
int Mot2 = 4;         // Izquierda giro adelante
int Mot2_n = 5;       // Izquierda giro atrás
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
  /*digitalWrite(Mot1, LOW);
  digitalWrite(Mot1_n, HIGH);
  digitalWrite(Mot2, HIGH);
  digitalWrite(Mot2_n, LOW); 
  
  analogWrite(pwmPin1, 57);
  analogWrite(pwmPin2, 60);
  */
  move_robot(0.20, 0);
  move_robot(0.50, -90);
  move_robot(0.50, 90);
  stop_robot();
  while(true){
    delay(1000);
  }
}

void move_robot(float distancia, float angulo){
  int Tv_izq = 1107;
  int Tv_der = 1850;
  int Tr = 2698;
  int tiempo = 0;
  
  //Una vuelta de 360 grados la da en Tv segundos
  //Si nos manda un ángulo tetha, el tiempo que tiene que estar prendido es (theta/360)*Tv
  //Calculamos así el tiempo y se da con un delay
  
  
  if(angulo > 0){
    digitalWrite(Mot1, LOW);
    digitalWrite(Mot1_n, HIGH);
    digitalWrite(Mot2, HIGH);
    digitalWrite(Mot2_n, LOW);
    tiempo = abs(angulo*Tv_der/360);
  }
  else{
    digitalWrite(Mot1, HIGH);
    digitalWrite(Mot1_n, LOW);
    digitalWrite(Mot2, LOW);
    digitalWrite(Mot2_n, HIGH);
    tiempo = abs(angulo*Tv_izq/360);
  }
  
  
  analogWrite(pwmPin1, 57);
  analogWrite(pwmPin2, 60);
  delay(tiempo);
  Serial.println(tiempo);
  stop_robot();
  
  //Una distancia de 1 metro lo recorre en Tr segundos
  //Si nos da una distancia D, el tiempo que tiene que estar prendido es (D/1m)*Tr
  //Calculamos así el tiempo y se da con un delay
  tiempo = distancia*Tr;
  
  digitalWrite(Mot1, HIGH);
  digitalWrite(Mot1_n, LOW);
  digitalWrite(Mot2, HIGH);
  digitalWrite(Mot2_n, LOW);
  analogWrite(pwmPin1, 77);
  analogWrite(pwmPin2, 80);
  delay(tiempo);
  stop_robot();
    
}

void stop_robot(){
  digitalWrite(Mot1, LOW);
  digitalWrite(Mot1_n, LOW);
  digitalWrite(Mot2, LOW);
  digitalWrite(Mot2_n, LOW);
  analogWrite(pwmPin1, 0);
  analogWrite(pwmPin2, 0);
  delay(100);
}

