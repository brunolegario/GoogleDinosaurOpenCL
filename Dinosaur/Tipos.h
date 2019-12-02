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



typedef struct openclelements {
	cl::Platform default_platform;
	cl::Device default_device;
	cl::Context context;
	cl::Program program;
	cl::CommandQueue queue;

	cl::Buffer b_d_states;
	cl::Buffer b_d_pos_x;
	cl::Buffer b_d_pos_y;
	cl::Buffer b_d_fitness;
	cl::Buffer b_d_speedy;
	cl::Buffer b_d_planemove;
	cl::Buffer b_d_planecool;
	cl::Buffer b_d_sprite;

	cl::Buffer b_d_dnas;

	cl::Buffer b_d_spritewidth;
	cl::Buffer b_d_spriteheight;


	cl::Buffer b_o_pos_x;
	cl::Buffer b_o_pos_y;
	cl::Buffer b_o_types;


	cl::Buffer b_o_spritewidth;
	cl::Buffer b_o_spriteheight;

} OpenCLElements;