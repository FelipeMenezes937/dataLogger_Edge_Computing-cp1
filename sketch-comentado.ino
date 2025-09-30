#include <LiquidCrystal.h>  
// Biblioteca para controlar o display LCD

// Define os pinos de conexão do LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

// Definição dos pinos usados no projeto
int ldr = A0;     // Entrada analógica do LDR (sensor de luminosidade)
int buzz = 13;    // Pino do buzzer
int valorldr = 0; // Variável para armazenar a leitura do LDR
int ledG = 6;     // LED verde
int ledY = 7;     // LED amarelo
int ledR = 8;     // LED vermelho

// Variáveis auxiliares para calcular a média das leituras
int nloops = 0;        // Contador de loops
float somaldr = 0;     // Acumula valores lidos pelo LDR
int mediaLDR = 0;      // Média das leituras do LDR

void setup() {
  // Inicializa o LCD com 16 colunas e 2 linhas
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0); // Coloca o cursor na primeira linha
  lcd.print("Luminosidade:"); // Mensagem inicial no LCD

  // Configura pinos como entrada ou saída
  pinMode(ledG, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ldr, INPUT);
  pinMode(buzz, OUTPUT);

  // Inicializa comunicação serial (para monitoramento no PC)
  Serial.begin(9600);
}

void loop() {
  // Faz a leitura do sensor LDR
  valorldr = analogRead(ldr);
  somaldr += valorldr; // Soma os valores lidos
  nloops++;            // Incrementa o contador

  // A cada 10 leituras, calcula a média
  if (nloops == 10) {
    mediaLDR = somaldr / nloops;

    // Mapeia o valor para uma escala de 0 a 100 invertida
    // (quanto mais luz, menor o valor)
    int valorMapeado = map(mediaLDR, 0, 1023, 100, 0);

    // Atualiza o display LCD
    lcd.setCursor(0, 1); // Vai para a segunda linha
    lcd.print("  ");      // Limpa a linha
    lcd.setCursor(0, 1);
    lcd.print(valorMapeado);
    lcd.print("%");       // Mostra a porcentagem

    // Envia os dados para o monitor serial
    Serial.print("Media LDR: ");
    Serial.println(valorMapeado);

    // Desliga LEDs e buzzer antes de verificar as condições
    digitalWrite(ledR, LOW);
    digitalWrite(ledY, LOW);
    digitalWrite(ledG, LOW);
    noTone(buzz);

    // Verifica condições de luminosidade:
    if (valorMapeado > 80) {
      // Ambiente muito iluminado → LED vermelho e buzzer forte
      digitalWrite(ledR, HIGH);
      tone(buzz, 5000); // Frequência alta (som forte)
    }
    else if (valorMapeado >= 60 && valorMapeado <= 80) {
      // Luminosidade média → LED amarelo e buzzer fraco por 3s
      digitalWrite(ledY, HIGH);
      tone(buzz, 300);  // Frequência baixa (som fraco)
      delay(3000);
      noTone(buzz);     // Para o buzzer após o tempo
    }
    else if (valorMapeado < 60) {
      // Ambiente pouco iluminado → LED verde, sem som
      digitalWrite(ledG, HIGH);
    }

    // Reseta variáveis para próxima média
    nloops = 0;
    somaldr = 0;
  }

  // Intervalo entre leituras (meio segundo)
  delay(500);
}
