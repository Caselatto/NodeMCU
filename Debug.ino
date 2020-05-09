void mostraRAW()
{
  Serial.print(tempo_prev);
  Serial.print("\tTmp = "); Serial.print(Tp);
  Serial.print("\tAcX = "); Serial.print(AX);
  Serial.print("\tAcY = "); Serial.print(AY);
  Serial.print("\tAcZ = "); Serial.print(AZ);
  Serial.print("\tGyX = "); Serial.print(GX);
  Serial.print("\tGyY = "); Serial.print(GY);
  Serial.print("\tGyZ = "); Serial.print(GZ);
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
  Serial.print("180, " + String(Roll) + "," + String(Pitch) + "," + String(Yaw) + ", -180");
}
