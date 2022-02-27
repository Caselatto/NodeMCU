#ifdef CARTAO

char filename[9] = "00.csv";    // Nome do arquivo inicial
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
      sprintf(filename, "0%d.csv", i);
    }
    else
    {
      sprintf(filename, "%2d.csv", i);
    }
    i++;
  }
  sdFile = SD.open(filename, FILE_WRITE);
  Serial.print("Arquivo: ");
  Serial.println(filename);
  Serial.println("SD ok");
}

#endif

void salva(char nome[9], double valor)
{
  Serial.print(nome);
  Serial.print("\t");
  Serial.print(valor, 3);
  Serial.print("\t");
#ifdef CARTAO
  //  sdFile.print(nome);
  //  sdFile.print(";\t");
  sdFile.print(valor, 2);
  sdFile.print(";\t");
#endif
}
