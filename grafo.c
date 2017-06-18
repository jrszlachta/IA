#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "lista.h"
#include "grafo.h"

lista vizinhanca(vertice v) { return v->adjacentes; }

unsigned int grau(vertice v) {return tamanho_lista(v->adjacentes);};

grafo constroi_grafo(void) {
	grafo g = malloc(sizeof(struct grafo));
	if (!g) return NULL;
	g->vertices	= constroi_lista();
	g->n_vertices = 0;
	g->n_pintados = 0;
	g->n_arestas = 0;
	return g;
}

int destroi_grafo(grafo g) {
	for (no n = primeiro_no(g->vertices); n; n = proximo_no(n)) {
		destroi_vertice(g, n);
	}
	destroi_lista(g->vertices, NULL);
	free(g);
}

int destroi_vertice(void *g, void *node) {
	if (!node) return 1;
	grafo G = (grafo) g;
	no m = (no) node;
	vertice v = (vertice) conteudo(m);
	if (v->adjacentes) {
		for (no n = primeiro_no(v->adjacentes); n; n = proximo_no(n)) {
			adjacente a = (adjacente) conteudo(n);
			destroi_adjacente(v, a);
		}
		if (destroi_lista(v->adjacentes, NULL) == 0) return 0;
	}
	remove_no(G->vertices, m, NULL);
	free(v);
	if (v) return 0;
	return 1;
}

int destroi_adjacente(void *v, void *a) {
	adjacente A = (adjacente) a;
	vertice U = A->v;
	vertice V = (vertice) v;
	for (no n = primeiro_no(U->adjacentes); n; n = proximo_no(n)) {
		adjacente B = (adjacente) conteudo(n);
		if (B->v == V) {
			remove_no(U->adjacentes, n, NULL);
			free(B);
		}
	}
	free(A);
	if (A) return 0;
	return 1;
}

vertice cria_vertice(grafo g, int cor, int area, int rotulo) {
	vertice v = malloc(sizeof(struct vertice));
	if (!v) return NULL;
	v->adjacentes = constroi_lista();
	v->cor = cor;
	v->area = area;
	v->rotulo = rotulo;
	v->visitado = 0;
	v->pintado = 0;
	if (insere_lista(v, g->vertices) == NULL) return NULL;
	return v;
}

adjacente cria_adjacente(grafo g, vertice u, vertice v) {
	for (no n = primeiro_no(v->adjacentes); n; n = proximo_no(n)) {
		adjacente k = (adjacente) conteudo(n);
		if (u->rotulo == k->v->rotulo)
			return k;
	}
	adjacente a = malloc(sizeof(struct adjacente));
	adjacente b = malloc(sizeof(struct adjacente));
	if (!a || !b) return NULL;
	a->v = v;
	b->v = u;
	insere_lista(a, u->adjacentes);
	insere_lista(b, v->adjacentes);
	return a;
}

int desvisita(grafo g) {
	for (no n = primeiro_no(g->vertices); n; n = proximo_no(n)) {
		vertice v = (vertice) conteudo(n);
		v->visitado = 0;
		v->pintado = 0;
	}
	g->n_pintados = 0;
}

no busca_vertice(grafo g, vertice v) {
	vertice w;
	for (no n = primeiro_no(g->vertices); n; n = proximo_no(n)) {
		w = (vertice) conteudo(n);
		if (w == v)
			return n;
	}
	return NULL;
}

vertice busca_por_rotulo(grafo g, int rot) {
	vertice v;
	for (no n = primeiro_no(g->vertices); n; n = proximo_no(n)) {
		v = (vertice) conteudo(n);
		if (v->rotulo == rot)
			return v;
	}
	return NULL;
}

void imprime_grafo(grafo g) {
    no n, m;
    if (!g) return;
    printf("strict graph G {\n");
    for (n = primeiro_no(g->vertices); n; n = proximo_no(n)) {
        vertice v = (vertice) conteudo(n);
        printf("\t\"%d\" [label=\"cor=%d, p=%d, v=%d\"];\n", abs(v->rotulo), v->cor, v->pintado, v->visitado);
	}
    for (n = primeiro_no(g->vertices); n; n = proximo_no(n)) {
        vertice v = (vertice) conteudo(n);
        for (m = primeiro_no(v->adjacentes); m; m = proximo_no(m)) {
            adjacente a = (adjacente) conteudo(m);
            printf("\t\"%d\" -- \"%d\";\n", abs(v->rotulo), abs(a->v->rotulo));
        }
    }
	printf("}\n");
}

void atualiza_info(grafo g) {
	for (no n = primeiro_no(g->vertices); n; n = proximo_no(n)) {
		vertice v = (vertice) conteudo(n);
		g->n_vertices++;
		g->n_arestas += tamanho_lista(v->adjacentes);
	}
	g->n_arestas /= 2;
}
