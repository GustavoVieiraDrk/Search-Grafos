#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Headers/busca_grafo.h"
#include "Headers/fila_dinamica.h"

typedef struct grafoo{
    char nomes_vertices[QTDADE_MAX_VERT][30];
    int matriz[QTDADE_MAX_VERT][QTDADE_MAX_VERT];
    int qtdade_atual_vert;
    bool eh_digrafo;
} grafo;

Grafo cria_grafo(bool eh_dig){
    int i, j;
    Grafo g = (Grafo) malloc(sizeof(grafo));

    if(g != NULL){
        g->eh_digrafo = eh_dig;
        g->qtdade_atual_vert = 0;
        for(i=0; i<QTDADE_MAX_VERT; i++){
            for(j=0; j<QTDADE_MAX_VERT; j++){
                g->matriz[i][j] = -1;
            }
        }
    }

    return g;
}

void libera_grafo(Grafo g){
    free(g);
}

void escreve_tela(){
    printf("Hello World");
}

void insere_vertice(Grafo g, char* nome){
    int num_do_vert = g->qtdade_atual_vert;
    g->qtdade_atual_vert++;
    int i, j;

    for(i=0; i<num_do_vert+1; i++){
        for(j=0; j<num_do_vert+1; j++){
            g->matriz[i][j] = 0;
        }
    }

    strcpy(g->nomes_vertices[num_do_vert], nome);
}

int nome_por_id(Grafo g, char *nome){
    int i;

    for(i=0; i<g->qtdade_atual_vert; i++){
        if(!strcmp(g->nomes_vertices[i], nome))
            return i;
    }

    return -1;
}

void insere_aresta(Grafo g, char *nome1, char *nome2, int peso){
    int id_nome1 = nome_por_id(g, nome1);
    int id_nome2 = nome_por_id(g, nome2);

    if(id_nome1 != -1 && id_nome2 != -1){
        g->matriz[id_nome1][id_nome2] = peso;

        if(!g->eh_digrafo)
            g->matriz[id_nome2][id_nome1] = peso;
    }
}

void imprime_peso(Grafo g, char *nome1, char *nome2){
    int id_nome1 = nome_por_id(g, nome1);
    int id_nome2 = nome_por_id(g, nome2);

    if(id_nome1 != -1 && id_nome2 != -1)
        printf("Peso: %d\n", g->matriz[id_nome1][id_nome2]);
    else
        printf("Erro: não existe pelo menos 1 dos 2 vertices\n");
}

bool possui_laco(Grafo g, char *nome){
    int id_nome = nome_por_id(g, nome);
    int peso = g->matriz[id_nome][id_nome];

    if(id_nome != -1){
        return peso > 0;
    } else
        return false;
}

void imprime_grau(Grafo g, char *nome){
    int id_nome = nome_por_id(g, nome);

    if(id_nome != -1){
        if(g->eh_digrafo){
            int i, cont=0;
            for(i=0; i<g->qtdade_atual_vert; i++){
                if(g->matriz[id_nome][i] > 0)
                    cont++;
            }
            printf("O vertice %s possui grau_saida=%d\n", nome, cont);
            cont=0;
            for(i=0; i<g->qtdade_atual_vert; i++){
                if(g->matriz[i][id_nome] > 0)
                    cont++;
            }
            printf("O vertice %s possui grau_entrada=%d\n", nome, cont);
        } else {
            int i, cont=0;
            for(i=0; i<g->qtdade_atual_vert; i++){
                if(g->matriz[i][id_nome] > 0)
                    cont++;
            }
            printf("O vertice %s possui grau=%d\n", nome, cont);
        }
    } else
        printf("Erro: vertice informado nao existe.\n");
}

void print_matriz(Grafo g){
    int i, j;
    for(i=0; i<g->qtdade_atual_vert; i++){
        for(j=0; j<g->qtdade_atual_vert; j++){
            printf("%d ", g->matriz[i][j]);
        }
        printf("\n");
    }
    printf("--------\n");
    for(i=0; i<g->qtdade_atual_vert; i++){
        printf("%s\n", g->nomes_vertices[i]);
    }
    printf("--------\n");
}

