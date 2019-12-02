
float DistanciaProximoObstaculo(float X) {

	int indice = ProcurarProximoObstaculo(X);

	return obstaculo[indice].X - X;
}


float LarguraProximoObstaculo(float X) {

	int indice = ProcurarProximoObstaculo(X);
	float Largura = obstaculo[indice].sprite[obstaculo[indice].FrameAtual]->Largura;

	return Largura;
}


float ComprimentoProximoObstaculo(float X) {

	int indice = ProcurarProximoObstaculo(X);
	float Altura = obstaculo[indice].sprite[obstaculo[indice].FrameAtual]->Altura;

	return Altura;
}


float AlturaProximoObstaculo(float X) {

	int indice = ProcurarProximoObstaculo(X);

	return obstaculo[indice].Y;
}