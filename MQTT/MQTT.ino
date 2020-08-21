#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "WiFi-MatheusCaselatto";
const char* password = "123456789";
const char* mqtt_server = "broker.mqttdashboard.com";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup()
{
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(9600);
  Conectar_WiFi();
  Conectar_MQTT();
}

void loop()
{
  if (!client.connected())
  {
    Reconectar();
  }
  client.loop();

    ++value;
    snprintf (msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("MQTT/Um", msg);
}
