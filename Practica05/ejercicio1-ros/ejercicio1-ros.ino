#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Bool.h>

ros::NodeHandle nh;

std_msgs::Float32 sharpSensor;                                  //
std_msgs::Bool contactSensor;   


ros::Publisher sharpSensorPub("/sharp_sensor", &sharpSensor);   //
ros::Publisher contactSensorPub("/contact_sensor", &contactSensor);


int sen_contact1 = 12;    //Sensor de contacto derecho
int sen_contact2 = 13;    //Sensor de contacto izquierdo
int infrared1 = A0;   //Sensor infrarrojo derecho
int infrared2 = A1;   //Sensor infrarrojo izquierdo
/*int Mot1 = 2;         // Derecha giro adelante        |||||Mot1 -> motor derecho   Mot2 -> Motor izquierdo|||||
int Mot1_n = 3;       // Derecha giro atrás
int Mot2 = 4;         // Izquierda giro adelante
int Mot2_n = 5;       // Izquierda giro atrás
int pwmPin1 = 11;     // Señal PWM para motor 1
int pwmPin2 = 10;     // Señal PWM para motor 2



//void speedMotorCallback(const std_msgs::Float32 &mess){
  digitalWrite(Mot1, LOW);
  digitalWrite(Mot1_n, HIGH);
  digitalWrite(Mot2, HIGH);
  digitalWrite(Mot2_n, LOW);
  analogWrite(pwmPin1, 57);
  analogWrite(pwmPin2, 60);
  delay(1000);
  stop_robot();
  //digitalWrite(13, HIGH);
//}

void stop_robot(){
  digitalWrite(Mot1, LOW);
  digitalWrite(Mot1_n, LOW);
  digitalWrite(Mot2, LOW);
  digitalWrite(Mot2_n, LOW);
  analogWrite(pwmPin1, 0);
  analogWrite(pwmPin2, 0);
  delay(100);
}

//ros::Subscriber<std_msgs::Float32> subSpeedMotor1("/speed_motor_1", speedMotorCallback);
*/


void setup() {
  /*pinMode(Mot1, OUTPUT);
  pinMode(Mot1_n, OUTPUT);
  pinMode(Mot2, OUTPUT);
  pinMode(Mot2_n, OUTPUT);*/
  
  nh.initNode();                          // Inicializando el nodo en el que va a estar publicando
  nh.advertise(sharpSensorPub);           // Creando el tópico para el sensor sharp
  nh.advertise(contactSensorPub);         // Creando el tópico para el sensor de contacto 
  //nh.subscribe(subSpeedMotor1);          
}

void loop() {
  
  sharpSensor.data = infraredSen(1);
  contactSensor.data = true;
  sharpSensorPub.publish(&sharpSensor);
  sharpSensorPub.publish(&contactSensor);
  nh.spinOnce();                          //Para que pueda publicar los mensajes y para que pueda recibir 
  delay(500);

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
    //Serial.println("Número de sensor no válido");
    }
}

// TTYACM0
