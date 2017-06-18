#ifndef _GRAFO_H
#define _GRAFO_H

#include <stdio.h>
#include "lista.h"

typedef struct grafo *grafo;
typedef struct vertice *vertice;
typedef struct adjacente *adjacente;

struct grafo {
    lista vertices;
	vertice primeiro;
    int n_vertices;
	int n_pintados;
	int n_arestas;
	int n_cores;
};


struct vertice {
    lista adjacentes;
	int cor;
	int area;
	int rotulo;
    int visitado;
	int pintado;
};

struct adjacente {
	vertice v;
};

lista vizinhanca(vertice v);

unsigned int grau(vertice v);

grafo constroi_grafo(void);

int destroi_grafo(grafo g);

int destroi_vertice(void *g, void *n);

int destroi_adjacente(void *v, void *a);

vertice cria_vertice(grafo g, int cor, int area, int rotulo);

adjacente cria_adjacente(grafo g, vertice u, vertice v);

int desvisita(grafo g);

grafo copia_grafo(grafo g);

no busca_vertice(grafo g, vertice v);

vertice busca_por_rotulo(grafo g, int rot);

void imprime_grafo(grafo g);

void atualiza_info(grafo g);

#endif

