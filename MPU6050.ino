
#include "Arduino.h"  //  
#include "MPU6050.h"  //  
#include "Wire.h"     //  Biblioteca de comunicação I2C
#include "I2Cdev.h"   //  

// Armazenamento dos dados "crus" do acelerômetro
int16_t AX, AY, AZ, Tp, GX, GY, GZ;

// Geral
double VelX = 0, VelY = 0, VelZ = 0;
double AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
double tempo_prev;
double dt;

// Media movel
#define n 10
double AmX, AmY, AmZ, GmX, GmY, GmZ;
double numbers[n];

// Variavel do offset
bool OFFSET = true;
double offAX, offAY, offAZ;

// Calculo ângulos
double Acc[2];
double Pitch = 0;
double Roll = 0;
double Yaw = 0;

//Conversão de unidades
#define RAD_TO_DEG 57.295779  // Radianos para graus (180/PI)
long convGYRO, convACEL;     // Datasheet do sensor

#define LED D8
bool led_state = false;

// object initialization
MPU6050 mpu6050;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);

  //  Setup_CircuitIO();
  Setup_FilipeFlop();
}

void loop() {
  dt = (millis() - tempo_prev) / 1000.0;
  tempo_prev = millis();

  // lê os dados do sensor
  //  readRawMPU_CircuitIO();
  readRawMPU_FilipeFlop();

  // Converte os dados do sensor
  converterRAW();

  // Faz a média do valor após conversão
  AmX = media_movel(AcX);
  AmY = media_movel(AcY);
  AmZ = media_movel(AcZ);
  //  GmX = media_movel(GyX);
  //  GmY = media_movel(GyY);
  //  GmZ = media_movel(GyZ);

  //Offset
  offset();

  // Calcula os ângulos em função dos eixos do sensor
  PitchRollYaw(AcX, AcY, AcZ, GyX, GyY, GyZ);

  //Corrige erro no valor dos angulos
  corrigirANGULO();

  //Calculo da velocidade
  velocidade(AmX, AmY, AmZ);

  //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //Mostra os valores
  //  mostraRAW();
  mostraOFF();
  //  mostraCON();
  mostraMED();
  //  mostraANG();
  //  mostraVEL();
  //  Serial.print("\t" + String(dt));
  //  Serial.print(OFFSET);
  //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  if (OFFSET)
  {
    OFFSET = !OFFSET;
  }
  led_state = !led_state;
  digitalWrite(LED, led_state);         // pisca LED do NodeMCU a cada leitura do sensor
  Serial.println();
}
