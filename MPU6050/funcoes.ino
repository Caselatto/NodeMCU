void offset()
{
  //  Serial.println();
  //  Serial.println("Botão offset pressionado");
  //  Serial.println();
  OFFSET = true;
}

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

void PitchRollYaw(double aX, double aY, double aZ, double gX, double gY, double gZ)
{
  //A partir de los valores del acelerometro, se calculan los angulos Y, X
  //respectivamente, con la formula de la tangente.
  Acc[1] = atan(-1 * aX / sqrt(pow(aY, 2) + pow(aZ, 2))) * RAD_TO_DEG;
  Acc[0] = atan(aY / sqrt(pow(aX, 2) + pow(aZ, 2))) * RAD_TO_DEG;

  //Aplicar el Filtro Complementario
  Pitch = 0.98 * (Pitch + gX * dt) + 0.02 * Acc[0];
  Roll = 0.98 * (Roll + gY * dt) + 0.02 * Acc[1];
  //Integración respecto del tiempo paras calcular el YAW
  Yaw = Yaw + gZ * dt;

  Roll = confANG(Roll) - offRoll;
  Pitch = confANG(Pitch) - offPitch;
  Yaw = confANG(Yaw) - offYaw;
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
  Roll = Roll - (-0.03 / 2764);
  Pitch = Pitch - (-0.06 / 2764);
  Yaw = Yaw - (70.87 / 2764);
}

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
