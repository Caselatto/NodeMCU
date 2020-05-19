
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "RedeWIFI_NodeMCU";
const char *password = "123456789";

int readingInt = 999;
#define LED1 D8
#define LED2 D6

ESP8266WebServer server(80);

void handleSentVar()
{
  //  Serial.println("handleSentVar function called...");
  if (server.hasArg("sensor_reading")) // this is the variable sent from the client
  {
    Serial.println("Sensor reading received...");
    readingInt = server.arg("sensor_reading").toInt();

    Serial.print("Reading: ");
    Serial.println(readingInt);
    Serial.println();
    //    server.send(200, "text/html", "Data received");
    return;
  }
}

void setup()
{
  delay(1000);
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);


  Serial.println();
  Serial.print("Configuring access point...");

  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/data/", HTTP_GET, handleSentVar); // when the server receives a request with /data/ in the string then run the handleSentVar function
  server.begin();

  Serial.println("HTTP server started");
  Serial.println();

  Serial.print("Connected as ");
  Serial.println(ssid);
  Serial.print("Password: ");
  Serial.println(password);
}

void loop()
{
  server.handleClient();
  if (readingInt == 0)
  {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
  }
  if (readingInt == 1)
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
  }
}
