#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Int64.h>

#define RH_ENCODER_A 3
#define RH_ENCODER_B 12

int MotI = 12;         // Derecha giro adelante        |||||Mot1 -> motor derecho   Mot2 -> Motor izquierdo|||||
int MotI_n = 13;       // Derecha giro atrás
int MotD = 5;         // Izquierda giro adelante
int MotD_n = 6;       // Izquierda giro atrás
int pwmPin1 = 11;     // Señal PWM para motor 1
int pwmPin2 = 10;     // Señal PWM para motor 2

volatile long rightCount = 0;

void rightEncoderEvent(){
  if(digitalRead(RH_ENCODER_A) == HIGH){
    if(digitalRead(RH_ENCODER_B) == LOW){
      rightCount++;
    }
    else{
      rightCount--;
    }
  }
  else{
    if(digitalRead(RH_ENCODER_B) == LOW){
      rightCount--;
    }
    else{
      rightCount++;
    }
  }
}

ros::NodeHandle nh;

std_msgs::Int16 sharpSensor1;
std_msgs::Int16 sharpSensor2;
std_msgs::Bool contactSensor1;
std_msgs::Bool contactSensor2;
std_msgs::Int64 encoder1;
std_msgs::Int64 encoder2;
std_msgs::Int16 photo1;
std_msgs::Int16 photo2;
std_msgs::Int16 photo3;
std_msgs::Int16 photo4;

ros::Publisher sharpSensorPub1("/sharp_sensor_1", &sharpSensor1);
ros::Publisher sharpSensorPub2("/sharp_sensor_2", &sharpSensor2);
ros::Publisher contactSensorPub1("/contact_sensor_1", &contactSensor1);
ros::Publisher contactSensorPub2("/contact_sensor_2", &contactSensor1);
ros::Publisher encoderPub1("/encoder_1", &encoder1);
ros::Publisher encoderPub2("/encoder_2", &encoder2);
ros::Publisher photoPub1("/photo_1", &photo1);
ros::Publisher photoPub2("/photo_2", &photo2);
ros::Publisher photoPub3("/photo_3", &photo3);
ros::Publisher photoPub4("/photo_4", &photo4);

void speedMotor1Callback(const std_msgs::Float32& mess){
  if(mess.data >= 0){
    digitalWrite(MotI, HIGH);
    digitalWrite(MotI_n, LOW);
    analogWrite(pwmPin1, mess.data);
  }
  else{
    digitalWrite(MotI, LOW);
    digitalWrite(MotI_n, HIGH);
    analogWrite(pwmPin1, fabs(mess.data));
  }
}

void speedMotor2Callback(const std_msgs::Float32& mess){
  if(mess.data >= 0){
    digitalWrite(MotI, HIGH);
    digitalWrite(MotI_n, LOW);
    analogWrite(pwmPin1, mess.data);
  }
  else{
    digitalWrite(MotI, LOW);
    digitalWrite(MotI_n, HIGH);
    analogWrite(pwmPin1, fabs(mess.data));
  } 
}

ros::Subscriber<std_msgs::Float32> subSpeedMotor1("/speed_motor_1", speedMotor1Callback);
ros::Subscriber<std_msgs::Float32> subSpeedMotor2("/speed_motor_2", speedMotor2Callback);

void setup() {
  nh.initNode();
  nh.advertise(sharpSensorPub1);
  nh.advertise(sharpSensorPub2);
  nh.advertise(contactSensorPub1);
  nh.advertise(contactSensorPub2);
  nh.advertise(encoderPub1);
  nh.advertise(encoderPub2);
  nh.advertise(photoPub1);
  nh.advertise(photoPub2);
  nh.advertise(photoPub3);
  nh.advertise(photoPub4);
  nh.subscribe(subSpeedMotor1);
  nh.subscribe(subSpeedMotor2);
  pinMode(MotI, OUTPUT);
  pinMode(MotI_n, OUTPUT);
  pinMode(RH_ENCODER_A, INPUT);
  pinMode(RH_ENCODER_B, INPUT);

  attachInterrupt(1, rightEncoderEvent, CHANGE);
}

void loop() {
  sharpSensor1.data = 0.5;
  sharpSensor2.data = 0.7;
  contactSensor1.data = true;
  contactSensor2.data = false;
  encoder1.data = rightCount;
  encoder2.data = 0;
  photo1.data = 1;
  photo2.data = 1;
  photo3.data = 1;
  photo4.data = 1;
  sharpSensorPub1.publish(&sharpSensor1);
  sharpSensorPub2.publish(&sharpSensor2);
  contactSensorPub1.publish(&contactSensor1);
  contactSensorPub2.publish(&contactSensor2);
  encoderPub2.publish(&encoder1);
  encoderPub2.publish(&encoder2);
  photoPub1.publish(&photo1);
  photoPub2.publish(&photo2);
  photoPub3.publish(&photo3);
  photoPub4.publish(&photo4);
  nh.spinOnce();
  delay(50);
}
