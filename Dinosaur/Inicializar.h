
void InicializarDinossauro(int Indice, float* DNA, float X, float Y) {

	Dinossauros[Indice].Estado = 0;
	Dinossauros[Indice].X = X;
	Dinossauros[Indice].Y = Y;
	Dinossauros[Indice].Frame = 0;
	Dinossauros[Indice].SpriteAtual = 0;
	Dinossauros[Indice].FrameAviao = 0;
	if (Dinossauros[Indice].ResetarFitness == 1) {
		Dinossauros[Indice].Fitness = 0;
	} else {
		Dinossauros[Indice].Estado = 3;
		DinossaurosMortos++;
	}

	if (DNA == NULL) {    /// Inicializa aleatoriamente

		for (int i = 0; i < Dinossauros[Indice].TamanhoDNA; i++) {
			Dinossauros[Indice].DNA[i] = getRandomValue();
		}

	} 
	else {                /// Inicializa com o DNA passado pelo parametro

		for (int i = 0; i < Dinossauros[Indice].TamanhoDNA; i++) {
			Dinossauros[Indice].DNA[i] = DNA[i];
		}

	}

	RNA_CopiarVetorParaCamadas(Dinossauros[Indice].Cerebro, Dinossauros[Indice].DNA);

	Dinossauros[Indice].AviaoCooldown = 0;
	Dinossauros[Indice].AviaoDeslocamento = 0;
}


void InicializarObstaculos() {

	ObstaculoDaVez = 0;

	for (int i = 0; i < MAX_OBSTACULOS; i++) {

		getNextObstaculo(&obstaculo[i], ObstaculoDaVez);

	}
}