#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "floodit.h"
#include "lista.h"
#include "grafo.h"

void gera_mapa(tmapa *m, int semente) {
  int i, j;

  if(semente < 0)
    srand(time(NULL));
  else
    srand(semente);
  m->mapa = (int**) malloc(m->nlinhas * sizeof(int*));
  for(i = 0; i < m->nlinhas; i++) {
    m->mapa[i] = (int*) malloc(m->ncolunas * sizeof(int));
    for(j = 0; j < m->ncolunas; j++)
      m->mapa[i][j] = 1 + rand() % m->ncores;
  }
}

void carrega_mapa(tmapa *m) {
  int i, j;

  scanf("%d", &(m->nlinhas));
  scanf("%d", &(m->ncolunas));
  scanf("%d", &(m->ncores));
  m->mapa = (int**) malloc(m->nlinhas * sizeof(int*));
  for(i = 0; i < m->nlinhas; i++) {
    m->mapa[i] = (int*) malloc(m->ncolunas * sizeof(int));
    for(j = 0; j < m->ncolunas; j++)
      scanf("%d", &(m->mapa[i][j]));
  }
}

void mostra_mapa(tmapa *m) {
  int i, j;

  printf("%d %d %d\n", m->nlinhas, m->ncolunas, m->ncores);
  for(i = 0; i < m->nlinhas; i++) {
    for(j = 0; j < m->ncolunas; j++)
      if(m->ncores > 10)
	printf("%02d ", m->mapa[i][j]);
      else
	printf("%d ", m->mapa[i][j]);
    printf("\n");
  }
}

void mostra_mapa_cor(tmapa *m) {
  int i, j;
  char* cor_ansi[] = { "\x1b[0m",
		       "\x1b[31m", "\x1b[32m", "\x1b[33m",
		       "\x1b[34m", "\x1b[35m", "\x1b[36m",
		       "\x1b[37m", "\x1b[30;1m", "\x1b[31;1m",
		       "\x1b[32;1m", "\x1b[33;1m", "\x1b[34;1m",
		       "\x1b[35;1m", "\x1b[36;1m", "\x1b[37;1m" };

  if(m->ncores > 15) {
    mostra_mapa(m);
    return;
  }
  printf("%d %d %d\n", m->nlinhas, m->ncolunas, m->ncores);
  for(i = 0; i < m->nlinhas; i++) {
    for(j = 0; j < m->ncolunas; j++)
      if(m->ncores > 10)
	printf("%s%02d%s ", cor_ansi[m->mapa[i][j]], m->mapa[i][j], cor_ansi[0]);
      else
	printf("%s%d%s ", cor_ansi[m->mapa[i][j]], m->mapa[i][j], cor_ansi[0]);
    printf("\n");
  }
}

void pinta(tmapa *m, int l, int c, int fundo, int cor) {
  m->mapa[l][c] = cor;
  if(l < m->nlinhas - 1 && m->mapa[l+1][c] == fundo)
    pinta(m, l+1, c, fundo, cor);
  if(c < m->ncolunas - 1 && m->mapa[l][c+1] == fundo)
    pinta(m, l, c+1, fundo, cor);
  if(l > 0 && m->mapa[l-1][c] == fundo)
    pinta(m, l-1, c, fundo, cor);
  if(c > 0 && m->mapa[l][c-1] == fundo)
    pinta(m, l, c-1, fundo, cor);
}

void pinta_mapa(tmapa *m, int cor) {
  if(cor == m->mapa[0][0])
    return;
  pinta(m, 0, 0, m->mapa[0][0], cor);
}

void enfila(tmapa *m, int l, int c, grafo g, vertice u) {
	//printf("Enfila: l: %d c:%d\n", l, c);
	int ok = 1;
	posicao p;
	for (no n = primeiro_no(enfilados); n && ok; n = proximo_no(n)) {
		p = (posicao) conteudo(n);
		ok &= (p->l != l || p->c != c);
	}
	if (ok) {
		p = malloc(sizeof(struct posicao));
		vertice v = cria_vertice(g, m->mapa[l][c], 0, 0);
		if (u != NULL) { cria_adjacente(g, u, v); }
		p->l = l;
		p->c = c;
		p->v = v;
		insere_lista(p, enfilados);
	}
}

posicao desenfila(void) {
	posicao p = NULL;
	no remover;
	for(no n = primeiro_no(enfilados); n; n = proximo_no(n))
		if (proximo_no(n) == NULL) {
			p = (posicao) conteudo(n);
			remover = n;
		}
	remove_no(enfilados, remover, NULL);
	return p;
}

