#ifndef FLOODIT_H_
#define FLOODIT_H_

#include "lista.h"
#include "grafo.h"

typedef struct {
  int nlinhas;
  int ncolunas;
  int ncores;
  int **mapa;
} tmapa;

typedef struct posicao *posicao;

struct posicao{
	int l, c;
	vertice v;
};

lista enfilados;
int rotulo;

void gera_mapa(tmapa *m, int semente);
void carrega_mapa(tmapa *m);
void mostra_mapa(tmapa *m);
void mostra_mapa_cor(tmapa *m);
void pinta(tmapa *m, int l, int c, int fundo, int cor);
void pinta_mapa(tmapa *m, int cor);
void enfila(tmapa *m, int l, int c, grafo g, vertice u);
void vertifica(tmapa *m, vertice v, int l, int c, int cor, grafo g);
grafo map_to_graph(tmapa *m);

#endif
