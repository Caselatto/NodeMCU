void finaliza()
{
  dt = (millis() - tempo_prev) / 1000.0;
  tempo_prev = millis();

  //  if (OFFSET)
  //  {
  //    offAX = AmX;
  //    offAY = AmY;
  //    offAZ = AmZ;
  //
  //    VelX = 0;
  //    VelY = 0;
  //    VelZ = 0;
  //
  //    /*
  //        offRoll = Roll;
  //        offPitch = Pitch;
  //        offYaw = Yaw;
  //    */
  //    OFFSET = !OFFSET;
  //  }
  led_state = !led_state;
  digitalWrite(LED1, led_state);
  digitalWrite(LED2, !led_state);         // pisca LED do NodeMCU a cada leitura do sensor
  Serial.println();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void offset()
{
  //  Serial.println();
  //  Serial.println("Botão offset pressionado");
  //  Serial.println();
  //  OFFSET = true;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void converterRAW()
{
  AcX = double(AX) / convACEL;
  AcY = double(AY) / convACEL;
  AcZ = double(AZ) / convACEL;
  Tmp = (double(Tp) + 12412.0) / 340.0;
  GyX = double(GX) / convGYRO;
  GyY = double(GY) / convGYRO;
  GyZ = double(GZ) / convGYRO;
}
