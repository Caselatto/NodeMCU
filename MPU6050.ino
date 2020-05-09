
#include "Arduino.h"  //  
#include "MPU6050.h"  //  
#include "Wire.h"     //  Biblioteca de comunicação I2C
#include "I2Cdev.h"   //  

float convGYRO, convACEL;
float AcX = 0, AcY = 0, AcZ = 0, Tmp = 0, GyX = 0, GyY = 0, GyZ = 0;
long tempo_prev;
float dt;
int espera = 100;

float Acc[2];
float Pitch = 0;
float Roll = 0;
float Yaw = 0;

//Conversão de radianos para graus (180/PI)
#define RAD_TO_DEG 57.295779

// variáveis para armazenar os dados "crus" do acelerômetro
int16_t AX, AY, AZ, Tp, GX, GY, GZ;

#define LED 2
bool led_state = false;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);

  //  Setup_FilipeFlop();
  Setup_CircuitIO();
}

void loop() {
  dt = (millis() - tempo_prev) / 1000.0;
  tempo_prev = millis();
  // lê os dados do sensor
  readRawMPU_CircuitIO();
  //  readRawMPU_FilipeFlop();

  // Converte os dados do sensor
  converter();

  // Calcula os ângulos em função dos eixos do sensor
  PitchRollYaw();

  //Mostra os valores
  //mostraRAW();
  //mostraCON();
  mostraANG();

  led_state = !led_state;
  digitalWrite(LED, led_state);         // pisca LED do NodeMCU a cada leitura do sensor
  delay(espera);
  Serial.println();
}
