int led = 3;
int potPin = A0;
int tiempoMs = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  tiempoMs = map(analogRead(potPin), 0, 1023, 0, 5000);
  Serial.println(tiempoMs);
  for(int i=0; i<255; i++){
    analogWrite(led, i);
    delay(10);
  }
  delay(tiempoMs);
  for(int i=255; i>0; i--){
    analogWrite(led, i);
    delay(10);
  }
  delay(tiempoMs);
}
