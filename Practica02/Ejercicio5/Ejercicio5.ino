int ir = A0;

void setup() {
  Serial.begin(9600);

}

void loop() {
  float value = 0;
  float prom_value = 0;
  float x;
  float dist;
  for(int i=0; i<100; i++){
    value = analogRead(ir);
    prom_value += value;
  }
  prom_value /= 10;
  x = prom_value;
  dist = (0.0043*x^4) - (0.3543*x^3) + (10.768*x^2) - (150.18*x) + 971.47; 
  Serial.println(dist);
  delay(500);
}
