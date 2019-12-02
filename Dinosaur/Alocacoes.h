
void AlocarDinossauro() {

	int Tamanho;

	for (int i = 0; i < 10; i++) {
		Dinossauros[QuantidadeDinossauros].sprite[i] = getDinossauroSprite(i);
	}

	Dinossauros[QuantidadeDinossauros].ResetarFitness = 1;

	Dinossauros[QuantidadeDinossauros].Cerebro = RNA_CriarRedeNeural(DINO_BRAIN_QTD_LAYERS,
																	 DINO_BRAIN_QTD_INPUT,
																	 DINO_BRAIN_QTD_HIDE,
																	 DINO_BRAIN_QTD_OUTPUT);

	Tamanho = RNA_QuantidadePesos(Dinossauros[QuantidadeDinossauros].Cerebro);
	if (DNATamanho == 0) { DNATamanho = Tamanho; }		// FOR GPU

	Dinossauros[QuantidadeDinossauros].TamanhoDNA = Tamanho;
	Dinossauros[QuantidadeDinossauros].DNA = (float*)malloc(Tamanho * sizeof(float));

	InicializarDinossauro(QuantidadeDinossauros, NULL, 0, 0);

	QuantidadeDinossauros = QuantidadeDinossauros + 1;
}


void AlocarDinossauros() {

	for (int i = 0; i < POPULACAO_TAMANHO; i++) {
		AlocarDinossauro();
	}

}


void AlocarPonteiros() {

	DinoEstados = (int*)malloc(sizeof(int)*POPULACAO_TAMANHO);
	DinoPosicoesX = (float*)malloc(sizeof(float)*POPULACAO_TAMANHO);
	DinoPosicoesY = (float*)malloc(sizeof(float)*POPULACAO_TAMANHO);
	DinoFitness = (float*)malloc(sizeof(float)*POPULACAO_TAMANHO);
	DinoVelocidadeY = (float*)malloc(sizeof(float)*POPULACAO_TAMANHO);
	DinoDeslocamentoAviao = (float*)malloc(sizeof(float)*POPULACAO_TAMANHO);
	DinoCooldownAviao = (float*)malloc(sizeof(float)*POPULACAO_TAMANHO);
	DinoSpriteAtual = (int*)malloc(sizeof(int)*POPULACAO_TAMANHO);

	DinoDNA = (float*)malloc(sizeof(float)*DNATamanho*POPULACAO_TAMANHO);

	DinoLargurasSprites = (int*)malloc(sizeof(int)*DINOSSAUROS_SPRITE_QUANTIDADE);
	DinoAlturasSprites = (int*)malloc(sizeof(int)*DINOSSAUROS_SPRITE_QUANTIDADE);
	int LarguraFramesDino[DINOSSAUROS_SPRITE_QUANTIDADE] = { 40,40,55,55,40,40,40,40,39,39 };
	int AlturaFramesDino[DINOSSAUROS_SPRITE_QUANTIDADE] = { 43,43,25,26,43,43,43,43,37,37 };
	for (int i = 0; i < DINOSSAUROS_SPRITE_QUANTIDADE; i++) {
		DinoLargurasSprites[i] = LarguraFramesDino[i];
		DinoAlturasSprites[i] = AlturaFramesDino[i];
	}


	ObsPosicoesX = (float*)malloc(sizeof(float)*MAX_OBSTACULOS);
	ObsPosicoesY = (float*)malloc(sizeof(float)*MAX_OBSTACULOS);
	ObsTipos = (int*)malloc(sizeof(int)*MAX_OBSTACULOS);

	ObsLargurasSprites = (int*)malloc(sizeof(int)*OBSTACULOS_SPRITE_QUANTIDADE);
	ObsAlturasSprites = (int*)malloc(sizeof(int)*OBSTACULOS_SPRITE_QUANTIDADE);
	int LarguraObstaculos[OBSTACULOS_SPRITE_QUANTIDADE] = { 32,23,15,49,73, 42,42, 810 };
	int AlturaObstaculos[OBSTACULOS_SPRITE_QUANTIDADE] =  { 33,46,33,33,47, 36,36, 31 };
	for (int i = 0; i < OBSTACULOS_SPRITE_QUANTIDADE; i++) {
		ObsLargurasSprites[i] = LarguraObstaculos[i];
		ObsAlturasSprites[i] = AlturaObstaculos[i];
	}

}