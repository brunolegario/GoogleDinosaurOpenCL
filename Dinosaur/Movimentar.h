
void MovimentarObstaculos() {

	int Largura;

	for (int i = 0; i < MAX_OBSTACULOS; i++) {

		obstaculo[i].X = obstaculo[i].X + VELOCIDADE;
		Largura = obstaculo[i].sprite[0]->Largura;

		if (obstaculo[i].X + Largura < -10) {
			getNextObstaculo(&obstaculo[i], ObstaculoDaVez);
			obstaculo[i].X = obstaculo[i].X - DistanciaAtual;
		}
	}
}


void MovimentarDinossauros() {

	clock_t startc, end;
	double cpu_time_used;

	startc = clock();

	for (int i = 0; i < QuantidadeDinossauros; i++) {

		if (Dinossauros[i].Estado == 3) {  /// MUERTO

			Dinossauros[i].X = Dinossauros[i].X + VELOCIDADE;

		} else {

			if (Dinossauros[i].Estado == 0 || Dinossauros[i].Estado == 1) {
				Dinossauros[i].Fitness = Dinossauros[i].Fitness + 2.0;

			} else {
				Dinossauros[i].Fitness = Dinossauros[i].Fitness + 1.0;
			}

		}
	}

	end = clock();
	cpu_time_used = ((double)(end - startc)) / CLOCKS_PER_SEC;

	printf("CPU : %f ms\n", cpu_time_used);
}

//void MovimentarDinossauros(cl::Program &P, cl::Context &C, cl::CommandQueue &Q) {
//
//	clock_t startc, end;
//	double gpu_time_used;
//
//	startc = clock();
//
//	/*int* Estados = (int*)malloc(sizeof(int)*QuantidadeDinossauros);
//	float* PosicoesX = (float*)malloc(sizeof(float)*QuantidadeDinossauros);
//	float* Fitness = (float*)malloc(sizeof(float)*QuantidadeDinossauros);*/
//
//	for (int i = 0; i <  ; i++) {
//		Estados[i] = Dinossauros[i].Estado;
//		PosicoesX[i] = Dinossauros[i].X;
//		Fitness[i] = Dinossauros[i].Fitness;
//	}
//
//
//	cl::Kernel move_dinosaurs = cl::Kernel(P, "move_dinosaurs");
//
//	cl::Buffer states(C, CL_MEM_READ_ONLY, sizeof(int)*QuantidadeDinossauros);
//	cl::Buffer pos_x(C, CL_MEM_READ_WRITE, sizeof(float)*QuantidadeDinossauros);
//	cl::Buffer fitness(C, CL_MEM_READ_WRITE, sizeof(float)*QuantidadeDinossauros);
//
//
//	Q.enqueueWriteBuffer(states, CL_TRUE, 0, sizeof(int)*QuantidadeDinossauros, Estados);
//	Q.enqueueWriteBuffer(pos_x, CL_TRUE, 0, sizeof(float)*QuantidadeDinossauros, PosicoesX);
//	Q.enqueueWriteBuffer(fitness, CL_TRUE, 0, sizeof(float)*QuantidadeDinossauros, Fitness);
//
//	move_dinosaurs.setArg(0, states);
//	move_dinosaurs.setArg(1, pos_x);
//	move_dinosaurs.setArg(2, fitness);
//	move_dinosaurs.setArg(4, VELOCIDADE);
//
//	Q.enqueueNDRangeKernel(move_dinosaurs, cl::NullRange, cl::NDRange(2048), cl::NDRange(128));
//	Q.enqueueReadBuffer(pos_x, CL_TRUE, 0, sizeof(float)*QuantidadeDinossauros, PosicoesX);
//	Q.enqueueReadBuffer(fitness, CL_TRUE, 0, sizeof(float)*QuantidadeDinossauros, Fitness);
//
//
//	for (int i = 0; i < QuantidadeDinossauros; i++) {
//		Dinossauros[i].X = PosicoesX[i];
//		Dinossauros[i].Fitness = Fitness[i];
//	}
//
//	end = clock();
//	gpu_time_used = ((double)(end - startc)) / CLOCKS_PER_SEC;
//
//	printf("GPU : %f ms\n", gpu_time_used);
//
//}