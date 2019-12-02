#pragma warning (disable : 4996)
#pragma comment(lib, "OpenCL.lib")

#define CL_HPP_TARGET_OPENCL_VERSION 200
#define CL_TARGET_OPENCL_VERSION 220


//#########################################################################//


#define PASSARO_CODIGO_TIPO     5
#define ESPINHO_CODIGO_TIPO     6

#define POPULACAO_TAMANHO       2000

#define DINO_BRAIN_QTD_LAYERS   1       /// Quantidade de camadas escondidas na rede neural
#define DINO_BRAIN_QTD_INPUT    6       /// Quantidade de neuronios na camada de entrada
#define DINO_BRAIN_QTD_HIDE     6       /// Quantidade de neuronios nas camadas escondidas
#define DINO_BRAIN_QTD_OUTPUT   3       /// Quantidade de neuronios na camada de saida


//#########################################################################//


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <CL/cl2.hpp>
#include <vector>
#include <errno.h>


#include "kernels.h"
#include "Sprites.h"
#include "redeNeural.c"
#include "Tipos.h"
#include "Variaveis.h"
#include "FuncoesAuxiliares.h"
#include "DNAs.h"
#include "GeradorObstaculos.h"
#include "Inicializar.h"
#include "Alocacoes.h"
#include "Colisao.h"
#include "Movimentar.h"
#include "Atualizar.h"
#include "InputsRedeNeural.h"


//#########################################################################//


void SetDefaults(cl::Platform &default_platform, cl::Device &default_device);

void AplicarGravidade();
void ControlarEstadoDinossauros();

void RandomMutations();

void InicializarNovaPartida();
void EncerrarPartida();
void VerificarFimDePartida();

void ConfiguracoesIniciais();

void CarregarRede();


//#########################################################################//


int main() {
	cl::Platform default_platform;
	cl::Device default_device;
	

	SetDefaults(default_platform, default_device);
	std::cout << "Using platform: " << default_platform.getInfo<CL_PLATFORM_NAME>() << std::endl;
	std::cout << "Using device: " << default_device.getInfo<CL_DEVICE_NAME>() << std::endl;


	//##############################//


	cl::Context context({ default_device });
	cl::Program::Sources sources;


	sources.push_back({ kernel_code.c_str(), kernel_code.length() });


	cl::Program program(context, sources);
	if (program.build({ default_device }) != CL_SUCCESS) {
		std::cout << "Error building: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device) << std::endl;
		system("pause");
		exit(1);
	}


	cl::CommandQueue queue(context, default_device);


	//##############################//


	ConfiguracoesIniciais();

	int TimerTotal = 0;

	while (TimerGeral < 1000) {

		if (TimerTotal >= Periodo) {

			MovimentarObstaculos();  // CPU
			//MovimentarDinossauros(program, context, queue); // GPU
			MovimentarDinossauros(); // CPU

			AtualizarMelhorDinossauro(); // CPU
			AplicarGravidade(); // GPU
			AplicarColisao(); // GPU
			ControlarEstadoDinossauros(); // GPU

			if (fabs(VELOCIDADE) < 8) {
				VELOCIDADE = VELOCIDADE - 0.0005;
			}

			DistanciaAtual = DistanciaAtual + fabs(VELOCIDADE);
			if (DistanciaAtual > 1000000 && DistanciaAtual > DistanciaRecorde) {
				//SalvarRedeArquivo();
				DinossaurosMortos = POPULACAO_TAMANHO;
			}

			VerificarFimDePartida();
			TimerTotal = 0;
		} else {
			TimerTotal++;
		}

		TimerGeral++;
	}



	// Finish
	system("pause");
	return 0;
}


//#########################################################################//


