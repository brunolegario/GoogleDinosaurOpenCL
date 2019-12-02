
void AtualizarMelhorDinossauro() {

	if (MelhorDinossauro->Estado == 3) {

		for (int i = 0; i < POPULACAO_TAMANHO; i++) {

			if (Dinossauros[i].Estado != 3) {
				MelhorDinossauro = &Dinossauros[i];
				break;
			}

		}

	}
}