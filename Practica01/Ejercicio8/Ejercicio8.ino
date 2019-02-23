int led = 13;
int intPin = 2;
volatile int flag = 0;
volatile int i;

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
    if(flag == 0){
      for(i=0;i<10;i++){
            digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
            delay(125000);                       // wait for a second
            digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
            delay(125000);     
      }
      flag = 1;
    }
    else
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)   
}