void desenhe_grafo(Grafo g){
    int i, j;
    printf("\n");

    if(!g->eh_digrafo){
        printf("graph G {\n");
        for(i=0; i<g->qtdade_atual_vert; i++){
            for(j=0; j<g->qtdade_atual_vert; j++){
                if(i >= j && g->matriz[i][j] > 0)
                    printf("  \"%s\" -- \"%s\"\n", g->nomes_vertices[i], g->nomes_vertices[j]);
            }
        }
    } else {
        printf("digraph G {\n");
        for(i=0; i<g->qtdade_atual_vert; i++){
            for(j=0; j<g->qtdade_atual_vert; j++){
                if(g->matriz[i][j] > 0)
                    printf("  \"%s\" -> \"%s\"\n", g->nomes_vertices[i], g->nomes_vertices[j]);
            }
        }
    }
    printf("}\n");
}

bool sao_adjacentes(Grafo g, char *nome1, char *nome2){
    int id_nome1 = nome_por_id(g, nome1);
    int id_nome2 = nome_por_id(g, nome2);

    if(id_nome1 != -1 && id_nome2 != -1){
        if((!g->eh_digrafo) && g->matriz[id_nome1][id_nome2] > 0)
            return true;
        else if(g->eh_digrafo && (g->matriz[id_nome1][id_nome2] > 0 || g->matriz[id_nome2][id_nome1] > 0))
            return true;
        else
            return false;
    } else {
        printf("Erro: não existe pelo menos 1 dos 2 vertices\n");
        return false;
    }
}

void imprime_adjacentes(Grafo g, char *nome){
    int id_nome = nome_por_id(g, nome), i;
    printf("Os vertices adjacentes de %s sao:\n", nome);

    if(g->eh_digrafo){
        for(i=0; i<g->qtdade_atual_vert; i++){
            if(g->matriz[id_nome][i] > 0)
                printf("%s\n", g->nomes_vertices[i]);
        }
        for(i=0; i<g->qtdade_atual_vert; i++){
            if(g->matriz[i][id_nome] > 0)
                printf("%s\n", g->nomes_vertices[i]);
        }
    } else {
        for(i=0; i<g->qtdade_atual_vert; i++){
            if(g->matriz[i][id_nome] > 0)
                printf("%s\n", g->nomes_vertices[i]);
        }
    }
    printf("--------------\n");
}

void busca_profundidade_recursiva(Grafo g, int no, int *visitados) {
    int i, foi_visitado = visitados[no];

    if (!foi_visitado) {
        visitados[no] = 1;
        printf("Visitei: %s\n", g->nomes_vertices[no]);

        for (i = 0; i < g->qtdade_atual_vert; i++) {
            if (g->matriz[no][i] > 0) {
                busca_profundidade_recursiva(g, i, visitados);
            }
        }
    }
}

void busca_profundidade(Grafo g, char *nome) {
    int cont, visitados[g->qtdade_atual_vert];

    for (cont = 0; cont < g->qtdade_atual_vert; cont++) {
        visitados[cont] = 0;
    }

    int id_nome = nome_por_id(g, nome);

    busca_profundidade_recursiva(g, id_nome, visitados);
}

void busca_largura(Grafo g, char *nome){
    int i, visitados[g->qtdade_atual_vert];

    for(i=0; i<g->qtdade_atual_vert; i++)
        visitados[i] = 0;

    int id_nome = nome_por_id(g, nome);

    visitados[id_nome] = 1;

    Fila f = create_queue();
    Info inf;
    inf.valor = id_nome;
    insert_queue(f, inf);

    while(!empty_queue(f)){
        Info el = remove_queue(f);
        int no_atual = el.valor;
        printf("Visitei: %s\n", g->nomes_vertices[no_atual]);

        for(i=0; i<g->qtdade_atual_vert; i++){
            if(g->matriz[no_atual][i] > 0){
                if(visitados[i] == 0){
                    visitados[i] = 1;
                    Info inf;
                    inf.valor = i;
                    insert_queue(f, inf);
                }
            }
        }
    }
    free_queue(f);
}
