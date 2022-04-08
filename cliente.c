//aluno: Renzo Prats Silva Souza   matricula: 11921ECP004
//arquivo com a funcao main
#include <stdio.h>
#include <stdlib.h>
#include "digrafo_lista_peso.h"

int main() {
    //declarando as variaveis para o input
    int n, m, u, v, w;
    //recebendo n e m
    scanf("%d %d", &n, &m);
    //criando o grafo G de tamanho n
    Grafo *G = criar_digrafo(n);

    //para cada m(estrada)
    for (int i = 0; i < m; i++) {
        //recebe a cidade_1, cidade_2 e o valor do pedagio
        scanf("%d %d %d", &u, &v, &w);
        //insere no arco a estrada de u para v com o valor do pedagio
        inserir_arco(G, u - 1, v - 1, w);
        //insere no arco a estrada de v para u com o valor do pedagio
        inserir_arco(G, v - 1, u - 1, w);
    }
    //declarando o ponteiro indx usado na funcao adapta_arco    
    int *indx;
    int v1 = 0;
    indx = &v1;
    
    //criando o grafo Novo que sera uma adaptacao do grafo G
    Grafo *Novo = criar_digrafo(n);
    
    //chamando a funcao adapta_grafo
    adapta_grafo(G, Novo, indx);
    
    //chamando a funcao dijkstra
    dijkstra(Novo, 0);

    //destruindo os grafos G e Novo
    destruir_digrafo(G);
    destruir_digrafo(Novo);
    return 0;
}