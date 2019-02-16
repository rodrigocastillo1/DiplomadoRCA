int motorD_F = 8;
int motorD_B = 7;
int motorI_F = 12;
int motorI_B = 13;
int potD = 3;
int potI = 5;

int tv = 500, tl = 2000, tc = 1000;
//accion0 -> Detenido, accion1-> Adelante, acción2-> Atrás, acción3-> Detenido.


void setup() {
  pinMode(motorD_F, OUTPUT);
  pinMode(motorD_B, OUTPUT);
  pinMode(motorI_F, OUTPUT);
  pinMode(motorI_B, OUTPUT);
}

void loop() {
  int tiempo;
  int accionD, accionI;
  
  for(int estado=0; estado<8; estado++){
    if(estado%2 == 0){                //Recorrido derecho
      tiempo = tl;
      if(estado == 2 || estado == 6)  //Reccorrido corto
        tiempo = tc;
      accionD = 1;
      accionI = 1;
      } 
    else {                            //Dar vuelta
      accionD = 1;
      accionI = 2;
      tiempo = tv;
    }
    comenzar(accionD, accionI, tiempo);
  }
}


void comenzar(int accionD, int accionI, int tiempo){
  digitalWrite(motorD_F, HIGH);
  digitalWrite(motorD_B, LOW);
  digitalWrite(motorI_F, HIGH);
  digitalWrite(motorI_B, LOW);

  if(accionD==1 && accionI==1){
    analogWrite(potD, 255/4);
    analogWrite(potI, 255/3);
    }
    else{
      if (accionD == 1 && accionI==2){
        analogWrite(potD, 255/4);
        analogWrite(potI, 255/8);
        }
      }
    delay(tiempo);
}


