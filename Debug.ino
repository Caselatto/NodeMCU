void mostraRAW()
{
  Serial.print(tempo_prev);
  Serial.print("\tTp = "); Serial.print(Tp);
  Serial.print("\tAX = "); Serial.print(AX);
  Serial.print("\tAY = "); Serial.print(AY);
  Serial.print("\tAZ = "); Serial.print(AZ);
  Serial.print("\tGX = "); Serial.print(GX);
  Serial.print("\tGY = "); Serial.print(GY);
  Serial.print("\tGZ = "); Serial.print(GZ);
}

void mostraCON()
{
  Serial.print(tempo_prev);
  Serial.print("\tTmp = "); Serial.print(Tmp);
  Serial.print("\tAcX = "); Serial.print(AcX);
  Serial.print("\tAcY = "); Serial.print(AcY);
  Serial.print("\tAcZ = "); Serial.print(AcZ);
  Serial.print("\tGyX = "); Serial.print(GyX);
  Serial.print("\tGyY = "); Serial.print(GyY);
  Serial.print("\tGyZ = "); Serial.print(GyZ);
}

void mostraANG()
{
  Serial.print("\t180, " + String(Roll) + "," + String(Pitch) + "," + String(Yaw) + ", -180");
}
