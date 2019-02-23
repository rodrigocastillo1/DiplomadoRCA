bool flag = 0;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {

    if(flag == 0){
      for(int i=0;i<10;i++){
            digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
            delay(1250);                       // wait for a second
            digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
            delay(1250);     
      }
      flag = 1;
    }
    else
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)   
}
