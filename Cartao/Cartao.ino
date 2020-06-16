//biblioteca responsável pela comunicação com o Cartão SD
#include "SD.h"

//PINOUT
/* VCC        VCC
   GND        GND
   MISO       D6
   MOSI       D7
   SCK        D5
*/
#define CS_PIN  D8  //pino ligado ao CS do módulo SD Card


char filename[7] = "00.TXT";    // Nome do arquivo inicial
int i = 0;

float valor;
File sdFile;

void setup()
{
  Serial.begin(9600);

  pinMode(CS_PIN, OUTPUT);   // Inicia cartão SD
  if (!SD.begin(CS_PIN))
  {
    Serial.println(F("SD falhou"));   // Em caso de falha na inicialização
    while (1);
  }
  Serial.println(F("Tudo certo"));    // Inicialização certa

  while (SD.exists(filename))         // Função para gerar arquivo com nome seguinte
  {
    if (i < 10)
    {
      sprintf(filename, "0%d.TXT", i);
    }
    else
    {
      sprintf(filename, "%2d.TXT", i);
    }
    i++;
  }
  sdFile = SD.open(filename, FILE_WRITE);
  Serial.print("Arquivo: ");
  Serial.println(filename);
  Serial.println("SD ok");

  valor = millis();
}

void mostra (char nome[9], float valor)
{
  Serial.print(nome);
  Serial.print("\t");
  Serial.print(valor);
  Serial.print("\t");
  sdFile.print(nome);
  sdFile.print(",");
  sdFile.print(valor);
  sdFile.print(",");
}

void loop ()
{
  valor = millis() - valor;
  //  sdFile = SD.open(filename, FILE_WRITE);
  if (sdFile)
  {
    Serial.println("O arquivo foi aberto com sucesso.");
    mostra("milli", valor);
    valor = valor / 1000;
    mostra("0123456789ABCDEFGHIJ0123456789", valor);
    //    sdFile.println(valor);
    //    sdFile.print(" | ");
    //    sdFile.print(valor / 1000);
    sdFile.println();
    //    sdFile.close();
  }
  else
  {
    Serial.println("Falha ao abrir o cartão");
  }

  sdFile.flush();

  //  delay(500);
}
