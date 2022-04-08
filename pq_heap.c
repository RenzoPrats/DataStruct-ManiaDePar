//aluno: Renzo Prats Silva Souza   matricula: 11921ECP004
//arquivo que define as funcoes da fila de prioridade
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pq_heap.h"

#define F_ESQ(i) (2*i+1) /*Filho esquerdo de i*/
#define F_DIR(i) (2*i+2) /*Filho direito de i*/
#define PAI(i) ((i-1)/2)
#define swap(a,b) {t_item tmp = *a; *a = *b; *b = tmp;}

//cria fila de prioridade
PQ* pq_criar(int tam){
    PQ* p = (PQ*) malloc(sizeof(PQ));
    p->dados = (t_item*) malloc(tam * sizeof(t_item));
    p->n = 0;
    p->tam = tam;
    p->indice = (int*) malloc(tam * sizeof(int));
    return p;
}

//destroi a fila de prioridade
void pq_destruir(PQ **p) {
    free((*p)->dados);
    free((*p)->indice);
    free(*p);
    *p = NULL;
}

//adiciona na fila de prioridade
void pq_adicionar(PQ *p, int idx, int chave) {
    t_item item;
    item.chave = chave;
    item.idx = idx;

    p->dados[p->n] = item;
    
    //ajusta o indice da fila de prioridade
    p->indice[item.idx] = p->n;
    
    p->n++;

    //ajusta o elemento adicionado na heap
    sobe_no_heap(p, p->n - 1);
}

void sobe_no_heap(PQ *p, int pos) {
     
    //se o filho for menor que o pai ele sobe
    if (pos > 0 &&  p->dados[pos].chave < p->dados[PAI(pos)].chave) {

        p->indice[p->dados[PAI(pos)].idx] = pos; //posicao do pai passa a ser a posicao do filho
        p->indice[p->dados[pos].idx] = PAI(pos); //posicao do filho passa a ser a posicao do pai

        //troca os elementos
        swap(&p->dados[pos], &p->dados[PAI(pos)]);
        //chama a funcao ate estar tudo ajustado
        sobe_no_heap(p, PAI(pos));
    }
}

//extrai o minimo da fila de prioridade
t_item pq_extrai_minimo(PQ *p) {
    t_item item = p->dados[0];
    
    //troca o indice do primeiro elemento com o do ultimo
    p->indice[p->dados[0].idx] = p->n -1;
    p->indice[p->dados[p->n - 1].idx] = 0;

    //troca os elementos
    swap(&p->dados[0], &p->dados[p->n - 1]);
    p->n--;
    
    //ajusta a heap
    desce_no_heap(p, 0);
    return item;
}

void desce_no_heap(PQ *p, int pos) {
    //verifica se ha filho esquerdo
    if (F_ESQ(pos) < p->n){
        //o filho esquerdo comeca sendo o menor
        int menor_filho = F_ESQ(pos);
        
        //verifica se o filho da direita eh menor que o filho da esquerda
        if (F_DIR(pos) < p->n && p->dados[F_ESQ(pos)].chave > p->dados[F_DIR(pos)].chave){
            menor_filho = F_DIR(pos);
        }
        
        //verifica se o pai eh menor que o menor filho
        if (p->dados[pos].chave > p->dados[menor_filho].chave) {
            
            //troca o indice do pai com o indice do menor filho
            p->indice[p->dados[pos].idx] = menor_filho;
            p->indice[p->dados[menor_filho].idx] = pos;

            //troca os elementos
            swap(&p->dados[pos], &p->dados[menor_filho]);
            //chama a funcao ate estar tudo ajustado
            desce_no_heap(p, menor_filho);
        }
    }
}

//verifica se a fila de prioridade esta vazia
int pq_vazia(PQ *p) {
    return p->n == 0;
}

//muda a prioridade de um elemento
void muda_prioridade(PQ* p, int vertice, int val){
    //acha o elemento pelo indice e muda sua prioridade(chave)
    int ind_vertice = p->indice[vertice];
    p->dados[ind_vertice].chave = val;

    //sobe na heap pois o elemento so mudara sua prioridade caso a nova prioridade seja menor que a atual
    //portanto e necessario subir na heap ja que os menores valores sempre estao no comeco da heap
    sobe_no_heap(p, ind_vertice);

}

//retorna a prioridade de um vertice
int prioridade(PQ* p, int vertice){
    return p->dados[p->indice[vertice]].chave;
}