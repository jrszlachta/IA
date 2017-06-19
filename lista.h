#ifndef _LISTA_H
#define _LISTA_H

typedef struct no *no;

struct no {
	void *conteudo;
	no proximo;
};

typedef struct lista *lista;

struct lista {
	unsigned int tamanho;
	no primeiro;
};

unsigned int tamanho_lista(lista l);

no primeiro_no(lista l);

no ultimo_no(lista l);

no proximo_no(no n);

void *conteudo(no n);

no insere_lista(void *conteudo, lista l);

lista constroi_lista(void);

int destroi_lista(lista l, int destroi(void *));

int remove_no(struct lista *l, struct no *rno, int destroi(void *));

lista inverte_lista(lista l);

lista copia_lista(lista l);

#endif

