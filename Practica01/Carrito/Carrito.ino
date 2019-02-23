int motorD_F = 8;
int motorD_B = 7;
int motorI_F = 12;
int motorI_B = 13;
int potD = 3;
int potI = 5;
int curvas = 0;
bool detenido = false;

int tv = 800, tl = 1250, tc = 600;
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
    if(detenido == false){
      if(estado%2 == 0){                      //Recorrido largo
        if(curvas == 2)
          tiempo = tl/2;
        else
          tiempo = tl;
        if(estado == 2 || estado == 6){       //Reccorrido corto
          if(curvas == 3){
            tiempo = tc/2;
            detenido = true;
          }
          else
            tiempo = tc;
          
        }
        accionD = 1;
        accionI = 1;
        } 
      else {                                  //Dar vuelta
        accionD = 1;
        accionI = 2;
        tiempo = tv;
        curvas+=1;
      }
      comenzar(accionD, accionI, tiempo);
    }
    else{
      comenzar(0, 0, tiempo);
    }
  }
}


void comenzar(int accionD, int accionI, int tiempo){
  digitalWrite(motorD_F, HIGH);
  digitalWrite(motorD_B, LOW);
  digitalWrite(motorI_F, HIGH);
  digitalWrite(motorI_B, LOW);

  if(accionD==1 && accionI==1){
    analogWrite(potD, 255/4); //63
    analogWrite(potI, 80); //85
  }
  else{
    if (accionD == 1 && accionI==2){
      analogWrite(potD, 255/4);
      analogWrite(potI, 255/8);
    }
    else{
      analogWrite(potD, 0);
      analogWrite(potI, 0);
    }
  }
    delay(tiempo);
}


