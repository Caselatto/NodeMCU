void offset()
{
  if (OFFSET)
  {
    offAX = AmX;
    offAY = AmY;
    offAZ = AmZ;
  }
}

void converterRAW()
{
  AcX = (double(AX) / convACEL);
  AcY = (double(AY) / convACEL);
  AcZ = (double(AZ) / convACEL);
  Tmp = (double(Tp) + 12412.0) / 340.0;
  GyX = double(GX) / convGYRO;
  GyY = double(GY) / convGYRO;
  GyZ = double(GZ) / convGYRO;
}

double media_movel(double entrada)
{
  int i;
  //desloca os elementos do vetor de média móvel
  for (i = (n - 1); i > 0 ; i = i - 1)
  {
    numbers[i] = numbers[i - 1];
  }
  numbers[0] = entrada; //posição inicial do vetor recebe a leitura original
  double acc = 0;          //acumulador para somar os pontos da média móvel
  for (int i = 0; i < n; i++)
  {
    acc += numbers[i]; //faz a somatória do número de pontos
  }
  acc = acc / n;
  return (acc); //retorna a média móvel
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
  }
}
