int Mot1 = 3;
int Mot1_n = 5;
int Mot2 = 10;
int Mot2_n = 11;

String opt;

void setup() {
  Serial.begin(9600);
  pinMode(Mot1, OUTPUT);
  pinMode(Mot1_n, OUTPUT);
  pinMode(Mot2, OUTPUT);
  pinMode(Mot2_n, OUTPUT);
  
}

void loop() {
  int motor1[] = {Mot1, Mot1_n};
  int motor2[] = {Mot2, Mot2_n};
  
  if(Serial.available() > 0){
    Serial.println("####################");
    opt = Serial.readString();
  }

  switch(optParser(opt)){
      case 1:
        turnLeft(motor1);
        break;
      case 2:
        turnRight(motor1);
        break;
      case 3:
        turnLeft(motor2);
        break;
      case 4:
        turnRight(motor2);
        break;
      case 5:
        turnOff(motor1);
        break;
      case 6:
        turnOff(motor2);
        break;
      //default:
        //Serial.println("Ingrese una opción");
  }

}

void turnLeft(int *motor){
  Serial.println("Girando hacia la izquierda");
  Serial.println(motor[0]);
  Serial.println(motor[1]);
  //analogWrite(motor[0], 0);
  //delay(50);
  digitalWrite(motor[0], HIGH);
  digitalWrite(motor[1], LOW);
}

void turnRight(int *motor){
  //analogWrite(motor[1], 0);
  //delay(50);
  digitalWrite(motor[0], LOW);
  digitalWrite(motor[1], HIGH);
}

void turnOff(int *motor){
  digitalWrite(motor[0], LOW);
  digitalWrite(motor[1], LOW);
}


int optParser(String opt){
  String M1_left = "M1 on left";
  String M1_right = "M1 on right";
  String M2_left = "M2 on left";
  String M2_right = "M2 on right";
  String M1_off = "M1 off";
  String M2_off = "M2 off";
  if(M1_left.equals(opt))
    return 1;
  if(M1_right.equals(opt))
    return 2;
  if(M2_left.equals(opt))
    return 3; 
  if(M2_right.equals(opt))
    return 4;
  if(M1_off.equals(opt))
    return 5;
  if(M2_off.equals(opt))
    return 6;
  else
    return 0;
}
