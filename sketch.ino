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

byte A_topleft[8] = {
  B00000, B00000, B00011, B01111,
  B11000, B11000, B11000, B11000
};
byte A_botleft[8] = {
  B11111, B11111, B11000, B11000,
  B11000, B11000, B00000, B00000
};
byte A_topright[8] = {
  B00000, B00000, B11000, B11110,
  B00011, B00011, B00011, B00011
};
byte A_botright[8] = {
  B11111, B11111, B00011, B00011,
  B00011, B00011, B00000, B00000
};

byte P_topleft[8] = {
  B00000, B00000, B11111, B11111,
  B11000, B11000, B11000, B11000
};
byte P_botleft[8] = {
  B11111, B11111, B11000, B11000,
  B11000, B11000, B00000, B00000
};
byte P_topright[8] = {
  B00000, B00000, B11100, B11110,
  B00011, B00011, B00011, B00011
};
byte P_botright[8] = {
  B11110, B11100, B00000, B00000,
  B00000, B00000, B00000, B00000
};

void desenhaTexto(int pos) {
  lcd.clear();
  lcd.setCursor(pos, 0);
  lcd.write(byte(0));
  lcd.write(byte(2));
  lcd.write(byte(4));
  lcd.write(byte(6));
  lcd.write(byte(0));
  lcd.write(byte(2));
  lcd.write(byte(4));
  lcd.write(byte(6));

  lcd.setCursor(pos, 1);
  lcd.write(byte(1));
  lcd.write(byte(3));
  lcd.write(byte(5));
  lcd.write(byte(7));
  lcd.write(byte(1));
  lcd.write(byte(3));
  lcd.write(byte(5));
  lcd.write(byte(7));
}

void setup() {
  lcd.begin(16, 2);

  lcd.createChar(0, A_topleft);
  lcd.createChar(1, A_botleft);
  lcd.createChar(2, A_topright);
  lcd.createChar(3, A_botright);
  lcd.createChar(4, P_topleft);
  lcd.createChar(5, P_botleft);
  lcd.createChar(6, P_topright);
  lcd.createChar(7, P_botright);

  for (int pos = 16; pos >= -8; pos--) { 
    desenhaTexto(pos);
    delay(250);
  }

  delay(1500);
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
    int valorMapeado = map(mediaLDR, 0, 1023, 0, 100);

    lcd.setCursor(0, 1);
    lcd.print("    ");
    lcd.setCursor(0, 1);
    lcd.print(valorMapeado);
    lcd.print("%");

    Serial.print("Media LDR: ");
    Serial.println(valorMapeado);

    digitalWrite(ledR, LOW);
    digitalWrite(ledY, LOW);
    digitalWrite(ledG, LOW);
    noTone(buzz);

    if (valorMapeado >= 80) {
      digitalWrite(ledR, HIGH);
      tone(buzz, 1000);
    }
    else if (valorMapeado >= 60) {
      digitalWrite(ledY, HIGH);
      tone(buzz, 5000);
      delay(3000);
      noTone(buzz);
    }
    else {
      digitalWrite(ledG, HIGH);
    }

    nloops = 0;
    somaldr = 0;
  }

  delay(250);
}
