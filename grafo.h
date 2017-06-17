#ifndef _GRAFO_H
#define _GRAFO_H

#include <stdio.h>
#include "lista.h"

typedef struct grafo *grafo;

struct grafo {
    lista vertices;
    int n_vertices;
	int n_pintados;
	int n_arestas;
};

typedef struct vertice *vertice;

struct vertice {
    lista adjacentes;
	int cor;
	int area;
	int rotulo;
    int visitado;
	int pintado;
};
typedef struct adjacente *adjacente;

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

void imprime_grafo(grafo g);

#endif

