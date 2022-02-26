#include <ESP8266WiFi.h>
#include "Wire.h"     //  Biblioteca de comunicação I2C 

// Tempo
double dt, tempo_prev = 0.00;

// Armazenamento dos dados "crus" do acelerômetro
int16_t AX, AY, AZ, Tp, GX, GY, GZ;

// Armazenamento dos dados após conversão
double AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
long convGYRO, convACEL;     // Datasheet do sensor

// Leds piscando alternado a cada ciclo do loop
#define LED1 D8
#define LED2 D7
bool led_state = false;

// Parametros de configuração para Access Point
const char *ssid = "RedeWIFI_NodeMCU";
const char *password = "123456789";
const char *host = "192.168.11.4";
WiFiClient client; // Define o objeto cliente

void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, led_state);
  digitalWrite(LED2, led_state);
  //  Serial.begin(9600);

  setup_MPU();
  setup_transmissao();
}

void loop()
{
  readRaw_MPU();
  converterRAW();

  //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  //  mostraRAW();
  //  mostraCON();
  Serial.print("\t" + String(dt));

  //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  envia();
  finaliza();
}