void SetDefaults(cl::Platform &default_platform, cl::Device &default_device) {
	// Find available platforms
	std::vector<cl::Platform> all_platforms;
	cl::Platform::get(&all_platforms);
	if (all_platforms.size() == 0) {
		std::cout << "No platforms found. Check OpenCL installation!\n";
		exit(1);
	}


	// Print available platforms
	/*std::cout << "Available platforms:" << std::endl;
	for (int i = 0; i < all_platforms.size(); i++) {
		cl::Platform platform = all_platforms[i];
		std::cout << "\tPlatform[" << i << "]: "
			<< platform.getInfo<CL_PLATFORM_NAME>() << std::endl;
	}*/


	// Set the first platform as default
	default_platform = all_platforms[0];


	// Find available devices in selected platform
	std::vector<cl::Device> all_devices;
	default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
	if (all_devices.size() == 0) {
		std::cout << "No devices found. Check OpenCL installation!\n";
		exit(1);
	}


	// Print available platforms
	/*std::cout << "Available devices:" << std::endl;
	for (int i = 0; i < all_devices.size(); i++) {
		cl::Device device = all_devices[i];
		std::cout << "\tDevice[" << i << "]: "
			<< device.getInfo<CL_DEVICE_NAME>() << std::endl;
	}*/


	// Set the first device as default
	default_device = all_devices[0];
}


//void AplicarGravidade() {
//
//	for (int i = 0; i < QuantidadeDinossauros; i++) {
//
//		if (Dinossauros[i].Y > 15) {
//
//			if (Dinossauros[i].Estado != 4) {         /// VOANDO
//
//				Dinossauros[i].VelocidadeY = Dinossauros[i].VelocidadeY - (0.08);
//
//			} 
//			else {
//
//				if (Dinossauros[i].VelocidadeY <= 0) {
//					Dinossauros[i].VelocidadeY = 0;
//				} else {
//					Dinossauros[i].VelocidadeY = Dinossauros[i].VelocidadeY - (0.08);
//				}
//
//			}
//
//			Dinossauros[i].Y = Dinossauros[i].Y + Dinossauros[i].VelocidadeY;
//
//		} 
//		else {
//
//			Dinossauros[i].VelocidadeY = 0;
//			Dinossauros[i].Y = 15;
//			if (Dinossauros[i].Estado == 2)
//				Dinossauros[i].Estado = 0;
//
//		}
//	}
//}

void AplicarGravidade() {

	for (int i = 0; i < QuantidadeDinossauros; i++) {

		if (Dinossauros[i].Y > 15) {

			if (Dinossauros[i].Estado != 4) {         /// VOANDO

				Dinossauros[i].VelocidadeY = Dinossauros[i].VelocidadeY - (0.08);

			} else {

				if (Dinossauros[i].VelocidadeY <= 0) {
					Dinossauros[i].VelocidadeY = 0;
				} else {
					Dinossauros[i].VelocidadeY = Dinossauros[i].VelocidadeY - (0.08);
				}

			}

			Dinossauros[i].Y = Dinossauros[i].Y + Dinossauros[i].VelocidadeY;

		} else {

			Dinossauros[i].VelocidadeY = 0;
			Dinossauros[i].Y = 15;
			if (Dinossauros[i].Estado == 2)
				Dinossauros[i].Estado = 0;

		}
	}
}

