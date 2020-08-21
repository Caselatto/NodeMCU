
void salva(char nome[9], double valor)
{
  Serial.print(nome);
  Serial.print("\t");
  Serial.print(valor, 3);
  Serial.print("\t");
  char MQTT[20] = "MQTT/";
  strcat(MQTT, nome);
  char msg[MSG_BUFFER_SIZE] = "X";
  sprintf(msg, "%10.5f", valor);
  client.publish(MQTT, msg);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void finaliza()
{
  led_state = !led_state;
  digitalWrite(BUILTIN_LED, led_state);
  if (OFFSET)
  {
    offAX = AmX;
    offAY = AmY;
    offAZ = AmZ;

    VelX = 0;
    VelY = 0;
    VelZ = 0;

    OFFSET = !OFFSET;
  }
#ifdef CARTAO
  sdFile.println();
  sdFile.flush();
#endif
  Serial.println();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void offset()
{
  //  Serial.println();
  //  Serial.println("Botão offset pressionado");
  //  Serial.println();
  OFFSET = true;
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

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void PitchRollYaw(double aX, double aY, double aZ, double gX, double gY, double gZ)
{
  //A partir de los valores del acelerometro, se calculan los angulos Y, X
  //respectivamente, con la formula de la tangente.
  Acc2 = atan(-1 * aX / sqrt(pow(aY, 2) + pow(aZ, 2))) * RAD_TO_DEG;
  Acc1 = atan(aY / sqrt(pow(aX, 2) + pow(aZ, 2))) * RAD_TO_DEG;

  //Aplicar el Filtro Complementario
  Pitch = 0.98 * (Pitch + gX * dt) + 0.02 * Acc1;
  Roll = 0.98 * (Roll + gY * dt) + 0.02 * Acc2;
  //Integración respecto del tiempo paras calcular el YAW
  Yaw = Yaw + gZ * dt;
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
  Roll  = confANG(Roll);
  Pitch = confANG(Pitch);
  Yaw   = confANG(Yaw   - erroYAW * tempo_prev);
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

    //    VelX = VelX * 3.6 ;
    //    VelY = VelY * 3.6;
    //    VelZ = VelZ * 3.6;
  }
}
