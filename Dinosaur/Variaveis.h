

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


OpenCLElements* cl;


int*		DinoEstados;
float*		DinoPosicoesX;
float*		DinoPosicoesY;
float*		DinoFitness;
float*		DinoVelocidadeY;
float*		DinoDNA;
float*		DinoDeslocamentoAviao;
float*		DinoCooldownAviao;
int*		DinoSpriteAtual;

int*		DinoLargurasSprites;
int*		DinoAlturasSprites;


float*		ObsPosicoesX;
float*		ObsPosicoesY;
int*		ObsTipos;

int*		ObsLargurasSprites;
int*		ObsAlturasSprites;


int			DNATamanho = 0;