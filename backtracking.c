#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "floodit.h"

void iteration(void) {

}

void backtrack(tmapa *m, int l, int c) {
	// TODO lista/pilha
	// TODO recursão
}

int main(int argc, char **argv) {
	int cor;
	tmapa m;
	int semente;

	if (argc < 4 || argc > 5) {
		printf("Uso: %s <numero_de_linhas> <numero_de_colunas> <numero_de_cores> [<semente_aleatoria>]\n", argv[0]);
		exit(1);
	}

	m.nlinhas = atoi(argv[1]);
	m.ncolunas = atoi(argv[2]);
	m.ncores = atoi(argv[3]);

	if (argc == 5) semente = atoi(argv[4]);
	else semente = -1;

	gera_mapa(&m, semente);
	mostra_mapa(&m);

	// TODO

	return 0;
}
