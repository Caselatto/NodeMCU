
void offset()
{
  //  Serial.println();
  //  Serial.println("Botão offset pressionado");
  //  Serial.println();
  OFFSET = true;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void PitchRollYaw()
{
  //A partir de los valores del acelerometro, se calculan los angulos Y, X
  //respectivamente, con la formula de la tangente.
  Acc[1] = atan(-1 * AcX / sqrt(pow(AcY, 2) + pow(AcZ, 2))) * 57.295779;
  Acc[0] = atan(AcY / sqrt(pow(AcX, 2) + pow(AcZ, 2))) * 57.295779;

  //Aplicar el Filtro Complementario
  Pitch = 0.98 * (Pitch + GyX * dt) + 0.02 * Acc[0];
  Roll = 0.98 * (Roll + GyY * dt) + 0.02 * Acc[1];
  //Integración respecto del tiempo paras calcular el YAW
  Yaw = Yaw + GyZ * dt;

  Roll = confANG(Roll) - offRoll;
  Pitch = confANG(Pitch) - offPitch;
  Yaw = confANG(Yaw) - offYaw;

  //  corrigirANGULO();
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

float confANG(float valor)
{
  if (valor > 180)
  {
    valor = valor - 360;
  }
  else if (valor < -180)
  {
    valor = valor + 360;
  }
  return (valor);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void corrigirANGULO()
{
  Roll = Roll - (-0.03 / 2764);
  Pitch = Pitch - (-0.06 / 2764);
  Yaw = Yaw - (70.87 / 2764);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void velocidade(double aX, double aY, double aZ)
{
  if (!OFFSET)
  {
    VelX = VelX + (aX - offAX) * dt;
    VelY = VelY + (aY - offAY) * dt;
    VelZ = VelZ + ((aZ - offAZ) * dt);
    offAX = aX;
    offAY = aY;
    offAZ = aZ;

    //    VelX = VelX * 3.6;
    //    VelY = VelY * 3.6;
    //    VelZ = VelZ * 3.6;
  }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void finaliza()
{
  dt = (millis() - tempo_prev) / 1000.0;
  tempo_prev = millis();

  if (OFFSET)
  {
    offAX = AcX;
    offAY = AcY;
    offAZ = AcZ;

    VelX = 0;
    VelY = 0;
    VelZ = 0;

    /*
        offRoll = Roll;
        offPitch = Pitch;
        offYaw = Yaw;
    */
    OFFSET = !OFFSET;
  }
  led_state = !led_state;
  digitalWrite(LED1, led_state);
  digitalWrite(LED2, !led_state);         // pisca LED do NodeMCU a cada leitura do sensor
  Serial.println();
}
