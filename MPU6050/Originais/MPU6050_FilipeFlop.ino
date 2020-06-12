//Programa: Acelerometro com ESP8266 NodeMCU
#include <Wire.h>         // biblioteca de comunicação I2C
float pi = 3.14159265359;
float roll = 0;
float pitch = 0;
float yaw = 0;
int velX, velY, velZ;
float convGYRO, convACEL;
float AX, AY, AZ, GX, GY, GZ, tA, t;

/*
   Definições de alguns endereços mais comuns do MPU6050
   os registros podem ser facilmente encontrados no mapa de registros do MPU6050
*/
const int MPU_ADDR =      0x68; // definição do endereço do sensor MPU6050 (0x68)
const int WHO_AM_I =      0x75; // registro de identificação do dispositivo
const int PWR_MGMT_1 =    0x6B; // registro de configuração do gerenciamento de energia
const int GYRO_CONFIG =   0x1B; // registro de configuração do giroscópio
const int ACCEL_CONFIG =  0x1C; // registro de configuração do acelerômetro
const int ACCEL_XOUT =    0x3B; // registro de leitura do eixo X do acelerômetro

const int sda_pin = D6; // definição do pino I2C SDA
const int scl_pin = D5; // definição do pino I2C SCL

#define LED 2
bool led_state = false;

// variáveis para armazenar os dados "crus" do acelerômetro
short AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

/*
   função que configura a I2C com os pinos desejados
   sda_pin -> D5
   scl_pin -> D6
*/
void initI2C()
{
  //Serial.println("---inside initI2C");
  Wire.begin(sda_pin, scl_pin);
}

/*
   função que escreve um dado valor em um dado registro
*/
void writeRegMPU(int reg, int val)      //aceita um registro e um valor como parâmetro
{
  Wire.beginTransmission(MPU_ADDR);     // inicia comunicação com endereço do MPU6050
  Wire.write(reg);                      // envia o registro com o qual se deseja trabalhar
  Wire.write(val);                      // escreve o valor no registro
  Wire.endTransmission(true);           // termina a transmissão
}

/*
   função que lê de um dado registro
*/
uint8_t readRegMPU(uint8_t reg)        // aceita um registro como parâmetro
{
  uint8_t data;
  Wire.beginTransmission(MPU_ADDR);     // inicia comunicação com endereço do MPU6050
  Wire.write(reg);                      // envia o registro com o qual se deseja trabalhar
  Wire.endTransmission(false);          // termina transmissão mas continua com I2C aberto (envia STOP e START)
  Wire.requestFrom(MPU_ADDR, 1);        // configura para receber 1 byte do registro escolhido acima
  data = Wire.read();                   // lê o byte e guarda em 'data'
  return data;                          //retorna 'data'
}

/*
   função que procura pelo sensor no endereço 0x68
*/
void findMPU(int mpu_addr)
{
  Wire.beginTransmission(MPU_ADDR);
  int data = Wire.endTransmission(true);

  if (data == 0)
  {
    Serial.print("Dispositivo encontrado no endereço: 0x");
    Serial.println(MPU_ADDR, HEX);
  }
  else
  {
    Serial.println("Dispositivo não encontrado!");
  }
}

/*
   função que verifica se o sensor responde e se está ativo
*/
void checkMPU(int mpu_addr)
{
  findMPU(MPU_ADDR);

  int data = readRegMPU(WHO_AM_I); // Register 117 – Who Am I - 0x75

  if (data == 104)
  {
    Serial.println("MPU6050 Dispositivo respondeu OK! (104)");

    data = readRegMPU(PWR_MGMT_1); // Register 107 – Power Management 1-0x6B

    if (data == 64) Serial.println("MPU6050 em modo SLEEP! (64)");
    else Serial.println("MPU6050 em modo ACTIVE!");
  }
  else Serial.println("Verifique dispositivo - MPU6050 NÃO disponível!");
}

/*
   função de inicialização do sensor
*/
void initMPU()
{
  setSleepOff();
  setGyroScale();
  setAccelScale();
}

/*
    função para configurar o sleep bit
*/
void setSleepOff()
{
  writeRegMPU(PWR_MGMT_1, 0); // escreve 0 no registro de gerenciamento de energia(0x68), colocando o sensor em o modo ACTIVE
}

/* função para configurar as escalas do giroscópio
   registro da escala do giroscópio: 0x1B[4:3]
   0 é 250°/s

    FS_SEL  Full Scale Range                  Conversão
      0        ± 250 °/s      0b00000000      131
      1        ± 500 °/s      0b00001000      65.5
      2        ± 1000 °/s     0b00010000      32.8
      3        ± 2000 °/s     0b00011000      16.4
*/
void setGyroScale()
{
  writeRegMPU(GYRO_CONFIG, 0);
  convGYRO = 131;
}

