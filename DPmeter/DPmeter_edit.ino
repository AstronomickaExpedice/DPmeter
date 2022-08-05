//TEPLOMĚR NEFUNKČNÍ
#include <OneWire.h>
#include "DallasTemperature.h"
//Include Dallas teploměr a OneWire
#define ONE_WIRE_PIN 6
//Nadefinování měřícího pinu
OneWire oneWire(ONE_WIRE_PIN);

DallasTemperature sensors(&oneWire);
unsigned long cas1 = 0;
unsigned long cas2 = 0;
unsigned long tmr = 0;
//nastavení výchozích hodnot proměnných pro měření času
int kapacita = 0;
//nastavení výchozí hodnoty proměnné pro zápis funkce
void setup() {
  Serial.begin(9600);
  //setup výstupu na 9600 baudu
}

void loop() {
  kapacita = Mereni();
  Serial.println(kapacita);
       if (kapacita >= 45) {
        Serial.println("MAM ROSU");
   }
   //podmínka pro oznámení stavu na PCB
}
//základní cyklus s printem funkce

int Mereni() {
  cas1 = 0;
  cas2 = 0;
  tmr = 0;
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(5, HIGH);
  digitalWrite(4, HIGH);
  delay(500);
  pinMode(5, INPUT);
  digitalWrite(4, LOW);
  cas1 = micros();
  while (1) {
    if (digitalRead(5) == LOW){
      cas2 = micros();
      tmr = cas2 - cas1;
      return tmr;
  }
 }
  
}
