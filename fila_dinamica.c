#include <stdio.h>
#include <stdlib.h>
#include "Headers/fila_dinamica.h"

struct elemento{
	Info dados;
	struct elemento* prox;
};

struct fila{
	tpElemento* inicio;
	tpElemento* fim;
};

Fila create_queue(){
	Fila f = (Fila) malloc(sizeof(struct fila));

	if(!empty_queue(f)){
		f->fim = NULL;
		f->inicio = NULL;
	}

	return f;
}

int empty_queue(Fila f){
    if(f == NULL || f->inicio == NULL)
        return 1;
    else
    	return 0;
}

void insert_queue(Fila f, Info i){
    apElemento no = (apElemento) malloc(sizeof(tpElemento));

    no->dados = i;
    no->prox = NULL;

    if(f->fim == NULL)
        f->inicio = no;
    else
        f->fim->prox = no;

    f->fim = no;
}

Info remove_queue(Fila f){
    Info i;
    if(!empty_queue(f)){
        apElemento no = f->inicio;
        f->inicio = f->inicio->prox;

        if(f->inicio == NULL)
            f->fim = NULL;

        i = no->dados;
        free(no);
        return i;
    }else{
        printf("Fila vazia, nao ha nada a ser removido.\n");
        return i;
    }
}

void print_queue(Fila f){
    apElemento no = f->inicio;

    printf("--------------------------FILA--------------------------------\n");
    while(no != NULL){
        printf("%d\n", no->dados.valor);
        no = no->prox;
    }
    printf("--------------------------FILA--------------------------------\n");

    free(no);
}

void free_queue(Fila f){
	if(!empty_queue(f)){
		apElemento no;

		while(f->inicio != NULL){
			no=f->inicio;
			f->inicio=f->inicio->prox;
			free(no);
		}
		free(f);
	}
}
