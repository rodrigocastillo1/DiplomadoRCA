int sen_contact = 3;
int sen_photora = A0;
int sen_photord = 4;
int sen_temp = A1;
int sen_infrared = A2;
String opt;

void setup() {
  Serial.begin(9600);
  pinMode(sen_contact, INPUT);
  pinMode(sen_photord, INPUT);
  

}

void loop() {
  
  if(Serial.available() > 0){
    Serial.println("####################");
    opt = Serial.readString();
  }

  switch(optParser(opt)){
      case 1:
        contactSen();
        break;
      case 2:
        photoraSen();
        break;
      case 3:
        photordSen();
        break;
      case 4:
        tempSen();
        break;
      case 5:
        infraredSen();
        break;
      //default:
        //Serial.println("Ingrese una opción");
  }
}


void photoraSen(){
  int value;
  value = analogRead(sen_photora);
  Serial.print("photora ");
  Serial.println(value);
  delay(500);
}

void contactSen(){
  int value;
  value = digitalRead(sen_contact);
  Serial.print("contact ");
  Serial.println(value);
  delay(500);
}

void photordSen(){
  int value;
  value = digitalRead(sen_photord);
  Serial.print("photord ");
  Serial.println(value);
  delay(500);
}

void tempSen(){
  float temp = 0;
  float raw_data = 0;
  float raw_25 = 153.45;
  float delta = 0.01*1024/5;
  raw_data = analogRead(sen_temp);
  temp = (raw_data - raw_25)/delta + 25;
  Serial.print("temp ");
  Serial.print(temp);
  Serial.println(" °C");
  delay(500);
}

void infraredSen(){
  float value = 0;
  float prom_value = 0;
  float x;
  float dist;
  for(int i=0; i<100; i++){
    value = analogRead(sen_infrared);
    prom_value += value;
  }
  prom_value /= 100;
  x = prom_value;
  dist = (0.000000004*pow(x,4)) - (0.000005*pow(x,3)) + (0.0026*pow(x,2)) - (0.6005*x) + 63.91; 
  Serial.println(dist);
  delay(500);
}

int optParser(String opt){
  String contact = "shs contact";
  String photora = "shs photora";
  String photord = "shs photord";
  String temp = "shs temp";
  String infrared = "shs infrared";
  if(contact.equals(opt))
    return 1;
  if(photora.equals(opt))
    return 2;
  if(photord.equals(opt))
    return 3; 
  if(temp.equals(opt))
    return 4;
  if(infrared.equals(opt))
    return 5;
  else
    return 0;
}

