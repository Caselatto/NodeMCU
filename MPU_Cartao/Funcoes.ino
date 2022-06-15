
void finaliza()
{
  led_state = !led_state;
  digitalWrite(LED1, led_state);
  digitalWrite(LED2, !led_state);         // pisca LED do NodeMCU a cada leitura do sensor
  Serial.println();

#ifdef CARTAO
  sdFile.println();
  sdFile.flush();
#endif
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void converterRAW()
{
  AcX = (double(AX) / convACEL);
  AcY = (double(AY) / convACEL);
  AcZ = (double(AZ) / convACEL);
  Tmp = (double(Tp) + 12412.0) / 340.0;
  GyX = double(GX) / convGYRO;
  GyY = double(GY) / convGYRO;
  GyZ = double(GZ) / convGYRO;

  if (offAX == 0 && offAY == 0 && offAZ == 0 && offGX == 0 && offGY == 0 && offGZ == 0) {
    offAX = AcX;
    offAY = AcY;
    offAZ = AcZ;
    offGX = GyX;
    offGY = GyY;
    offGZ = GyZ;
  }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void PitchRollYaw(double aX, double aY, double aZ, double gX, double gY, double gZ)
{
  //A partir de los valores del acelerometro, se calculan los angulos Y, X
  //respectivamente, con la formula de la tangente.
  Acc[1] = atan(-1 * aX / sqrt(pow(aY, 2) + pow(aZ, 2))) * RAD_TO_DEG;
  Acc[0] = atan(aY / sqrt(pow(aX, 2) + pow(aZ, 2))) * RAD_TO_DEG;
  Acc[2] = atan(aZ / sqrt(pow(aX, 2) + pow(aZ, 2))) * RAD_TO_DEG;

  //Aplicar el Filtro Complementario
  Roll = 0.98 * (Roll + gX * dt) + 0.02 * Acc[0];
  Pitch = 0.98 * (Pitch + gY * dt) + 0.02 * Acc[1];
  //Integración respecto del tiempo paras calcular el YAW
  Yaw = Yaw + gZ * dt;

  if (offRoll == 0 && offPitch == 0 && offYaw == 0) {
    offRoll = Roll;
    offPitch = Pitch;
    offYaw = Yaw;
  }

  Roll = confANG(Roll);
  Pitch = confANG(Pitch);
  Yaw = confANG(Yaw);
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
    VelZ = VelZ + (aZ - offAZ) * dt;
    //    offAX = aX;
    //    offAY = aY;
    //    offAZ = aZ;

    //    VelX = VelX * 3.6;
    //    VelY = VelY * 3.6;
    //    VelZ = VelZ * 3.6;
  }
}
