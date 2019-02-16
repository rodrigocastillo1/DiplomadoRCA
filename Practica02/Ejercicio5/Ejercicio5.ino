int ir = A0;
float value = 0;
float prom_value = 0;

void setup() {
  Serial.begin(9600);

}

void loop() {
  for(int i=0; i<10; i++){
    value = analogRead(ir);
    prom_value += value;
  }
  prom_value /= 10;
  
  Serial.println(prom_value);

}
