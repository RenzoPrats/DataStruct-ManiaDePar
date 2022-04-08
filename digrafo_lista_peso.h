//aluno: Renzo Prats Silva Souza   matricula: 11921ECP004
//arquivo que define o prototipo das funcoes do digrafo
#ifndef DIGRAFO_LISTA_PESO_H
#define DIGRAFO_LISTA_PESO_H
#include "lista_peso.h"
#include "pq_heap.h"

//Dados
typedef struct {
    No **L; //Lista de adjacencias
    int n;
} Grafo;

//Funcoes
//cria digrafo
Grafo* criar_digrafo(int n);
//destroi digrafo
void destruir_digrafo(Grafo *p);

//conecta um vertice no outro no digrafo(cria um arco)
void inserir_arco(Grafo *p, int u, int v, int w);
//remove um vertice do outro no digrafo(remove um arco)
void remover_arco(Grafo *p, int u, int v);

//calcula o menor caminho(preco)
void dijkstra(Grafo *p, int u);

//adapta o Grafo para poder calcular o menor caminho(preco) par
void adapta_grafo(Grafo *p, Grafo *Novo, int *index);

#endif