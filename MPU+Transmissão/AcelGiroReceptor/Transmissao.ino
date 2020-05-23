void setup_transmissao()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip, gateway, subnet);
  WiFi.softAP(ssid, password);

  // Print IP for check
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Configure the server's route
  server.on("/", handleIndex); //Receber requisições, funciona como interrupções
  server.on("/atual", atualizar);
  server.begin();
}

void handleIndex()
{
  server.send(200, "text/plain", String(millis())); //Needs refresh for update
  //  Serial.print(millis());
}

void atualizar()
{
  AcX = server.arg("AcX").toFloat();
  AcY = server.arg("AcY").toFloat();
  AcZ = server.arg("AcZ").toFloat();

  GyX = server.arg("GyX").toFloat();
  GyY = server.arg("GyY").toFloat();
  GyZ = server.arg("GyZ").toFloat();
}
