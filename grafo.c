#include <stdlib.h>
#include <stdio.h>
#include "lista.h"
#include "grafo.h"

lista vizinhanca(vertice v) { return v->arestas; }

unsigned int grau(vertice v) {return tamanho_lista(v->arestas);};

grafo constroi_grafo(void) {
	grafo g = malloc(sizeof(struct grafo));
	if (!g) return NULL;
	g->vertices	= constroi_lista();
	g->n_vertices = 0;
	g->n_arestas = 0;
	return g;
}

int destroi_grafo(grafo g) {
	destroi_lista(g->vertices, destroi_vertice);
	free(g);
}

int destroi_vertice(void *v) {
	vertice V = (vertice) v;
	if (destroi_lista(V->arestas, destroi_aresta) == 0) return 0;
	free(V);
	if (V) return 0;
	return 1;
}

int destroi_aresta(void *a) {
	aresta A = (aresta) a;
	free(A);
	if (A) return 0;
	return 1;
}

int cria_vertice(grafo g, int cor, int area) {
	vertice v = malloc(sizeof(struct vertice));
	if (!v) return 0;
	v->arestas = constroi_lista();
	v->cor = cor;
	v->area = area;
	v->visitado = 0;
	v->pintado = 0;
	if (insere_lista(v, g->vertices) == NULL) return 0;
	return 1;
}

int cria_aresta(grafo g, vertice u, vertice v) {
	aresta a = malloc(sizeof(struct aresta));
	if (!a) return 0;
	a->u = u;
	a->v = v;
	return 1;
}

int desvisita(grafo g) {
	for (no n = primeiro_no(g->vertices); n; n = proximo_no(n)) {
		vertice v = (vertice) conteudo(n);
		v->visitado = 0;
		v->pintado = 0;
	}
}
