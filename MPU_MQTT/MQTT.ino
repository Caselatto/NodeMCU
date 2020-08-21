const char* ssid = "Oi_Velox_Mariza";
const char* password = "mariza3884";
const char* mqtt_server = "broker.mqttdashboard.com";

//WiFiClient espClient;
//PubSubClient client(espClient);
unsigned long lastMsg = 0;

void Conectar_WiFi()
{
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void Conectar_MQTT()
{
  client.setServer(mqtt_server, 1883);

  // Loop until we're connected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("MQTT/Um", "hello world");
      // ... and resubscribe
      client.subscribe("MQTT/Dois");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 1 second");
      // Wait before retrying
      delay(1000);
    }
  }

  client.setCallback(Receber);
}

void Reconectar()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Conectar_WiFi();
  }
  if (!client.connected())
  {
    Conectar_MQTT();
  }
}

void Receber(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
  } else {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
  }
}
