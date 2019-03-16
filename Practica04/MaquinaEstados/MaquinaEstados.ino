/***********************************************************************
*                 Algoritmo de Evasión de Obstaculos                   *
*          Programa en C de Arduino para un robot móvil que evade      * 
*                               obstáculos.                            *
*                           Lab. Bio-Robótica                          *
*                               FI-UNAM                                *
*                                                                      *
************************************************************************/
// Definicion de constantes
#define ADELANTE move_robot(AVANCE, 0.0f)
#define ATRAS move_robot(-AVANCE, 0.0)
#define GIRO_IZQ move_robot(0.0, GIRO)
#define GIRO_DER move_robot(0.0, -GIRO)
#define ALTO move_robot(0.0,0.0)

int Mot1 = 2;         // Derecha giro adelante        |||||Mot1 -> motor derecho   Mot2 -> Motor izquierdo|||||
int Mot1_n = 3;       // Derecha giro atrás
int Mot2 = 4;         // Izquierda giro adelante
int Mot2_n = 5;       // Izquierda giro atrás
int pwmPin1 = 11;     // Señal PWM para motor 1
int pwmPin2 = 10;     // Señal PWM para motor 2
                      // Motor 1 avanza con PWM: 25 - 29
                      // Motor 2 avanza con PWM: 33 -35
int sen_contact1 = 12;    //Sensor de contacto derecho
int sen_contact2 = 13;    //Sensor de contacto izquierdo
int infrared1 = A0;   //Sensor infrarrojo derecho
int infrared2 = A1;   //Sensor infrarrojo izquierdo

void setup() {
  int i;
  Serial.begin(9600);
  pinMode(Mot1, OUTPUT);
  pinMode(Mot1_n, OUTPUT);
  pinMode(Mot2, OUTPUT);
  pinMode(Mot2_n, OUTPUT);
  pinMode(sen_contact1, INPUT);
  pinMode(sen_contact2, INPUT);
}


// Esta función hace que el robot primero gire un angulo y después avance una distancia
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

// Esta función lee el valor de un sensor, indicando su tipo y numero, y regresa su valor
float shs(String sensor, int num_sensor){
  switch(optParser(sensor)){
      case 1:
        return(float(contactSen(num_sensor)));
        break;
      case 2:
        return(infraredSen(num_sensor));
  }
}

int optParser(String opt){
  String contact = "contact";
  String infrared = "infrared";
  if(contact.equals(opt))
    return 1;
  if(infrared.equals(opt))
    return 2;
  else
    return 0;
}

int contactSen(int num_sensor){
  int value;
  
  if (num_sensor == 1){  
    value = digitalRead(sen_contact1);
    return value;
    delay(500);
    }
  if (num_sensor == 2){
    value = digitalRead(sen_contact2);
    return value;
    delay(500);
    }
  else {
    Serial.println("Número de sensor no válido");
    }
}

float infraredSen(int num_sensor){
  float value = 0;
  float prom_value = 0;
  float x;
  float dist;
  int sen_infrared;
  
  if (num_sensor == 1)
    sen_infrared = infrared1;
  if (num_sensor == 2)
    sen_infrared = infrared2;
  
  for(int i=0; i<100; i++){
    value = analogRead(sen_infrared);
    prom_value += value;
  }
  prom_value /= 100;
  x = prom_value;
  dist = (0.000000004*pow(x,4)) - (0.000005*pow(x,3)) + (0.0026*pow(x,2)) - (0.6005*x) + 63.91; 
  return(dist);
}

// Algoritmo de evasión de obstáculos
void loop(){
  int estado = 0;
  float Si,Sd;
  float AVANCE=.1;
  float GIRO= 45;
  // Estado inicial
  estado = 0;
  // Loop infinito
  while(1){
    // Se leen los sensores
    Si = shs("contact",1);
    Sd = shs("contact",2);
    Serial.print("Estado Presente: ");
    Serial.println(estado);
    Serial.print("Si: ");
    Serial.println(Si);
    Serial.print("Sd: ");
    Serial.println(Sd);
    switch (estado){
      case 0:
        // est0
        if (Si == 0){
          if (Sd == 0){
            estado = 0;
            ADELANTE;
            Serial.println("ADELANTE");
          }else{
            estado = 1;
            ALTO;
            Serial.println("ALTO");
          }
        }else{
          if (Sd == 0){
            estado = 3;
            ALTO;
            Serial.println("ALTO");
          }else{
            estado = 5;
            ALTO;
            Serial.println("ALTO");
          }
        }
      break;
      
      case 1: // est1
        estado = 2;
        ATRAS;
        Serial.println("ATRAS");
        break;case 2: // est2
        estado = 0;
        GIRO_IZQ;
        Serial.println("GIRO_IZQ");
      break;
      
      case 3: // est3
        estado = 4;
        ATRAS;
        Serial.println("ATRAS");
      break;
      
      case 4: // est4
        estado = 0;
        GIRO_DER;
        Serial.println("GIRO_DER");
      break;
      
      case 5: // est5
        estado = 6;
        ATRAS;
        Serial.println("ATRAS");
      break;
      
      case 6: // est6
        estado = 7;
        GIRO_IZQ;
        Serial.println("GIRO_IZQ");
      break;
      
      case 7: // est7
        estado = 8;
        GIRO_IZQ;
        Serial.println("GIRO_IZQ");
      break;
      
      case 8: // est8
        estado = 9;
        ADELANTE;
        Serial.println("ADELANTE");
      break;
      
      case 9: // est9
        estado = 10;
        ADELANTE;
        Serial.println("ADELANTE");
      break;
      
      case 10: // est10
        estado = 11;
        GIRO_DER;
        Serial.println("GIRO_DER");
      break;
      
      case 11: // est11
        estado = 0;
        GIRO_DER;
        Serial.println("GIRO_DER");
      break;
    } // end case
  } // end while
} // end Main (loop)
