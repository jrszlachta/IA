#include <malloc.h>
#include "lista.h"

unsigned int tamanho_lista(lista l) { return l->tamanho; }

no primeiro_no(lista l) { return l->primeiro ? l->primeiro : NULL; }

void *conteudo(no n) { return n->conteudo; }

no proximo_no(no n) { return n->proximo; }

no ultimo_no(lista l) {
	no ultimo;
	for (no n = primeiro_no(l); n; n = proximo_no(n)) {
		if (proximo_no(n) == NULL)
			ultimo = n;
	}
	return ultimo;
}

lista constroi_lista(void) {
  lista l = malloc(sizeof(struct lista));
  if ( ! l ) return NULL;
  l->primeiro = NULL;
  l->tamanho = 0;
  return l;
}

int destroi_lista(lista l, int destroi(void *)) {
  no p;
  int ok=1;
  while ( (p = primeiro_no(l)) ) {
    l->primeiro = proximo_no(p);
    if ( destroi ) ok &= destroi(conteudo(p));
    free(p);
  }
  if (l) free(l);
  return ok;
}

no insere_lista(void *conteudo, lista l) {
  no novo = malloc(sizeof(struct no));
  if ( ! novo ) return NULL;
  novo->conteudo = conteudo;
  novo->proximo = primeiro_no(l);
  ++l->tamanho;
  return l->primeiro = novo;
}

int remove_no(struct lista *l, struct no *rno, int destroi(void *)) {
	int r = 1;
	if (l->primeiro == rno) {
		l->primeiro = rno->proximo;
		if (destroi != NULL) {
			r = destroi(conteudo(rno));
		}
		free(rno);
		l->tamanho--;
		return r;
	}
	for (no n = primeiro_no(l); n->proximo; n = proximo_no(n)) {
		if (n->proximo == rno) {
			n->proximo = rno->proximo;
			if (destroi != NULL) {
				r = destroi(conteudo(rno));
			}
			free(rno);
			l->tamanho--;
			return r;
		}
	}
	return 0;
}

lista inverte_lista(lista l) {
    lista k = constroi_lista();
    for (no n = primeiro_no(l); n; n = proximo_no(n)) {
        void *aux = conteudo(n);
        insere_lista(aux, k);
    }
    destroi_lista(l, NULL);
    return k;
}

lista copia_lista(lista l) {
    lista k = constroi_lista();
    for (no n = primeiro_no(l); n; n = proximo_no(n)) {
        void *aux = conteudo(n);
        insere_lista(aux, k);
    }
    return inverte_lista(k);
}
