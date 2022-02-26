void setup_transmissao()
{
  //Conect to the server
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(". ");
    delay(100);
  }
  Serial.println();
  Serial.print("IP Adress (AP): ");
  Serial.println(WiFi.localIP());
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void envia()
{
  // Connect to the server and send data
  if (client.connect(host, 80))
  {
    String url = "/atual?";
    url += "AcX=";
    url += String(AcX);
    url += "&AcY=";
    url += String(AcY);
    url += "&AcZ=";
    url += String(AcZ);
    url += "&GyX=";
    url += String(GyX);
    url += "&GyY=";
    url += String(GyY);
    url += "&GyZ=";
    url += String(GyZ);
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: keep-alive\r\n\r\n");
    /*
      delay(10);
      // Read all the lines of the response and print them to Serial
      Serial.println("Resposta: ");
      while (client.available())
      {
      String line = client.readStringUntil('\r');
      Serial.print(line);
      }
    */
  }
  if (WiFi.status() != WL_CONNECTED)
  {
    setup_transmissao();
  }
}
