#include "Arduino.h"  //  
#include "Wire.h"     //  Biblioteca de comunicação I2C 
#include "SD.h"       //  Biblioteca do Cartão SD

/*
  ================================================================
  ===                        DEFINIÇÕES                        ===
  ================================================================
*/

File sdFile;

/*
  ===============================================================
  ===                        VARIÁVEIS                        ===
  ===============================================================
*/

// Tempo
double dt, tempo_prev = 0.00;

// Armazenamento dos dados "crus" do acelerômetro
int16_t AX, AY, AZ, Tp, GX, GY, GZ;

// Variavel do offset
bool OFFSET = false;
double offAX = 0, offAY = 0, offAZ = 0, offRoll = 0, offPitch = 0, offYaw = 0;
uint8_t botOffset = D4;

// Armazenamento dos dados após conversão
double AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
long convGYRO, convACEL;     // Datasheet do sensor

// Calculo ângulos
double Pitch = 0;
double Roll = 0;
double Yaw = 0;
double Acc[2];
#define RAD_TO_DEG 57.295779  // Radianos para graus (180/PI)

// Calculo velocidade
double VelX = 0, VelY = 0, VelZ = 0;

// Media movel
double AmX = 0, AmY = 0, AmZ = 0;
#define n 30

// Leds piscando alternado a cada ciclo do loop
#define LED1 D8
#define LED2 D7
bool led_state = false;

/*
  ===============================================================
  ===                      SETUP INICIAL                      ===
  ===============================================================
*/

void setup()
{
  Serial.begin(9600);
  Setup_MPU();
  Setup_Cartao();
}

/*
  ================================================================
  ===                       MAIN PROGRAM                       ===
  ================================================================
*/

void loop ()
{

}
