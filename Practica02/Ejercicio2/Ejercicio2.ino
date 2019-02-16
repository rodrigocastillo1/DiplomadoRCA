int sTemp = A0;
float raw_data = 0;
float raw_25 = 153.45;
float delta = 0.01*1024/5;

void setup() {
  Serial.begin(9600);
}

void loop() {
  float temp = 0;
  raw_data = analogRead(sTemp);
  temp = (raw_data - raw_25)/delta + 25;
  Serial.println("####################");
  Serial.print(temp);
  Serial.println(" °C");
  Serial.print(convF(temp));
  Serial.println(" °F");
  Serial.print(convK(temp));
  Serial.println(" K");
  delay(1000);
}

float convF(float temp_C){
  return(temp_C*9/5 + 32);
}

float convK(float temp_C){
  return(temp_C + 273.15);
}

