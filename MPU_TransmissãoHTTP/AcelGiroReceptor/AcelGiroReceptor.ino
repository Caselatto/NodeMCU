#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Tempo
double dt, tempo_prev = 0.00;

// Variavel do offset
bool OFFSET = false;
double offAX = 0, offAY = 0, offAZ = 0, offRoll = 0, offPitch = 0, offYaw = 0;
uint8_t botOffset = D5;

// Armazenamento dos dados após conversão
double AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

// Calculo ângulos
double Acc[2];
double Pitch = 0;
double Roll = 0;
double Yaw = 0;
#define RAD_TO_DEG 57.295779  // Radianos para graus (180/PI)

// Calculo velocidade
double VelX, VelY, VelZ;

// Leds piscando alternado a cada ciclo do loop
#define LED1 D8
#define LED2 D7
bool led_state = false;

// Parametros de configuração para Access Point
const char *ssid = "RedeWIFI_NodeMCU";
const char *password = "123456789";
IPAddress ip(192, 168, 11, 4);
IPAddress gateway(192, 168, 11, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server; // Define o objeto server

void setup()
{
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, led_state);
  digitalWrite(LED2, led_state);

  setup_transmissao();

  attachInterrupt(digitalPinToInterrupt(botOffset), offset, RISING);
}

void loop()
{
  server.handleClient();

  PitchRollYaw();
  velocidade(AcX, AcY, AcZ);

  //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  mostraCON();
  mostraANG();
  mostraVEL();
  Serial.print("\t" + String(dt));

  //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  finaliza();
}
