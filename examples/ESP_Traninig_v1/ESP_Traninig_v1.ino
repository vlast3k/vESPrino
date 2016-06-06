int BTTN_PIN = D7;
int LED_PIN = D3;
void ex2_attachInterrupt(void (*)());

void setup() {  
  /*
   * Exercise 0: Serial port communication
   */
   ex0_serialDumps();
   
  /*
   * Exercise 1: Blink LED
   */
   ex1_blink_led();
   
  /*
   * Exercise 2a: press button, display textD
   */
   ex2_attachInterrupt(ex2a_onBttnChange_text);

  /*
   * Exercise 2b: press button, display textD
   */
   ex2_attachInterrupt(ex2b_onBttnChange_led);
}


void loop() {
  /*
   * Exercise 3: blink in loop
   */
   pinMode(LED_PIN, OUTPUT);
   digitalWrite(LED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
   delay(300);              // wait for a second
   digitalWrite(LED_PIN, LOW);    // turn the LED off by making the voltage LOW
   delay(300);  
}

void ex0_serialDumps() {
  Serial.begin(115200L);
  Serial.println("ESP8266 101 Training");
}

void ex1_blink_led() {
   pinMode(LED_PIN, OUTPUT);
   for (int i=0; i < 10; i++) {
     digitalWrite(LED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
     delay(600);              // wait for a second
     digitalWrite(LED_PIN, LOW);    // turn the LED off by making the voltage LOW
     delay(600);  
   }  
}

void ex2_attachInterrupt(void (*func)()) {
  pinMode(BTTN_PIN, INPUT_PULLUP);
  attachInterrupt(BTTN_PIN, func, CHANGE);
}

void ex2a_onBttnChange_text() {
  Serial.println(String("Button state: ") + digitalRead(BTTN_PIN));
}

void ex2b_onBttnChange_led() {
  Serial.println(String("Button state: ") + digitalRead(BTTN_PIN));
  digitalWrite(LED_PIN, digitalRead(BTTN_PIN));
}
