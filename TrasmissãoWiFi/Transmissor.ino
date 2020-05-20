// Setup the server to receive data over WiFi
#include <ESP8266WiFi.h>

// Data send
int valor = 100;

// Configuration parameters for Access Point
const char *ssid = "RedeWIFI_NodeMCU";
const char *password = "123456789";
const char *host = "192.168.11.4";

// Set up the server object
WiFiClient client;

void setup()
{
  delay(500);
  Serial.begin(9600);
  pinMode(D5, INPUT);

  //Conect to the server
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(". ");
    delay(500);
  }
  Serial.println();
  Serial.print("IP Adress (AP): ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  valor = digitalRead(D5);

  // Connect to the server and send data
  if (client.connect(host, 80))
  {
    String url = "/update?value=";
    url += String(valor);
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: keep-alive\r\n\r\n");
    delay(10);
    // Read all the lines of the response and print them to Serial
    Serial.println("Resposta: ");
    while (client.available())
    {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
  }
}
