#define CS_PIN  D8              // Pino ligado ao CS do módulo SD Card
char filename[7] = "00.TXT";    // Nome do arquivo inicial
int i = 0;

void Setup_Cartao()
{
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
}

void mostra (float valor)
{
  if (sdFile)
  {
    Serial.print(valor);
    Serial.print("\t");
    sdFile.print(valor);
    sdFile.print(",");
  }
  else
  {
    Serial.println("Falha ao abrir o cartão");
  }
}
