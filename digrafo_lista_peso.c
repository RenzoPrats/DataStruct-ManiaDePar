//aluno: Renzo Prats Silva Souza   matricula: 11921ECP004
//arquivo que define as funcoes do digrafo
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "digrafo_lista_peso.h"

//cria digrafo
Grafo* criar_digrafo(int n) {
    int i;
    Grafo *g = (Grafo*) malloc(sizeof(Grafo));
    g->n = n;
    g->L = (No**) malloc(n * sizeof(No*));
    for (i = 0; i < n; i++){
        g->L[i] = criar_lista();
    }
    return g;
}

//destroi digrafo
void destruir_digrafo(Grafo *g) {
    int i;
    for (i = 0; i < g->n; i++){
        destruir_lista(g->L[i]);
    }
    free(g->L);
    free(g);
}

void inserir_arco(Grafo *p, int u, int v, int peso) {
    //insere na lista de adjacencia do vertice u o vertice v e o peso
    p->L[u] = inserir_na_lista(p->L[u], v, peso);
}

void remover_arco(Grafo *p, int u, int v) {
    //remova na lista de adjacencia do vertice u o vertice v e o peso
    p->L[u] = remover_da_lista(p->L[u], v);
}

//funcao que calcula o menor caminho(preco)
void dijkstra(Grafo *p, int u){
    // declarando a variavel preco
    int preco = 0;

    //declarando os vetores distancia e pai
    int* distancia = (int*) malloc(p->n * sizeof(int));

    int *pai = (int*) malloc(p->n * sizeof(int));

    //criando a fila de prioridade
    PQ *Fila = pq_criar(p->n);
    
    int v;
    //iniciando o vetor pai com -1, e a fila de prioridade com INT MAX
    for(v = 0; v < p->n; v++){
        pai[v] = -1;
        pq_adicionar(Fila, v, INT_MAX);
    }
    
    //muda o pai da posicao u(comeco do caminho) para ele mesmo
    pai[u] = u;
    //muda a prioridade de posicao u(comeco do caminho) para 0
    muda_prioridade(Fila, u, 0);
    
    //enquanto tiver elementos na fila
    while(!pq_vazia(Fila)){
        //extrai o elemento com prioridade minima
        t_item aux = pq_extrai_minimo(Fila);
        
        //salva na variavel v o indice desse elemento
        int v = aux.idx;
        //salva na variavel dist_v a prioridade desse elemento
        int dist_v = prioridade(Fila, v);

        //coloca no vetor distancia posicao v o dist_v
        distancia[v] = dist_v;
        
        // Se for retirado um vertice com distancia infinita estamos tratando de outro grafo
        //entao nao tera caminho a esse outro grafo e pode finalizar o dijkstra
        if(dist_v == INT_MAX){
            break;
        }
        
        No* t;
        //enquanto tiver elementos na lista de adjacencia do vertice v
        for(t = p->L[v]; t!=NULL; t = t->prox){
        //atualiza as distancias para cada vizinho de v
            int w = t->v; //valor na lista
            int peso = t->peso;
            //se dist_v + peso for menor que a prioridade entao achou um caminho com menor custo
            if(dist_v + peso < prioridade(Fila, w)){
                //muda a prioridade do vertice w para dist_v + peso
                muda_prioridade(Fila, w, dist_v+peso);
                //muda o pai de w para v
                pai[w] = v;
            }
        }
    }
    //depois que calculou o caminho com menor custo
    //verifica se o pai da ultima posicao eh -1, se for, nao tem caminho
    if(pai[p->n-1] != -1){
        //se o pai da ultima posicao for diferente de INT MAX entao tem caminho
        if(distancia[p->n - 1] != INT_MAX){
            //atribuimos a variavel preco o preco total deste caminho
            preco = distancia[p->n - 1];
        }else{
            preco = -1;
        }
    }else{
        preco = -1;
    }
    printf("%d\n", preco);

    //libera memoria
    pq_destruir(&Fila);
    free(distancia);
    free(pai);
}

//funcao que cria um novo grafo a partir do primeiro adaptado
//a ideia eh a seguinte, temos um caminho A -> B, e um caminho B -> C
//entao podemos dizer que temos um caminho A -> C, com peso = p1 + p2
//com isso garantimos que o dijkstra sempre ache o caminho com menor custo par
void adapta_grafo(Grafo *p, Grafo *Novo, int *index){
    //recebemos um grafo p, um grafo Novo que sera o criado, e o index para comecar a adaptacao(nesse caso sempre 0)
    
    //vamos acessar um vertice do grafo e ir andando em todas as conexoes que esse vertice tem
    for(No *t = p->L[*index]; t!=NULL; t = t->prox){
        
        int peso = t->peso;
        int vert = t->v;
        //criamos um No aux que sera uma das conexoes do vertice que estamos visitando atualmente
        No *aux = p->L[vert];

        //enquanto o aux for diferente de null, ou seja ele tem conexoes
        while(aux != NULL){
            //se essa conexao nao for igual ao proprio comeco
            if(aux->v != 0){
                //inserimos no arco no indice index esse vertice e seu novo peso
                inserir_arco(Novo, *index, aux->v, aux->peso + peso);
            }
            aux = aux->prox;
        }
    }
    //somamos um ao index
    (*index)++;
    //enquanto o index for diferente que o tamanho do grafo devemos chamar a funcao recursivamente
    if(*index != p->n){
        adapta_grafo(p, Novo, index);
    }
}