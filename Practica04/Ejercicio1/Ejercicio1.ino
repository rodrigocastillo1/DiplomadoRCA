int sen_contact1 = ;
int sen_contact = ;
String Sensors[] = {"contact"};

void setup() {
  Serial.begin(9600);
  pinMode(sen_contact1, INPUT);
  pinMode(sen_contact2, INPUT);
}



void loop() {
  Serial.println(sizeof(Sensors));
}


float shs(char* sensor, int num_sensor){
  float x;
  int tam_arr = 2;
  
  
  return x;

  
}


int contact(int num_sensor){
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
