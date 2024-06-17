#include <LedControl.h>
#include <LiquidCrystal_I2C.h>

// Definindo os pinos de conexão para o display de LEDs
#define CLK 13
#define DIN 11
#define CS  10

#define I2C_ADDR    0x27 // Endereço I2C do display LCD
#define LCD_COLUMNS 16 // Número de colunas do LCD
#define LCD_LINES   2 // Número de linhas do LCD

int buzzer = 9;
int lapCounter = 0; // Variável para contar as voltas

// Criando um objeto LedControl para um dispositivo MAX7219
LedControl lc = LedControl(DIN, CLK, CS, 8); // DIN, CLK, CS, número de dispositivos (1 MAX7219)
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES); // Criação do objeto LCD

void setup() {
  pinMode(buzzer, OUTPUT);

  // Inicializando o display de LEDs
  for (int i = 0; i < 8; i++) {
    lc.shutdown(i, false);       // Acorda o MAX7219 do modo de economia de energia
    lc.setIntensity(i, 8);       // Define o brilho (0 a 15)
    lc.clearDisplay(i);          // Limpa o display
  }

  // Inicializando o LCD
  lcd.begin(16, 2);
  lcd.print("Volta atual:");
  lcd.setCursor(0, 1);
  lcd.print(lapCounter);
}

void loop() {
  largada();  // Inicia a sequência de largada
  delay(1000);

  for (int lap = 1; lap <= 10; lap++) { // Simula 10 voltas como exemplo
    lapCounter++;
    displayLapCount(lapCounter);
    tone(buzzer, 1000, 200); // Bipe curto para indicar uma volta
    delay(2000); // Simula o tempo de uma volta
  }

  // Reiniciar contador
  lapCounter = 0;
}

void largada() {
  noTone(buzzer);
  for (int i = 3; i >= 0; i--) {
    circulo(i, true);
    tone(buzzer, 1000);
    delay(500);
    noTone(buzzer);
    delay(500);
  }

  // Sinal de largada
  tone(buzzer, 1000);
  for (int i = 0; i < 8; i++) {
    circulo(i, true);
  }
  delay(2000);
  for (int i = 0; i < 8; i++) {
    circulo(i, false);
  }
  noTone(buzzer);
}

void displayLapCount(int lap) {
  lcd.clear();
  lcd.print("Volta atual:");
  lcd.setCursor(0, 1);
  lcd.print(lap);
}

void circulo(int pos, bool light) {
  bool pattern[8][8] = {
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0}
  };

  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      lc.setLed(pos, row, col, pattern[row][col] && light);
    }
  }
}
