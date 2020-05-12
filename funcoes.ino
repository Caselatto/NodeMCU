void converterRAW()
{
  AcX = float(AX) / convACEL;
  AcY = float(AY) / convACEL;
  AcZ = float(AZ) / convACEL;
  Tmp = (float(Tp) + 12412.0) / 340.0;
  GyX = float(GX) / convGYRO;
  GyY = float(GY) / convGYRO;
  GyZ = float(GZ) / convGYRO;
  if (OFFSET)
  {
    offAX = AcX;
    offAY = AcY;
    offAZ = AcZ;
  }
}

void PitchRollYaw()
{
  //A partir de los valores del acelerometro, se calculan los angulos Y, X
  //respectivamente, con la formula de la tangente.
  Acc[1] = atan(-1 * AcX / sqrt(pow(AcY, 2) + pow(AcZ, 2))) * RAD_TO_DEG;
  Acc[0] = atan(AcY / sqrt(pow(AcX, 2) + pow(AcZ, 2))) * RAD_TO_DEG;

  //Aplicar el Filtro Complementario
  Pitch = 0.98 * (Pitch + GyX * dt) + 0.02 * Acc[0];
  Roll = 0.98 * (Roll + GyY * dt) + 0.02 * Acc[1];
  //Integración respecto del tiempo paras calcular el YAW
  Yaw = Yaw + GyZ * dt;

  Roll = confANG(Roll);
  Pitch = confANG(Pitch);
  Yaw = confANG(Yaw);
}

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

void corrigirANGULO()
{
  /*  aux = aux + 1;
    if (aux == 50)
    {
      Yaw = Yaw - 1.266;
    }
    if (aux == 100)
    {
      Roll = Roll - -0.0064;
      Pitch = Pitch - -0.0088;
      Yaw = Yaw - 1.266;
      aux = 0;
    }
  */
  Roll = Roll - (-0.03 / 2764);
  Pitch = Pitch - (-0.06 / 2764);
  Yaw = Yaw - (70.87 / 2764);
}

void velocidade()
{
  if (!OFFSET)
  {
    VelX = VelX + (AcX - offAX) * dt;
    VelY = VelY + (AcY - offAY) * dt;
    VelZ = VelZ + (AcZ - offAZ) * dt;
  }
}
