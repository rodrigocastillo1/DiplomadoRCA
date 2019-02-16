int ldr = A0;
float value = 0;

void setup() {
  Serial.begin(9600);

}

void loop() {
  value = analogRead(ldr);
  Serial.println(value);

}
