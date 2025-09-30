#include <LiquidCrystal.h>
 
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);
 
int ldr = A0;
int buzz = 13;
int valorldr = 0;
int ledG = 6;
int ledY = 7;
int ledR = 8;
 
int nloops = 0;           
float somaldr = 0;        
int mediaLDR = 0;
 
void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Luminosidade:");
 
  pinMode(ledG, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ldr, INPUT);
  pinMode(buzz, OUTPUT);
 
  Serial.begin(9600);
}
 
void loop() {
  valorldr = analogRead(ldr); 
  somaldr += valorldr;
  nloops++;
 
  if (nloops == 10) { 
    mediaLDR = somaldr / nloops;
 
    int valorMapeado = map(mediaLDR, 0, 1023, 100, 0); 
 
    lcd.setCursor(0, 1);
    lcd.print("  ");
    lcd.setCursor(0, 1);
    lcd.print(valorMapeado);
    lcd.print("%");
 
    Serial.print("Media LDR: ");
    Serial.println(valorMapeado);
 
    digitalWrite(ledR, LOW);
    digitalWrite(ledY, LOW);
    digitalWrite(ledG, LOW);
    noTone(buzz);
 
    if (valorMapeado > 80) {
      digitalWrite(ledR, HIGH);
      tone(buzz, 5000);
    }
    else if (valorMapeado >= 60 && valorMapeado <= 80) {
      digitalWrite(ledY, HIGH);
      tone(buzz, 300);
      delay(3000);
      noTone(buzz);
    }
    else if (valorMapeado < 60) {
      digitalWrite(ledG, HIGH);
    }
    nloops = 0;
    somaldr = 0;
  }
 
  delay(500);
}


