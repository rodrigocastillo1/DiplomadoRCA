int Mot1 = 2;
int Mot1_n = 3;
int Mot2 = 4;
int Mot2_n = 5;
int pwmPin1 = 10;
int pwmPin2 = 11;
int pwm = 0;

String opt = "";

void setup() {
  Serial.begin(9600);
  pinMode(Mot1, OUTPUT);
  pinMode(Mot1_n, OUTPUT);
  pinMode(Mot2, OUTPUT);
  pinMode(Mot2_n, OUTPUT);
  
}

void loop() {
  int motor1[] = {Mot1, Mot1_n, pwmPin1};
  int motor2[] = {Mot2, Mot2_n, pwmPin2};
  
  if(Serial.available() > 0){
    Serial.println("####################");
    opt = Serial.readString();
    Serial.println(opt);
    //Serial.println(optParser(opt));
    //Serial.println(pwm);
  }

  switch(optParser(opt)){
      case 1:
        turnLeft(motor1);
        motorControl(motor1, 255);
        break;
      case 2:
        turnRight(motor1);
        motorControl(motor1, 255);
        break;
      case 3:
        turnLeft(motor2);
        motorControl(motor2, 255);
        break;
      case 4:
        turnRight(motor2);
        motorControl(motor2, 255);
        break;
      case 5:
        turnOff(motor1);
        motorControl(motor1, 0);
        break;
      case 6:
        turnOff(motor2);
        motorControl(motor2, 0);
        break;
      case 7:
        motorControl(motor1, velControl(motor1));
        break;
      case 8:
        motorControl(motor2, velControl(motor2));
      //default:
        //Serial.println("Ingrese una opción");
  }

}

void turnLeft(int *motor){
  digitalWrite(motor[0], HIGH);
  digitalWrite(motor[1], LOW);
}

void turnRight(int *motor){
  digitalWrite(motor[0], LOW);
  digitalWrite(motor[1], HIGH);
}

void turnOff(int *motor){
  digitalWrite(motor[0], LOW);
  digitalWrite(motor[1], LOW);
}

void motorControl(int *motor, int vel){
  analogWrite(motor[2], vel);
}


int velControl(int *motor){
  int vel;
  if(pwm < 127){                                      //Recibe el valor de pwm enviado por el usuario y lo convierte en un valor de velocidad de 0 a 255 junto con la dirección
    vel = map(pwm, 0, 126, 0, 255);
    turnRight(motor);
  }
  else{
    if(pwm > 127){
      vel = map(pwm, 128, 255, 0, 255);
      turnLeft(motor);
    }
    else{
      turnOff(motor);
      vel = 0;
    }
  }

  return(vel);
}




/*
 * ESTO ESTÁ CHINGÓN, PERO NOE ESTÁ TOMANDO MUCHO TIMEPO. LUEGO JALA 
 * int optParser(String inst){
  int prev_space = 0;
  int j = 0;
  String opts[3];
  int opt = 0;
  int M1 = 0; M2 = 1; on = 0; off = 10; speed1 = 20; left = 0; right = 100; 
  
  for(int i=0; i <= inst.length(); i++){
    if(inst[i] == ' ' || i == inst.length()){
      opts[j] = inst.substring(prev_space, i);
      prev_space = i+1;
      j+=1;
    }
  }

  for(int i=0; i<opts.length(); i++){
    if(opts[i].equals("M1")){
      sum
    }
  }
}*/


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
  if(isSpeed(opt) == 1)
    return 7;
  if(isSpeed(opt) == 2)
    return 8;
  else{
    return 0;
  }
}


int isSpeed(String inst){
  int prev_space = 0;
  int j = 0;
  String opts[3];
  
  for(int i=0; i <= inst.length(); i++){
    if(inst[i] == ' ' || i == inst.length()){
      opts[j] = inst.substring(prev_space, i);
      prev_space = i+1;
      j+=1;
    }
  }

  if(opts[1].equals("speed")){
    pwm = opts[2].toInt();
    if(opts[0].equals("M1"))
      return 1;
    if(opts[0].equals("M2"))
      return 2;
  }

  return 0;
}

