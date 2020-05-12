
#include "Arduino.h"  //  
#include "MPU6050.h"  //  
#include "Wire.h"     //  Biblioteca de comunicação I2C
#include "I2Cdev.h"   //  

float convGYRO, convACEL;
float AcX = 0, AcY = 0, AcZ = 0, Tmp = 0, GyX = 0, GyY = 0, GyZ = 0, VelX = 0, VelY = 0, VelZ = 0;
float offAX, offAY, offAZ;
long tempo_prev;
float dt;
int aux = 0;

bool OFFSET = true;

float Acc[2];
float Pitch = 0;
float Roll = 0;
float Yaw = 0;

//Conversão de radianos para graus (180/PI)
#define RAD_TO_DEG 57.295779

// variáveis para armazenar os dados "crus" do acelerômetro
int16_t AX, AY, AZ, Tp, GX, GY, GZ;

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

  // Calcula os ângulos em função dos eixos do sensor
  PitchRollYaw();

  //Corrige erro no valor dos angulos
  corrigirANGULO();

  velocidade();

  //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //Mostra os valores
  //  mostraRAW();
  mostraCON();
  //  mostraANG();
  mostraVEL();
  Serial.print("\t" + String(dt));
  //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  if (OFFSET)
  {
    OFFSET = !OFFSET;
  }
  led_state = !led_state;
  digitalWrite(LED, led_state);         // pisca LED do NodeMCU a cada leitura do sensor
  Serial.println();
}
