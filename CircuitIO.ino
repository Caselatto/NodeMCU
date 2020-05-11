void Setup_CircuitIO()
{
  Wire.begin();
  mpu6050.initialize();
  convGYRO = 131.00;
  convACEL  = 1638.40;
}


void readRawMPU_CircuitIO()
{
  mpu6050.getMotion6(&AX, &AY, &AZ, &GX, &GY, &GZ);   //read accelerometer and gyroscope raw data in three axes
  Tp = (double)mpu6050.getTemperature();
}
