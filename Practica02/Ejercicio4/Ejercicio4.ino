int op = 2;


void setup() {
  pinMode(op, INPUT);
  Serial.begin(9600);
}

void loop() {
  int value;
  value = digitalRead(op);
  Serial.println(value);

}
