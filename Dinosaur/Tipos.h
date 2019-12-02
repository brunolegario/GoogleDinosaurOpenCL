#define LARG_GRAFICO			600
#define MAX_OBSTACULOS          7


typedef struct dinossauro {

	float X, Y;
	float VelocidadeY;

	int Frame;
	int SpriteAtual;
	int Estado;
	Sprite sprite[10];
	int ResetarFitness;

	int FrameAviao;
	float AviaoDeslocamento;
	float AviaoCooldown;

	int TamanhoDNA;
	float* DNA;
	float Fitness;

	RedeNeural* Cerebro;

}   Dinossauro;


typedef struct obstaculo {

	float X, Y;
	int Tipo;
	Sprite* sprite[2];
	int FrameAtual;

}   Obstaculo;