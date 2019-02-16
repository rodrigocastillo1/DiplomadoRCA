int led = 13;
int intPin = 2;

void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  pinMode(intPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(intPin), alerta, RISING);
}

void loop() {
  
  delay(100);
  
}

void alerta(){
  digitalWrite(led, HIGH);
  delay(200000);
  digitalWrite(led, LOW);
}

