void converter()
{
  AcX = AX / convACEL;
  AcY = AY / convACEL;
  AcZ = AZ / convACEL;
  Tmp = (Tp + 12412.0) / 340.0;
  GyX = GX / convGYRO;
  GyY = GY / convGYRO;
  GyZ = GZ / convGYRO;
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

  espera = 1;
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
