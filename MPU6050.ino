#include <Wire.h>         // biblioteca de comunicação I2C

float convGYRO, convACEL;
float AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
long tempo_prev;
float dt;
#define PitchRollYaw
int espera = 100;

#ifdef PitchRollYaw
//Conversion de radiano para graus (180/PI)
#define RAD_TO_DEG 57.295779
float Acc[2];
float Pitch = 0;
float Roll = 0;
float Yaw = 0;
int i = 0;
#endif

const int scl_pin = D6; // definição do pino I2C SCL
const int sda_pin = D5; // definição do pino I2C SDA

/*
   Definições de alguns endereços mais comuns do MPU6050
   os registros podem ser facilmente encontrados no mapa de registros do MPU6050
*/
const int MPU_ADDR      = 0x68; // definição do endereço do sensor MPU6050 (0x68)
const int WHO_AM_I      = 0x75; // registro de identificação do dispositivo
const int PWR_MGMT_1    = 0x6B; // registro de configuração do gerenciamento de energia
const int GYRO_CONFIG   = 0x1B; // registro de configuração do giroscópio
const int ACCEL_CONFIG  = 0x1C; // registro de configuração do acelerômetro
const int ACCEL_XOUT    = 0x3B; // registro de leitura do eixo X do acelerômetro

#define LED 2
bool led_state = false;

// variáveis para armazenar os dados "crus" do acelerômetro
int16_t AX, AY, AZ, Tp, GX, GY, GZ;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);

  Serial.println("nIniciando configuração do MPU6050n");
  initI2C();
  initMPU();
  checkMPU(MPU_ADDR);

  Serial.println("nConfiguração finalizada, iniciando loopn");
}

void loop() {
  dt = (millis() - tempo_prev) / 1000.0;
  tempo_prev = millis();
  readRawMPU();    // lê os dados do sensor
  converter();

#ifdef PitchRollYaw
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

  //Mostrar los valores por consola
  Serial.print("180, " + String(Roll) + "," + String(Pitch) + "," + String(Yaw) + ", -180");
  espera = 1;
#endif
  /*
    Serial.print(t);
    Serial.print("\tTmp = "); Serial.print(Tmp);
    Serial.print("\tAcX = "); Serial.print(AcX);
    Serial.print("\tAcY = "); Serial.print(AcY);
    Serial.print("\tAcZ = "); Serial.print(AcZ);
    Serial.print("\tGyX = "); Serial.print(GyX);
    Serial.print("\tGyY = "); Serial.print(GyY);
    Serial.print("\tGyZ = "); Serial.print(GyZ);
  */
  led_state = !led_state;
  digitalWrite(LED_BUILTIN, led_state);         // pisca LED do NodeMCU a cada leitura do sensor
  delay(espera);
  Serial.println();
}