void ControlarEstadoDinossauros() {       /// Função responsavel por calcular a decisão da rede neural e aplicar no dinossauro (ou seja, é a função que faz ele pular, abaixar ou usar o aviao)

	int Abaixar = 0, Pular = 0, Aviao = 0;
	float Saida[10];
	float Entrada[10];

	for (int i = 0; i < QuantidadeDinossauros; i++) {

		if (Dinossauros[i].Estado != 3) {

			Entrada[0] = DistanciaProximoObstaculo(Dinossauros[i].X);
			Entrada[1] = LarguraProximoObstaculo(Dinossauros[i].X);
			Entrada[2] = AlturaProximoObstaculo(Dinossauros[i].X);
			Entrada[3] = ComprimentoProximoObstaculo(Dinossauros[i].X);
			Entrada[4] = fabs(VELOCIDADE);
			Entrada[5] = Dinossauros[i].Y;


			RNA_CopiarParaEntrada(Dinossauros[i].Cerebro, Entrada);     /// Enviando informações para a rede neural
			RNA_CalcularSaida(Dinossauros[i].Cerebro);                  /// Calculando a decisão da rede
			RNA_CopiarParaSaida(Dinossauros[i].Cerebro, Saida);         /// Extraindo a decisão para vetor ''saida''


			if (Saida[0] == 0.0) { Pular = 0; }
			else				 { Pular = 1; }

			if (Saida[1] == 0.0) { Abaixar = 0; }	
			else				 { Abaixar = 1; }

			if (Saida[2] == 0.0) { Aviao = 0; }	
			else				 { Aviao = 1; }


			if (DINO_BRAIN_QTD_OUTPUT == 2) { Aviao = 0; }
				

			if (Dinossauros[i].Estado != 4) { /// Voando

				if (Dinossauros[i].Estado != 2) {
					Dinossauros[i].Estado = 0;
				}

				if (Abaixar && Dinossauros[i].Estado != 2) {
					Dinossauros[i].Estado = 1;
				}

				if (Abaixar && Dinossauros[i].Estado == 2) {

					if (Dinossauros[i].VelocidadeY > 0) { 
						Dinossauros[i].VelocidadeY = 0; 
					}
						
					Dinossauros[i].Y = Dinossauros[i].Y - 2;
				}

				if (Pular && Dinossauros[i].Estado != 2) {

					Dinossauros[i].Estado = 2;
					Dinossauros[i].Y = Dinossauros[i].Y + 1;

					Dinossauros[i].VelocidadeY = Dinossauros[i].VelocidadeY + 4.0;
				}

				if (Aviao && Dinossauros[i].AviaoCooldown <= 0) {

					Dinossauros[i].Estado = 4;
					Dinossauros[i].Y = Dinossauros[i].Y + 1;
					if (Dinossauros[i].VelocidadeY <= 0.5 && Dinossauros[i].Y < 25) {
						Dinossauros[i].VelocidadeY = Dinossauros[i].VelocidadeY + 4.0;
					}
					Dinossauros[i].AviaoCooldown = 4000.0;

				}
			} 
			else {

				if (Dinossauros[i].AviaoDeslocamento >= 820.0) {

					Dinossauros[i].AviaoDeslocamento = 0;
					Dinossauros[i].Estado = 2;

				} else {

					Dinossauros[i].AviaoDeslocamento = Dinossauros[i].AviaoDeslocamento + fabs(VELOCIDADE);

				}

			}


			Dinossauros[i].AviaoCooldown = Dinossauros[i].AviaoCooldown - fabs(VELOCIDADE);


			if (Dinossauros[i].Estado == 0) { /// Em pé
			
				Dinossauros[i].SpriteAtual = 0 + Dinossauros[i].Frame;

			}
			if (Dinossauros[i].Estado == 1) { /// Deitado
			
				Dinossauros[i].SpriteAtual = 2 + Dinossauros[i].Frame;

			}
			if (Dinossauros[i].Estado == 2) { /// Pulando
			
				Dinossauros[i].SpriteAtual = 4 + Dinossauros[i].Frame;

			}
			if (Dinossauros[i].Estado == 3) { /// Muerto
			
				Dinossauros[i].SpriteAtual = 6 + Dinossauros[i].Frame;

			}
			if (Dinossauros[i].Estado == 4) {  /// Voando
			
				Dinossauros[i].SpriteAtual = 8 + Dinossauros[i].Frame;

			}
		}
	}
}


