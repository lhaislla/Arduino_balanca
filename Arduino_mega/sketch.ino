// Lhaíslla E. Cavalcanti 
// Objetivo: Coletar dado da Balança de aditivos

//Bibliotecas para armazenar em um cartão de memória

#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SD.h>
#include "RTClib.h"

RTC_DS1307 rtc; // Inicializa o objeto para o RTC DS3231

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Endereço 0x27 para o LCD 16x2
#define B_VEM     A0
#define B_VED     A1
#define B_AMA     A2
#define RESET     A3
#define ENVIAR    A4
#define LIDER     A5
#define CS_PIN    10

File dataFileB1;
File dataFileB2;
File dataFileB3;

float b1 = 0.0;
float b2 = 0.0;
float b3 = 0.0;
int lider = 0;
int ultimoBotaoPressionado = -1;
int contadorB1 = 0;
int contadorB2 = 0;
int contadorB3 = 0;
float somaB1 = 0.0;
float somaB2 = 0.0;
float somaB3 = 0.0;
bool enviado = false;

void atualizarLCD(String prefixo, float valor) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(prefixo);
  lcd.print(valor, 2);  // Ajusta a precisão dos floats para 2 casas decimais
}

void exibirErroSD(String mensagem) {
  lcd.clear();
  lcd.print("Erro no cartao SD:");
  lcd.setCursor(0, 1);
  lcd.print(mensagem);
}

void gravarNoSD(String nomeArquivo, int contador, float valor, float soma) {
  File arquivo = SD.open(nomeArquivo, FILE_WRITE);
  if (arquivo) {
    arquivo.print(nomeArquivo.substring(0, 2) + "/" + nomeArquivo.substring(3, 5) + "/" + nomeArquivo.substring(6, 10) + "_");
    arquivo.print("contador = ");
    arquivo.print(contador);
    arquivo.print("; valor = ");
    arquivo.print(valor);
    arquivo.print("; soma = ");
    arquivo.println(soma);
    arquivo.close();
  } else {
    exibirErroSD("Erro ao escrever " + nomeArquivo);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(B_VEM, INPUT_PULLUP);
  pinMode(B_VED, INPUT_PULLUP);
  pinMode(B_AMA, INPUT_PULLUP);
  pinMode(RESET, INPUT_PULLUP);
  pinMode(LIDER, INPUT_PULLUP);
  pinMode(ENVIAR, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.backlight();

  if (!rtc.begin()) {
    lcd.clear();
    lcd.print("RTC sem conexao");
    lcd.setCursor(0, 1);
    lcd.print("Alerta conexoes!");
    while (1);
  }

  if (0) {
    lcd.clear();
    lcd.print("RTC perdeu energia,");
    lcd.setCursor(0, 1);
    lcd.print("ajuste a data e hora!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  if (digitalRead(B_VEM) == LOW) {
    b1 = digitalRead(B_VEM);
    ultimoBotaoPressionado = B_VEM;
    contadorB1++;
    somaB1 += b1;
    atualizarLCD("B1: ", b1);
    delay(1000);
  } else if (digitalRead(B_VED) == LOW) {
    b2 = digitalRead(B_VED);
    ultimoBotaoPressionado = B_VED;
    contadorB2++;
    somaB2 += b2;
    atualizarLCD("B2: ", b2);
    delay(1000);
  } else if (digitalRead(B_AMA) == LOW) {
    b3 = digitalRead(B_AMA);
    ultimoBotaoPressionado = B_AMA;
    contadorB3++;
    somaB3 += b3;
    atualizarLCD("B3: ", b3);
    delay(1000);
  } else if (digitalRead(RESET) == LOW) {
    if (ultimoBotaoPressionado == B_VEM) {
      somaB1 -= b1; // Subtrai o último valor de b1 da soma
      contadorB1--; // Decrementa o contador
      b1 = 0.0; // Reseta o valor de b1
      atualizarLCD("B1 RESETADO: ", b1);
    } else if (ultimoBotaoPressionado == B_VED) {
      somaB2 -= b2; // Subtrai o último valor de b2 da soma
      contadorB2--; // Decrementa o contador
      b2 = 0.0; // Reseta o valor de b2
      atualizarLCD("B2 RESETADO: ", b2);
    } else if (ultimoBotaoPressionado == B_AMA) {
      somaB3 -= b3; // Subtrai o último valor de b3 da soma
      contadorB3--; // Decrementa o contador
      b3 = 0.0; // Reseta o valor de b3
      atualizarLCD("B3 RESETADO: ", b3);
    }
  } else if (digitalRead(LIDER) == LOW) {
    lider = 1 - lider;
    atualizarLCD("LIDER: ", lider);
    delay(1000);
  } else if (digitalRead(ENVIAR) == LOW && !enviado) {
    enviado = true;
    if (ultimoBotaoPressionado == B_VEM) {
      gravarNoSD("B1.txt", contadorB1, b1, somaB1);
    } else if (ultimoBotaoPressionado == B_VED) {
      gravarNoSD("B2.txt", contadorB2, b2, somaB2);
    } else if (ultimoBotaoPressionado == B_AMA) {
      gravarNoSD("B3.txt", contadorB3, b3, somaB3);
    }
    delay(1000);
  } else if (digitalRead(ENVIAR) == HIGH) {
    enviado = false;
  }
}
