#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Armazenamento dos dados após conversão
double AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

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
  setup_transmissao();
}

void loop()
{
  server.handleClient();
  mostraCON();

  Serial.println();
}
