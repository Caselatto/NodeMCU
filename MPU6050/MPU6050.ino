#include "Arduino.h"  //  
#include "Wire.h"     //  Biblioteca de comunicação I2C 

// Tempo
double dt, tempo_prev = 0.00;

// Armazenamento dos dados "crus" do acelerômetro
int16_t AX, AY, AZ, Tp, GX, GY, GZ;

// Variavel do offset
bool OFFSET = false;
double offAX = 0, offAY = 0, offAZ = 0, offRoll = 0, offPitch = 0, offYaw = 0;
uint8_t botOffset = D5;

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

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, led_state);
  digitalWrite(LED2, led_state);
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(botOffset), offset, RISING);

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
  AmX = media_movelaX(AcX);
  AmY = media_movelaY(AcY);
  AmZ = media_movelaZ(AcZ);

  //Offset
  //  offset();

  // Calcula os ângulos em função dos eixos do sensor
  //  PitchRollYaw(AcX, AcY, AcZ, GyX, GyY, GyZ);

  //Corrige erro no valor dos angulos
  //  corrigirANGULO();

  //Calculo da velocidade
  velocidade(AmX, AmY, AmZ);

  //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //Mostra os valores
  //  mostraRAW();
  //  mostraOFF();
  //  mostraCON();
  //  mostraMED();
  //  mostraANG();
  mostraVEL();
  //  Serial.print("\t" + String(dt));
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  finaliza();
}
