#include <stdlib.h>
#include <stdio.h>
#include "lista.h"
#include "grafo.h"
#include "floodit.h"

lista inverte_lista(lista l) {
	lista k = constroi_lista();
	for (no n = primeiro_no(l); n; n = proximo_no(n)) {
		int *aux = (int *) conteudo(n);
		insere_lista(aux, k);
	}
	destroi_lista(l, NULL);
	return k;
}

int main(int argc, char **argv) {
  int cor;
  tmapa m;
  int semente;

  if(argc < 4 || argc > 5) {
    printf("uso: %s <numero_de_linhas> <numero_de_colunas> <numero_de_cores> [<semente_aleatoria>]\n", argv[0]);
    exit(1);
  }

  m.nlinhas = atoi(argv[1]);
  m.ncolunas = atoi(argv[2]);
  m.ncores = atoi(argv[3]);

  if(argc == 5)
    semente = atoi(argv[4]);
  else
    semente = -1;
  gera_mapa(&m, semente);
  mostra_mapa_cor(&m);

  grafo g = map_to_graph(&m);
  lista l;
  l = guloso(g);
  l = inverte_lista(l);
  printf("\n");
  for (no n = primeiro_no(l); n; n = proximo_no(n)) {
	int *aux =  (int *)  conteudo(n);
	printf("%d ", *aux);
	free(aux);
  }
  printf("\n Num Passos: %d\n", tamanho_lista(l));
  destroi_lista(l, NULL);
  //imprime_grafo(g);

  destroi_grafo(g);

  return 0;
}
