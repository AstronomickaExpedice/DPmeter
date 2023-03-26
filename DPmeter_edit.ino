#include <DallasTemperature.h>
#include <OneWire.h>
#define ONE_WIRE_PIN 6  //definování pinu pro teploměr (měření)
OneWire oneWire(ONE_WIRE_PIN);  //nastavení instance pro komunikaci se senzorem
DallasTemperature sensors(&oneWire);  //Reference ze senzoru přes oneWire knihovny
unsigned long cas1 = 0;
unsigned long cas2 = 0;
unsigned long tmr = 0;
int n = 0;
//nastavení výchozích hodnot proměnných pro měření času
int kapacita = 0;   //nastavení výchozí hodnoty proměnné pro zápis funkce
int teplota = 0;    //nastavení výchozí hodnoty proměnné pro zápis funkce
void setup() {
  Serial.begin(9600);   //setup zobrazení výstupu na 9600 baudu
  sensors.begin();  //začátek měření
  pinMode(8, OUTPUT); 
  pinMode(9, OUTPUT);
  //nastavení pinů pro H-bridge
}

void loop() {
  kapacita = Mereni();
  teplota = MereniTeploty();
  Serial.print("Kapacita: ");
  Serial.println(kapacita);
  Serial.print("Teplota: ");
  Serial.print(teplota);
  Serial.print("°C\n");
    if (kapacita >= 45) {
      Serial.println("MAM ROSU");
      n++;
      if (n >= 3){
        Peltier_ohrv();
      }
 }
      //podmínka pro oznámení stavu na PCB
    else{
      n = 0;
      Peltier_chlz();
    }
   Serial.println("-----------------");
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
  delay(250);
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

int MereniTeploty() {
  sensors.requestTemperatures();  //volání výstupu senzoru
  return sensors.getTempCByIndex(0);
}

void Peltier_chlz() {
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  Serial.println("PELTIER: chlazení");
}

void Peltier_ohrv() {
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  Serial.println("PELTIER: probíhá ohřev pro opětovné měření");
}
