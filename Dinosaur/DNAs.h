

float* DNADaVez[POPULACAO_TAMANHO];

float MediaFitnessPopulacao[LARG_GRAFICO];
float MediaFitnessFilhos[LARG_GRAFICO];
float BestFitnessPopulacao[LARG_GRAFICO];

int GeracaoCompleta = 0;


//#########################################################################//


float BestFitnessGeracao() {

	float Maior = 0;
	for (int i = 0; i < POPULACAO_TAMANHO; i++) {

		if (Dinossauros[i].Fitness > Maior) {
			Maior = Dinossauros[i].Fitness;
		}

	}
	return Maior;
}

float MediaFitnessGeracao() {

	float Media = 0;
	for (int i = 0; i < POPULACAO_TAMANHO; i++) {

		Media = Media + Dinossauros[i].Fitness;
	}

	Media = Media / (float)POPULACAO_TAMANHO;
	return Media;
}

float BestFitnessEver() {

	float Maior = 0;

	for (int i = 0; i < GeracaoCompleta; i++) {

		if (BestFitnessPopulacao[i] > Maior) {

			Maior = BestFitnessPopulacao[i];

		}
	}

	return Maior;
}


void InicializarDNA() {

	int TamanhoDNA = Dinossauros[0].TamanhoDNA;

	for (int i = 0; i < POPULACAO_TAMANHO; i++) {

		DNADaVez[i] = (float*)malloc(TamanhoDNA * sizeof(float));

		for (int j = 0; j < TamanhoDNA; j++) {
			DNADaVez[i][j] = getRandomValue();
		}
	}
}