void vertifica(tmapa *m, vertice v, int l, int c, int cor, grafo g) {
	//printf("Vertifica: l: %d c:%d\n", l, c);
	if (m->mapa[l][c] < 0) {
		int rot_atual = m->mapa[l][c];
		no n, m;
		/*posicao p;
		for(n =  primeiro_no(enfilados); n; n = proximo_no(n)) {
			p = (posicao) conteudo(n);
			m = n;
			remove_no(enfilados, n, NULL);
		}*/
		no o = busca_vertice(g, v);
		if (o) destroi_vertice(g, o);
		return;
	}
	//mostra_mapa(m);
	//printf("\n");
	v->area++;
	m->mapa[l][c] = rotulo;
	int i;
	// baixo
	if(l < m->nlinhas - 1) {
		i = m->mapa[l+1][c];
		if (i == cor)
			vertifica(m, v, l+1, c, cor, g);
		else if (i > 0)
			enfila(m, l+1, c, g, v);
		else if (i != rotulo){
			vertice w = busca_por_rotulo(g, i);
			cria_adjacente(g, v, w);
		}
	}
	// direita
	if(c < m->ncolunas - 1) {
		i = m->mapa[l][c+1];
		if (i == cor)
			vertifica(m, v, l, c+1, cor, g);
		else if (i > 0)
			enfila(m, l, c+1, g, v);
		else if (i != rotulo) {
			vertice w = busca_por_rotulo(g, i);
			cria_adjacente(g, v, w);
		}
	}
	// cima
	if(l > 0) {
		i = m->mapa[l-1][c];
		if (i == cor)
			vertifica(m, v, l-1, c, cor, g);
		else if (i > 0)
			enfila(m, l-1, c, g, v);
		else if (i != rotulo){
			vertice w = busca_por_rotulo(g, i);
			cria_adjacente(g, v, w);
		}
	}
	// esquerda
	if(c > 0) {
		i = m->mapa[l][c-1];
		if (i == cor)
			vertifica(m, v, l, c-1, cor, g);
		else if (i > 0)
			enfila(m, l, c-1, g, v);
		else if (i != rotulo) {
			vertice w = busca_por_rotulo(g, i);
			cria_adjacente(g, v, w);
		}
	}
}

grafo map_to_graph(tmapa *m) {
	grafo g = constroi_grafo();
	g->n_cores = m->ncores;
	enfilados = constroi_lista();
	enfila(m, 0, 0, g, NULL);
	rotulo = -1;
	while (tamanho_lista(enfilados) > 0) {
		/*imprime_grafo(g);
		for (no n =primeiro_no(enfilados); n; n = proximo_no(n)) {
			posicao q = (posicao) conteudo(n);
			printf("L: %d, C: %d, V->R: %d, V->C: %d\n", q->l, q->c, q->v->rotulo, q->v->cor);
		}
		printf("\n");*/
		posicao p = desenfila();
		if (g->primeiro == NULL) g->primeiro = p->v;
		p->v->rotulo = rotulo;
		vertifica(m, p->v, p->l, p->c, p->v->cor, g);
		free(p);
		rotulo--;
	}
	free(enfilados);
	return g;
}

void limpa_busca(grafo g) {
	for (no n = primeiro_no(g->vertices); n; n = proximo_no(n)) {
		vertice v = (vertice) conteudo(n);
		if(v->visitado == 1) v->visitado = 0;
	}
}

void pinta_grafo(grafo g, lista l, int cor) {
	for (no n = primeiro_no(l); n; n = proximo_no(n)) {
		vertice v = (vertice) conteudo(n);
		v->pintado = cor;
		for (no m = primeiro_no(v->adjacentes); m; m = proximo_no(m)) {
			adjacente a = (adjacente) conteudo(m);
			if (a->v->cor == cor && a->v->visitado != 2) {
				a->v->pintado = cor;
				a->v->visitado = 2;
				insere_lista(a->v, l);
			}
		}
	}
}

int busca_mais_comum(grafo g, lista l, int *areas) {
	int cor, max = 0;
	for (no n = primeiro_no(l); n; n = proximo_no(n)) {
		vertice v = (vertice) conteudo(n);
		for (no m = primeiro_no(v->adjacentes); m; m = proximo_no(m)) {
			adjacente a = (adjacente) conteudo(m);
			if (a->v->visitado == 0) {
				areas[a->v->cor-1] += a->v->area;
				a->v->visitado = 1;
			}
		}
	}
	for (int i = 1; i <= g->n_cores; i++) {
		if (areas[i-1] > max) {
			cor = i;
			max = areas[i-1];
		}
		areas[i-1] = 0;
	}
	limpa_busca(g);
	return cor;
}

lista guloso (grafo g) {
	lista pintados = constroi_lista();
	lista cores = constroi_lista();
	int ncores = g->n_cores;
	int *cor_mais_comum;
	int *area_cor = malloc(sizeof(int)*ncores);

	for (int i = 1; i <= ncores; i++)
		area_cor[i-1] = 0;

	g->primeiro->pintado = g->primeiro->cor;
	g->primeiro->visitado = 2;
	insere_lista(g->primeiro, pintados);

	while (tamanho_lista(pintados) < tamanho_lista(g->vertices)) {
		cor_mais_comum = malloc(sizeof(int));
		*cor_mais_comum = busca_mais_comum(g, pintados, area_cor);
		pinta_grafo(g, pintados, *cor_mais_comum);
		insere_lista(cor_mais_comum, cores);
		//imprime_grafo(g);
	}
	return cores;
}