/* função para configurar as escalas do acelerômetro
   registro da escala do acelerômetro: 0x1C[4:3]
   0 é 250°/s

    AFS_SEL   Full Scale Range                    Conversão
      0           ± 2g            0b00000000      1638.4      ok
      1           ± 4g            0b00001000      8192        ??
      2           ± 8g            0b00010000      4096        ??
      3           ± 16g           0b00011000      2048        ??
*/
void setAccelScale()
{
  writeRegMPU(ACCEL_CONFIG, 0);
  convACEL  = 1638.4;
}

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

  Wire.beginTransmission(MPU_ADDR);       // inicia comunicação com endereço do MPU6050
  Wire.write(ACCEL_XOUT);                       // envia o registro com o qual se deseja trabalhar, começando com registro 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);            // termina transmissão mas continua com I2C aberto (envia STOP e START)
  Wire.requestFrom(MPU_ADDR, 14);         // configura para receber 14 bytes começando do registro escolhido acima (0x3B)

  AcX = Wire.read() << 8;                 // lê primeiro o byte mais significativo
  AcX |= Wire.read();                     // depois lê o bit menos significativo
  AcY = Wire.read() << 8;
  AcY |= Wire.read();
  AcZ = Wire.read() << 8;
  AcZ |= Wire.read();

  Tmp = Wire.read() << 8;
  Tmp |= Wire.read();

  GyX = Wire.read() << 8;
  GyX |= Wire.read();
  GyY = Wire.read() << 8;
  GyY |= Wire.read();
  GyZ = Wire.read() << 8;
  GyZ |= Wire.read();
  
  AX = AcX/convACEL;
  AY = AcY/convACEL;
  AZ = AcZ/convACEL;
  GyX = GyX/convGYRO;
  GyY = GyY/convGYRO;
  GyZ = GyZ/convGYRO;
  GX = 2*pi*(GyX/60);
  GY = 2*pi*(GyY/60);
  GZ = 2*pi*(GyZ/60);
  tA = t;
  t = millis()/1000.000;
  pitch = GX*(t-tA)*(180/PI)+pitch;
  roll  = GY*(t-tA)*(180/PI)+roll;
  yaw   = ((GyZ*6.000)*(t-tA))+yaw;

  pitch = 180.000 * atan (AcX/sqrt(AcY*AcY + AcZ*AcZ))/pi;

  Serial.print(t);
  /*
  Serial.print("\tTmp = "); Serial.print(Tmp / 340.00 + 36.53);
  Serial.print("\tAcX = "); Serial.print(AX);
  Serial.print("\tAcY = "); Serial.print(AY);
  Serial.print("\tAcZ = "); Serial.print(AZ);
  Serial.print("\tGyX = "); Serial.print(GX);
  Serial.print("\tGyY = "); Serial.print(GY);
  */
  Serial.print("\t\tGyZ = "); Serial.print(GyZ);
  Serial.print("\t\tGZ = "); Serial.print(GZ);
  /*
  Serial.print("\tP = "); Serial.print(pitch);
  Serial.print("\tR = "); Serial.print(roll);
  */
  Serial.print("\t\tY = "); Serial.print(pitch);
  
  /*
  pitch = 180 * atan (AcX/sqrt(AcY*AcY + AcZ*AcZ))/3.14159265358979323846;
  roll  = 180 * atan (AcY/sqrt(AcX*AcX + AcZ*AcZ))/3.14159265358979323846;
  yaw   = 180 * atan (AcZ/sqrt(AcX*AcX + AcZ*AcZ))/3.14159265358979323846;
  Serial.print("Pitch = "); Serial.print(pitch);
  Serial.print("\tRoll = "); Serial.print(roll);
  Serial.print("\tYaw = "); Serial.print(yaw);
  */
  velX = AX*(t-tA);
  velY = AY*(t-tA);
  velZ = AZ*(t-tA);
  /*
  Serial.print("\tt = "); Serial.print(t);
  Serial.print("\ttA = "); Serial.print(tA);
  Serial.print("\tvelX = "); Serial.print(velX);
  Serial.print("\tvelY = "); Serial.print(velY);
  Serial.print("\tvelZ = "); Serial.print(velZ);
  */
  led_state = !led_state;
  digitalWrite(LED, led_state);         // pisca LED do NodeMCU a cada leitura do sensor
  delay(100);
  Serial.println();
}
