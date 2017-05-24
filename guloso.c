#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "floodit.h"

struct {
  // vetor de solucao a ser retornado
  int *sol;
  // lista com quantas casas cada passo possível p/ cada iteracao pinta (tam = numero de cores -1)
  int *partial;
  // contador de passos totais
  int steps;
  // tamanho total da area ocupada pela cor corrente
  int flooded;
}solution;

// TODO: Ler mapa ao inves de gerar cada vez (usar carrega_mapa)
// TODO: Var no pintar para contar quantas casa foram pintadas cada vez (var global?)
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
  // enquanto nao pinta mapa inteiro
    // testa possibilidades
    // pinta possibilidade escolhida no mapa real
    // conta quantas casas pintadas

  // imprime passos necessarios
  // imprime vetor de passos em ordem

	return 0;
}