void RandomMutations() {

	static float RangeRandom = Dinossauros[0].TamanhoDNA;

	Dinossauro* Vetor[POPULACAO_TAMANHO];
	Dinossauro* Temp;


	if (Geracao < LARG_GRAFICO) {

		GeracaoCompleta = Geracao + 1;
		BestFitnessPopulacao[Geracao] = BestFitnessGeracao();
		MediaFitnessPopulacao[Geracao] = MediaFitnessGeracao();

	} 
	else {

		for (int i = 0; i < LARG_GRAFICO - 1; i++) {
			BestFitnessPopulacao[i] = BestFitnessPopulacao[i + 1];
			MediaFitnessPopulacao[i] = MediaFitnessPopulacao[i + 1];
		}
		BestFitnessPopulacao[GeracaoCompleta] = BestFitnessGeracao();
		MediaFitnessPopulacao[GeracaoCompleta] = MediaFitnessGeracao();

	}


	for (int i = 0; i < POPULACAO_TAMANHO; i++) {
		Vetor[i] = &Dinossauros[i];
	}


	for (int i = 0; i < POPULACAO_TAMANHO; i++) {

		for (int j = 0; j < POPULACAO_TAMANHO - 1; j++) {

			if (Vetor[j]->Fitness < Vetor[j + 1]->Fitness) {
				Temp = Vetor[j];
				Vetor[j] = Vetor[j + 1];
				Vetor[j + 1] = Temp;
			}

		}
	}


	int Step = 1;
	for (int i = 0; i < Step; i++)  /// Clonando individuos
	{
		for (int j = Step + i; j < POPULACAO_TAMANHO; j = j + Step) {

			for (int k = 0; k < Vetor[j]->TamanhoDNA; k++) {
				Vetor[j]->DNA[k] = Vetor[i]->DNA[k];				/// individuo 'j' recebe dna do individuo 'i'
			}
		}
	}


	for (int j = Step; j < POPULACAO_TAMANHO; j++) {  /// Aplicando random mutations 
		
		int tipo;
		int mutations = (rand() % (int)RangeRandom) + 1;

		for (int k = 0; k < mutations; k++) {

			tipo = rand() % 3;

			int indice = rand() % Vetor[j]->TamanhoDNA;

			switch (tipo) {
				case 0:
					Vetor[j]->DNA[indice] = getRandomValue();       /// Valor Aleatorio
					break;
				case 1: {
					float number = (rand() % 10001) / 10000.0 + 0.5;
					Vetor[j]->DNA[indice] = Vetor[j]->DNA[indice] * number;   /// Multiplicação aleatoria
				}	break;
				case 2: {
					float number = getRandomValue() / 100.0;
					Vetor[j]->DNA[indice] = Vetor[j]->DNA[indice] + number; /// Soma aleatoria
				}	break;
			}

		}

	}


	for (int j = 0; j < POPULACAO_TAMANHO; j++) {  /// Copiando novos DNAs para DNAsDaVez

		for (int k = 0; k < Dinossauros[j].TamanhoDNA; k++) {
			DNADaVez[j][k] = Dinossauros[j].DNA[k];
		}
	}


	for (int i = 0; i < POPULACAO_TAMANHO; i++) {
		Vetor[i]->ResetarFitness = 1;
	}


	printf("Range Random: %f\n", RangeRandom);
	RangeRandom = RangeRandom * 0.99;
	if (RangeRandom < 20) {
		RangeRandom = 20;
	}

	Geracao++;
}


void InicializarNovaPartida() {

	GerarListaObstaculos();
	// CarregarListaObstaculos();

	DistanciaAtual = 0;
	VELOCIDADE = -3;
	DinossaurosMortos = 0;

	InicializarObstaculos();

	for (int i = 0; i < POPULACAO_TAMANHO; i++) {

		InicializarDinossauro(i, DNADaVez[i], 300 + (rand() % 200 - 100), 15);

	}
}

void EncerrarPartida() {

	if (DistanciaAtual > DistanciaRecorde) {

		DistanciaRecorde = DistanciaAtual;
		SalvarRedeArquivo();
	}

}

void VerificarFimDePartida() {

	if (DinossaurosMortos == POPULACAO_TAMANHO) {

		EncerrarPartida();
		RandomMutations();
		InicializarNovaPartida();
	}
}


void ConfiguracoesIniciais() {

	InicializarSprites();

	AlocarDinossauros();
	AlocarPonteiros();


	TimerGeral = 0;
	DistanciaRecorde = 0;
	Geracao = 0;
	MelhorDinossauro = &Dinossauros[0];

	InicializarDNA();
	InicializarNovaPartida();
}


void CarregarRede() {

	FILE* f = fopen("rede", "rb");
	fread(&Dinossauros[0].TamanhoDNA, 1, sizeof(int), f);
	fread(DNADaVez[0], Dinossauros[0].TamanhoDNA, sizeof(float), f);
	fclose(f);

}