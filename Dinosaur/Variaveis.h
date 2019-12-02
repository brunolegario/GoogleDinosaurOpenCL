

Dinossauro	Dinossauros[POPULACAO_TAMANHO];
Dinossauro*	MelhorDinossauro;
int			QuantidadeDinossauros = 0;


Obstaculo	obstaculo[MAX_OBSTACULOS];
Obstaculo	obstaculosModelo[20000];


float		VELOCIDADE;
int			TimerGeral = 0;
float		Periodo = 10;
float		DistanciaRecorde, DistanciaAtual;


int			DinossaurosMortos;
int			ObstaculoDaVez = 1;
int			Geracao;


int*		DinoEstados;
float*		DinoPosicoesX;
float*		DinoPosicoesY;
float*		DinoFitness;
float*		DinoVelocidadeY;
int*		DinoLargurasSprites;
int*		DinoAlturasSprites;
float**		DinoDNA;
float*		DinoDeslocamentoAviao;
float*		DinoCooldownAviao;
int*		DinoSpriteAtual;


float*		ObsPosicoesX;
float*		ObsPosicoesY;
int*		ObsLargurasSprites;
int*		ObsAlturasSprites;