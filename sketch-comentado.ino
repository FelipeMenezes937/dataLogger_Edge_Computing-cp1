<<<<<<< HEAD
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

=======
#include <LiquidCrystal.h>  // Biblioteca para controlar o display LCD

// Define os pinos do LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

int ldr = A0;        // Pino analógico conectado ao LDR (sensor de luminosidade)
int buzz = 13;       // Pino conectado ao buzzer
int valorldr = 0;    // Variável para armazenar a leitura do LDR
int ledG = 6;        // Pino do LED verde
int ledY = 7;        // Pino do LED amarelo
int ledR = 8;        // Pino do LED vermelho

int nloops = 0;      // Contador de leituras (quantas vezes o LDR foi lido)
float somaldr = 0;   // Soma de todas as leituras para calcular a média
int mediaLDR = 0;    // Valor médio das leituras

void setup() {
  lcd.begin(16, 2);         // Inicializa o display LCD 16x2
  lcd.clear();              // Limpa o display
  lcd.setCursor(0, 0);      // Define o cursor na primeira linha, primeira coluna
  lcd.print("Luminosidade:");// Escreve o título no LCD

  // Define os pinos como saída ou entrada
>>>>>>> 6905b358c4a17c76dde02d67cf6f6c401e583834
  pinMode(ledG, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ldr, INPUT);
  pinMode(buzz, OUTPUT);

<<<<<<< HEAD
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
=======
  Serial.begin(9600);       // Inicializa a comunicação serial (para monitor)
}

void loop() {
  valorldr = analogRead(ldr); // Faz a leitura do LDR (0 a 1023)
  somaldr += valorldr;        // Soma a leitura ao acumulador
  nloops++;                   // Incrementa o contador de leituras

  if (nloops == 10) {         // Quando tiver 10 leituras acumuladas
    mediaLDR = somaldr / nloops;  // Calcula a média das leituras

    // Converte a média de 0–1023 para uma escala de 0–100
    int valorMapeado = map(mediaLDR, 0, 1023, 0, 100);

    // Atualiza a linha 2 do LCD
    lcd.setCursor(0, 1);
    lcd.print("                "); // Apaga a linha (16 espaços)
    lcd.setCursor(0, 1);
    lcd.print(valorMapeado);       // Mostra a luminosidade em %
	lcd.print("%");					//Mostra o sinal de porcentagem
    
    // Também envia para o monitor serial
>>>>>>> 6905b358c4a17c76dde02d67cf6f6c401e583834
    Serial.print("Media LDR: ");
    Serial.println(valorMapeado);
    

<<<<<<< HEAD
    // Primeiro desliga todos LEDs e buzzer
=======
    // Desliga todos os LEDs e o buzzer antes de checar condições
>>>>>>> 6905b358c4a17c76dde02d67cf6f6c401e583834
    digitalWrite(ledR, LOW);
    digitalWrite(ledY, LOW);
    digitalWrite(ledG, LOW);
    noTone(buzz);

<<<<<<< HEAD
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
=======
    // Checa as condições de luminosidade
    if (valorMapeado > 80) {
      // Muito claro → LED vermelho aceso + buzzer forte
      digitalWrite(ledR, HIGH);
      tone(buzz, 5000); // Frequência alta
    }
    else if (valorMapeado >= 60 && valorMapeado <= 80) {
      // Luminosidade média → LED amarelo aceso + buzzer fraco intermitente
      digitalWrite(ledY, HIGH);
      tone(buzz, 300);  // Frequência baixa
      delay(3000);      // Espera 3 segundos
      noTone(buzz);     // Desliga o buzzer
    }
    else if (valorMapeado < 60) {
      // Pouca luz → LED verde aceso, buzzer desligado
      digitalWrite(ledG, HIGH);
>>>>>>> 6905b358c4a17c76dde02d67cf6f6c401e583834
    }

    // Reseta os acumuladores para o próximo ciclo de médias
    nloops = 0;
    somaldr = 0;
  }

<<<<<<< HEAD
  delay(250); // Intervalo entre leituras
=======
  delay(500); // Espera meio segundo antes da próxima leitura
>>>>>>> 6905b358c4a17c76dde02d67cf6f6c401e583834
}