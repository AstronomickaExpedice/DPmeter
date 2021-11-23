unsigned long cas1 = 0;
unsigned long cas2 = 0;
unsigned long tmr = 0;
void setup() {
  pinMode(4, OUTPUT); //NABÍJENÍ PŘES ODPOR, VYBÍJENÍ PŘES ODPOR
  pinMode(5, INPUT); //Monitor kapacity
  Serial.begin(9600);
}

void loop() {
  cas1 = 0;
  cas2 = 0;
  tmr = 0;
  digitalWrite(4, HIGH);
  delay(100);
  digitalWrite(4, LOW);
  cas1 = micros();
  while (digitalRead(5) == HIGH){
    if (digitalRead(5) == LOW){
        cas2 = micros();
        tmr = cas2 - cas1;
        Serial.println(tmr);
        if (tmr >= 40) {
            Serial.println("MAM ROSU");
          }
        delay(400);
    }
  }
}
