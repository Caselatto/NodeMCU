double mediaAx[n];

double media_movelaX(double entrada)
{
  //  Serial.print(entrada);
  //  Serial.print("\t");
  int i;
  //desloca os elementos do vetor de média móvel
  for (i = n - 1; i > 0 ; i--)
  {
    mediaAx[i] = mediaAx[i - 1];
    //    Serial.print(mediaAx[i]);
    //    Serial.print(",");
  }
  mediaAx[0] = entrada; //posição inicial do vetor recebe a leitura original
  //  Serial.print(mediaAx[0]);
  //  Serial.print("\t");
  double acc = 0;          //acumulador para somar os pontos da média móvel
  for (int i = 0; i < n; i++)
  {
    acc += mediaAx[i]; //faz a somatória do número de pontos
  }
  acc = acc / n;
  return (acc); //retorna a média móvel
}

double mediaAy[n];

double media_movelaY(double entrada)
{
  //  Serial.print(entrada);
  //  Serial.print("\t");
  int i;
  //desloca os elementos do vetor de média móvel
  for (i = n - 1; i > 0 ; i--)
  {
    mediaAy[i] = mediaAy[i - 1];
    //    Serial.print(mediaAy[i]);
    //    Serial.print(",");
  }
  mediaAy[0] = entrada; //posição inicial do vetor recebe a leitura original
  //  Serial.print(mediaAy[0]);
  //  Serial.print("\t");
  double acc = 0;          //acumulador para somar os pontos da média móvel
  for (int i = 0; i < n; i++)
  {
    acc += mediaAy[i]; //faz a somatória do número de pontos
  }
  acc = acc / n;
  return (acc); //retorna a média móvel
}

double mediaAz[n];

double media_movelaZ(double entrada)
{
  //  Serial.print(entrada);
  //  Serial.print("\t");
  int i;
  //desloca os elementos do vetor de média móvel
  for (i = n - 1; i > 0 ; i--)
  {
    mediaAz[i] = mediaAz[i - 1];
    //    Serial.print(mediaAz[i]);
    //    Serial.print(",");
  }
  mediaAz[0] = entrada; //posição inicial do vetor recebe a leitura original
  //  Serial.print(mediaAz[0]);
  //  Serial.print("\t");
  double acc = 0;          //acumulador para somar os pontos da média móvel
  for (int i = 0; i < n; i++)
  {
    acc += mediaAz[i]; //faz a somatória do número de pontos
  }
  acc = acc / n;
  return (acc); //retorna a média móvel
}
