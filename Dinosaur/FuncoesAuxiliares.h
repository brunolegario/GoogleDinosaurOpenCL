
float getRandomValue() {
	return (rand() % 20001 / 10.0) - 1000.0;
}


void SalvarRedeArquivo() {

	float Maior = 0;
	int Indice = 0;

	for (int i = 0; i < POPULACAO_TAMANHO; i++) {

		if (Dinossauros[i].Fitness > Maior) {
			Maior = Dinossauros[i].Fitness;
			Indice = i;
		}

	}

	char String[1000];
	sprintf(String, "redes\\%.2f - [%d,%d,%d,%d]",
			DistanciaRecorde,
			DINO_BRAIN_QTD_LAYERS,
			DINO_BRAIN_QTD_INPUT,
			DINO_BRAIN_QTD_HIDE,
			DINO_BRAIN_QTD_OUTPUT);


	errno = 0;
	FILE* f = fopen(String, "wb+");
	if (f == NULL) {
		printf("Error %d \n", errno);
		printf("It's null");
	}
	fwrite(&Dinossauros[Indice].TamanhoDNA, 1, sizeof(int), f);
	fwrite(Dinossauros[Indice].DNA, Dinossauros[Indice].TamanhoDNA, sizeof(float), f);
	fclose(f);

}


void getNextObstaculo(Obstaculo* obs, int Indice) {

	obs->X = obstaculosModelo[Indice].X;
	obs->Y = obstaculosModelo[Indice].Y;
	obs->Tipo = obstaculosModelo[Indice].Tipo;

	if (obs->Tipo == PASSARO_CODIGO_TIPO) {

		obs->sprite[0] = getObstaculosSprite(obs->Tipo, 0);
		obs->sprite[1] = getObstaculosSprite(obs->Tipo, 1);

	} else {

		obs->sprite[0] = getObstaculosSprite(obs->Tipo, 0);
		obs->sprite[1] = getObstaculosSprite(obs->Tipo, 0);

	}
	obs->FrameAtual = 0;

	ObstaculoDaVez++;
}

int ProcurarProximoObstaculo(float X) {

	int Indice = 0;
	float Menor = 999999;
	int Largura;

	for (int i = 0; i < MAX_OBSTACULOS; i++) {

		Largura = obstaculo[i].sprite[obstaculo[i].FrameAtual]->Largura;

		if (obstaculo[i].X < Menor && obstaculo[i].X + Largura > X) {
			Menor = obstaculo[i].X;
			Indice = i;
		}

	}

	return Indice;
}