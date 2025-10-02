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
  pinMode(ledG, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ldr, INPUT);
  pinMode(buzz, OUTPUT);

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
    Serial.print("Media LDR: ");
    Serial.println(valorMapeado);
    

    // Desliga todos os LEDs e o buzzer antes de checar condições
    digitalWrite(ledR, LOW);
    digitalWrite(ledY, LOW);
    digitalWrite(ledG, LOW);
    noTone(buzz);

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
    }

    // Reseta os acumuladores para o próximo ciclo de médias
    nloops = 0;
    somaldr = 0;
  }

  delay(500); // Espera meio segundo antes da próxima leitura
}