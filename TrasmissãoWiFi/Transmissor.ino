#include <ESP8266WiFi.h>
#include <U8g2lib.h>

//U8g2 Constructor List - https://github.com/olikraus/u8g2/wiki/u8g2setupcpp#introduction
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 5, /* data=*/ 4);

const char *ssid = "RedeWIFI_NodeMCU";
const char *password = "123456789";

int valor = 0;        // value read from the potentiometer

void setup() {
  Serial.begin(9600);
  pinMode(D5, INPUT);
  delay(10);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  u8g2.begin();
  u8g2.setFont(u8g2_font_logisoso62_tn);
  u8g2.setFontMode(0);    // enable transparent mode, which is faster
}

void loop() {
  // read the analog in value:
  valor = digitalRead(D5);


  // print the results to the Serial Monitor:
  Serial.print("valor enviado = ");
  Serial.print(valor);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const char * host = "192.168.4.1";
  const int httpPort = 80;

  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String url = "/data/";
  url += "?sensor_reading=";
  url += valor;

  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0)
  {
    if (millis() - timeout > 100)
    {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  //  Serial.println();
  //  Serial.println("Closing connection");
  //  Serial.println();
}
