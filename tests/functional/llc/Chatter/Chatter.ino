String msg = "nothing";

void setup() {
    Serial.begin(115200);
    Serial1.begin(115200);
    Serial2.begin(115200);
    Serial3.begin(115200);
    Serial4.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

    if (Serial1.available()) {
        msg = Serial1.readStringUntil('\n');
        blink();
        Serial1.println("OK,0");
    }
    
    if (Serial2.available()) {
        msg = Serial2.readStringUntil('\n');
        blink();
        Serial2.println("OK,1");
    }
    
    if (Serial3.available()) {
        msg = Serial3.readStringUntil('\n');
        blink();
        Serial3.println("OK,2");
    }
    
    if (Serial4.available()) {
        msg = Serial4.readStringUntil('\n');
        blink();
        Serial4.println("OK,3");
    }

    // To USB Monitor
    Serial.print("Received: ");
    Serial.println(msg);

}

void blink() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(25);
  digitalWrite(LED_BUILTIN, LOW);
}
