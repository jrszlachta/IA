#include <stdlib.h>
#include <stdio.h>
#include "lista.h"
#include "grafo.h"
#include "floodit.h"

/*lista inverte_lista(lista l) {
	lista k = constroi_lista();
	for (no n = primeiro_no(l); n; n = proximo_no(n)) {
		int *aux = (int *) conteudo(n);
		insere_lista(aux, k);
	}
	destroi_lista(l, NULL);
	return k;
}*/

int main(int argc, char **argv) {
  int cor;
  tmapa m;
  int semente;

  /*if(argc < 4 || argc > 5) {
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
  gera_mapa(&m, semente);*/
  carrega_mapa(&m);
  grafo g = map_to_graph(&m);
  lista l2, l3;

  l2 = guloso2(g);
  l2 = inverte_lista(l2);
  l3 = guloso3(g);
  l3 = inverte_lista(l3);

  lista l = (tamanho_lista(l2) < tamanho_lista(l3)) ? l2 : l3;
  printf("%d\n", tamanho_lista(l));
  for (no n = primeiro_no(l); n; n = proximo_no(n)) {
	int *aux =  (int *)  conteudo(n);
	printf("%d ", *aux);
	free(aux);
  }
  printf("\n");
  destroi_lista(l2, NULL);
  destroi_lista(l3, NULL);

  destroi_grafo(g);
  return 0;
}
