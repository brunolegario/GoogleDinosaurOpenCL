#define OBSTACULOS_SPRITE_QUANTIDADE    8
#define DINOSSAUROS_SPRITE_QUANTIDADE	10


typedef struct sprite {

	int Largura, Altura;

}   Sprite;


Sprite SpriteObstaculo[OBSTACULOS_SPRITE_QUANTIDADE];
Sprite SpriteAviao[2];


//#########################################################################//


void InicializarSpriteAviao() {

	for (int i = 0; i < 2; i++) {
		SpriteAviao[i].Largura = 70;
		SpriteAviao[i].Altura = 37;
	}
}

void InicializarSpritesObstaculos() {

	int i;
	int LarguraObstaculos[OBSTACULOS_SPRITE_QUANTIDADE] = { 32,23,15,49,73, 42,42, 810 };
	int AlturaObstaculos[OBSTACULOS_SPRITE_QUANTIDADE] =  { 33,46,33,33,47, 36,36, 31 };

	for (i = 0; i < OBSTACULOS_SPRITE_QUANTIDADE; i++) {

		SpriteObstaculo[i].Largura = LarguraObstaculos[i];
		SpriteObstaculo[i].Altura = AlturaObstaculos[i];
	}
}

void InicializarSprites() {

	InicializarSpritesObstaculos();
	InicializarSpriteAviao();

}


Sprite getDinossauroSprite(int Indice) {

	int LarguraFramesDino[DINOSSAUROS_SPRITE_QUANTIDADE] = { 40,40,55,55,40,40,40,40,39,39 };
	int AlturaFramesDino[DINOSSAUROS_SPRITE_QUANTIDADE] = { 43,43,25,26,43,43,43,43,37,37 };
	Sprite sprite;

	sprite.Largura = LarguraFramesDino[Indice];
	sprite.Altura = AlturaFramesDino[Indice];

	return sprite;
}

Sprite* getObstaculosSprite(int Tipo, int Frame) {

	if (Tipo == PASSARO_CODIGO_TIPO) {

		if (Frame == 0) {
			return &SpriteObstaculo[5];
		} else {
			return &SpriteObstaculo[6];
		}

	} 
	else {

		if (Tipo == ESPINHO_CODIGO_TIPO) {
			return &SpriteObstaculo[7];
		} else {
			return &SpriteObstaculo[Tipo];
		}

	}
}