#ifndef _GRAFO_H
#define _GRAFO_H

#include <stdio.h>
#include "lista.h"

typedef struct grafo *grafo;

struct grafo {
    lista vertices;
    int n_vertices;
	int n_arestas;
};

typedef struct vertice *vertice;

struct vertice {
    lista arestas;
	int cor;
	int area;
    int visitado;
	int pintado;
};
typedef struct aresta *aresta;

struct aresta {
	vertice u, v;
};

lista vizinhanca(vertice v);

unsigned int grau(vertice v);

grafo constroi_grafo(void);

int destroi_grafo(grafo g);

int destroi_vertice(void *v);

int destroi_aresta(void *a);

int cria_vertice(grafo g, int cor, int area);

int cria_aresta(grafo g, vertice u, vertice v);

int desvisita(grafo g);

grafo copia_grafo(grafo g);

#endif

