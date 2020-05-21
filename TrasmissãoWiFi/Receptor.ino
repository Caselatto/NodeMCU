// Setup the server to receive data over WiFi
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Configuration parameters for Access Point
const char *ssid = "RedeWIFI_NodeMCU";
const char *password = "123456789";

IPAddress ip(192, 168, 11, 4);
IPAddress gateway(192, 168, 11, 1);
IPAddress subnet(255, 255, 255, 0);

// Set up the server object
ESP8266WebServer server;

// Data received
double value = 0.00;
#define LED1 D8
#define LED2 D7

void setup()
{
  delay(500);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);

  Serial.begin(9600);
  Serial.println("Começando");

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip, gateway, subnet);
  WiFi.softAP(ssid, password);

  // Print IP for check
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Configure the server's route
  server.on("/", handleIndex); //Use the top root to report the last sensor value
  server.on("/update", handleUpdate); //Use this route to update the sensor value
  server.begin();
}

void loop()
{
  server.handleClient();
  if (value == 0)
  {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
  }
  if (value == 1)
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
  }
}

void handleIndex()
{
  server.send(200, "text/plain", String(value)); //Needs refresh for update
  delay(100);
  handleIndex();
}

void handleUpdate()
{
  value = server.arg("value").toFloat();
  Serial.print(value);
  Serial.print("\t");
  Serial.println(millis());
  //  server.send(200, "text/plain", "Updated");
}
