#include <LiquidCrystal.h>  
// Biblioteca para controlar o display LCD 16x2

// Pinos do LCD conectados no Arduino: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

// Declaração dos pinos usados
int ldr = A0;     // Sensor de luminosidade (LDR)
int buzz = 13;    // Buzzer
int valorldr = 0; // Valor lido do LDR
int ledG = 6;     // LED verde
int ledY = 7;     // LED amarelo
int ledR = 8;     // LED vermelho

// Variáveis auxiliares para média das leituras
int nloops = 0;           // Contador de leituras
float somaldr = 0;        // Soma dos valores lidos
int mediaLDR = 0;         // Média calculada

// ==================== CARACTERES CUSTOMIZADOS ====================
// Cada bloco representa 1 parte de uma letra feita em "pixels" no LCD
// Como o LCD só permite 8 caracteres customizados, dividimos letras
// grandes em partes (canto superior/esquerdo/direito/inferior).

// Letra "A" - canto superior esquerdo
byte A_topleft[8] = {
  B00000, B00000, B00011, B01111,
  B11000, B11000, B11000, B11000
};
// Letra "A" - canto inferior esquerdo
byte A_botleft[8] = {
  B11111, B11111, B11000, B11000,
  B11000, B11000, B00000, B00000
};
// Letra "A" - canto superior direito
byte A_topright[8] = {
  B00000, B00000, B11000, B11110,
  B00011, B00011, B00011, B00011
};
// Letra "A" - canto inferior direito
byte A_botright[8] = {
  B11111, B11111, B00011, B00011,
  B00011, B00011, B00000, B00000
};

// Letra "P" - canto superior esquerdo
byte P_topleft[8] = {
  B00000, B00000, B11111, B11111,
  B11000, B11000, B11000, B11000
};
// Letra "P" - canto inferior esquerdo
byte P_botleft[8] = {
  B11111, B11111, B11000, B11000,
  B11000, B11000, B00000, B00000
};
// Letra "P" - canto superior direito
byte P_topright[8] = {
  B00000, B00000, B11100, B11110,
  B00011, B00011, B00011, B00011
};
// Letra "P" - canto inferior direito
byte P_botright[8] = {
  B11110, B11100, B00000, B00000,
  B00000, B00000, B00000, B00000
};

// ==================== FUNÇÃO PARA DESENHAR TEXTO ====================
// Essa função recebe uma posição (coluna) e desenha as letras "APAP"
// usando os blocos customizados. Assim conseguimos animar o texto
// passando da direita para a esquerda.
void desenhaTexto(int pos) {
  lcd.clear();

  // Linha superior
  lcd.setCursor(pos, 0);
  lcd.write(byte(0)); // A canto sup. esq
  lcd.write(byte(2)); // A canto sup. dir
  lcd.write(byte(4)); // P canto sup. esq
  lcd.write(byte(6)); // P canto sup. dir
  lcd.write(byte(0)); // A canto sup. esq (segunda letra A)
  lcd.write(byte(2)); // A canto sup. dir
  lcd.write(byte(4)); // P canto sup. esq (segunda letra P)
  lcd.write(byte(6)); // P canto sup. dir

  // Linha inferior
  lcd.setCursor(pos, 1);
  lcd.write(byte(1)); // A canto inf. esq
  lcd.write(byte(3)); // A canto inf. dir
  lcd.write(byte(5)); // P canto inf. esq
  lcd.write(byte(7)); // P canto inf. dir
  lcd.write(byte(1)); // A canto inf. esq (segunda letra A)
  lcd.write(byte(3)); // A canto inf. dir
  lcd.write(byte(5)); // P canto inf. esq (segunda letra P)
  lcd.write(byte(7)); // P canto inf. dir
}

void setup() {
  lcd.begin(16, 2); // Inicia o LCD 16x2

  // Registra os 8 caracteres customizados
  lcd.createChar(0, A_topleft);
  lcd.createChar(1, A_botleft);
  lcd.createChar(2, A_topright);
  lcd.createChar(3, A_botright);
  lcd.createChar(4, P_topleft);
  lcd.createChar(5, P_botleft);
  lcd.createChar(6, P_topright);
  lcd.createChar(7, P_botright);

  // ==================== ANIMAÇÃO INICIAL ====================
  // O texto começa fora da tela (coluna 16) e vai andando até sair pela esquerda (-8).
  for (int pos = 16; pos >= -8; pos--) { 
    desenhaTexto(pos);  // Desenha as letras na posição
    delay(250);         // Controla a velocidade do movimento
  }

  delay(1500); // Pausa no final da animação
  lcd.clear();

  // ==================== CONFIGURAÇÃO DOS COMPONENTES ====================
  lcd.setCursor(0, 0);
  lcd.print("Luminosidade:"); // Título fixo no LCD

  pinMode(ledG, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ldr, INPUT);
  pinMode(buzz, OUTPUT);

  Serial.begin(9600); // Inicia comunicação serial
}

void loop() {
  // Lê o valor do LDR
  valorldr = analogRead(ldr);
  somaldr += valorldr; // Soma os valores para média
  nloops++;

  if (nloops == 10) { // Faz a média a cada 10 leituras
    mediaLDR = somaldr / nloops;
    int valorMapeado = map(mediaLDR, 0, 1023, 0, 100); // Converte para escala 0–100%

    // Mostra valor no LCD
    lcd.setCursor(0, 1);
    lcd.print("    "); // Limpa linha
    lcd.setCursor(0, 1);
    lcd.print(valorMapeado);
    lcd.print("%");

    // Mostra no Serial Monitor também
    Serial.print("Media LDR: ");
    Serial.println(valorMapeado);

    // Primeiro desliga todos LEDs e buzzer
    digitalWrite(ledR, LOW);
    digitalWrite(ledY, LOW);
    digitalWrite(ledG, LOW);
    noTone(buzz);

    // ==================== CONDIÇÕES DE LUMINOSIDADE ====================
    if (valorMapeado >= 80) {            // Alta luminosidade
      digitalWrite(ledR, HIGH);          // LED vermelho aceso
      tone(buzz, 1000);                  // Buzzer contínuo em 1 kHz
    }
    else if (valorMapeado >= 60) {       // Luminosidade média
      digitalWrite(ledY, HIGH);          // LED amarelo aceso
      tone(buzz, 5000);                  // Buzzer liga
      delay(3000);                       // Fica ligado 1s
      noTone(buzz);                      // Desliga buzzer
    }
    else {                               // Baixa luminosidade
      digitalWrite(ledG, HIGH);          // LED verde aceso
    }

    // Reseta variáveis para próxima média
    nloops = 0;
    somaldr = 0;
  }

  delay(250); // Intervalo entre leituras
}