void mostraRAW()
{
  //  Serial.print(tempo_prev);
  //  Serial.print("\tTp = "); Serial.print(Tp);
  //  Serial.print("\tAX = "); Serial.print(AX);
  //  Serial.print("\tAY = "); Serial.print(AY);
  //  Serial.print("\tAZ = "); Serial.print(AZ);
  //  Serial.print("\tGX = "); Serial.print(GX);
  //  Serial.print("\tGY = "); Serial.print(GY);
  //  Serial.print("\tGZ = "); Serial.print(GZ);
}

void mostraOFF()
{
  Serial.print("\toffAX = "); Serial.print(offAX);
  Serial.print("\toffAY = "); Serial.print(offAY);
  Serial.print("\toffAZ = "); Serial.print(offAZ);
}

void mostraCON()
{
  //  Serial.print(tempo_prev);
  //  Serial.print("\tTmp = "); Serial.print(Tmp);
  Serial.print("\tAcX = "); Serial.print(AcX);
  Serial.print("\tAcY = "); Serial.print(AcY);
  Serial.print("\tAcZ = "); Serial.print(AcZ);
  //  Serial.print("\tGyX = "); Serial.print(GyX);
  //  Serial.print("\tGyY = "); Serial.print(GyY);
  //  Serial.print("\tGyZ = "); Serial.print(GyZ);
}

void mostraMED()
{
  Serial.print("\tAmX = "); Serial.print(AmX);
  Serial.print("\tAmY = "); Serial.print(AmY);
  Serial.print("\tAmZ = "); Serial.print(AmZ);
  //  Serial.print("\tGmX = "); Serial.print(GmX);
  //  Serial.print("\tGmY = "); Serial.print(GmY);
  //  Serial.print("\tGmZ = "); Serial.print(GmZ);
}

void mostraANG()
{
  Serial.print("\t");
  Serial.print(180);
  Serial.print(",");
  Serial.print(Roll);
  Serial.print(",");
  Serial.print(Pitch);
  Serial.print(",");
  Serial.print(Yaw);
  Serial.print(",");
  Serial.print(-180);
}

void mostraVEL()
{
  Serial.print("\tVelX = "); Serial.print(VelX,5);
  Serial.print("\tVelY = "); Serial.print(VelY,5);
  Serial.print("\tVelZ = "); Serial.print(VelZ,5);
}
