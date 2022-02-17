void mostraRAW()
{
  salva("AX", AX);
  salva("AY", AY);
  salva("AZ", AZ);
  salva("GX", GX);
  salva("GY", GY);
  salva("GZ", GZ);
}

void mostraOFF()
{
  //  Serial.print("\toffAX = "); Serial.print(offAX);
  //  Serial.print("\toffAY = "); Serial.print(offAY);
  //  Serial.print("\toffAZ = "); Serial.print(offAZ);
  //  Serial.print("\toffGX = "); Serial.print(offGX);
  //  Serial.print("\toffGY = "); Serial.print(offGY);
  //  Serial.print("\toffGZ = "); Serial.print(offGZ);
  Serial.print("\toffRol = "); Serial.print(offRoll);
  Serial.print("\toffPit = "); Serial.print(offPitch);
  Serial.print("\toffYaw = "); Serial.print(offYaw);
}

void mostraCON()
{
  //  salva("AcX", AcX - offAX);
  //  salva("AcY", AcY - offAY);
  //  salva("AcZ", AcZ - offAZ);

  salva("AcX", AcX);
  salva("AcY", AcY);
  salva("AcZ", AcZ);

  //  salva("GyX", GyX - offGX);
  //  salva("GyY", GyY - offGY);
  //  salva("GyZ", GyZ - offGZ);

  salva("GyX", GyX);
  salva("GyY", GyY);
  salva("GyZ", GyZ);
}

void mostraMED()
{
  Serial.print("\tAmX = "); Serial.print(AmX);
  Serial.print("\tAmY = "); Serial.print(AmY);
  Serial.print("\tAmZ = "); Serial.print(AmZ);
}

void mostraANG()
{
  salva("Roll", Roll);    //- erroROLL);
  salva("Pitch", Pitch);  // - erroPITCH);
  salva("Yaw", Yaw);
}

void mostraVEL()
{
  salva("VelX", VelX);
  salva("VelY", VelY);
  salva("VelZ", VelZ);
}
