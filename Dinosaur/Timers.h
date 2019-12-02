
int CriarTimer() {
	int timer;

	timer = CGerenciadorTimers::CriaTimer();
	PIG_ExistenciaTimer[timer] = 1;
	return timer;
}