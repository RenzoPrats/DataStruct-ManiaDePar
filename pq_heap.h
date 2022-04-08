//aluno: Renzo Prats Silva Souza   matricula: 11921ECP004
//arquivo que define o prototipo das funcoes da fila de prioridade
#ifndef PQ_HEAP_H
#define PQ_HEAP_H

//Dados
typedef struct {
    int chave;
    int idx;
} t_item;

typedef struct {
    t_item *dados;
    int tam, n;
    int *indice;
} PQ;

//Funcoes
//cria fila de prioridade
PQ* pq_criar(int tam);
//destroi fila de prioridade
void pq_destruir(PQ **p);

//sobe no heap
void sobe_no_heap(PQ *p, int pos);
//desce no heap
void desce_no_heap(PQ *p, int pos);

//adiciona na fila de prioridade
void pq_adicionar(PQ *p, int idx, int chave);
//extrai o que tem menor prioridade
t_item pq_extrai_minimo(PQ *p);

//verifica se a fila de prioridade esta vazia
int pq_vazia(PQ* p);

//muda a prioridade de algum elemento
void muda_prioridade(PQ* p, int vertice, int val);
//retorna a prioridade de um elemento
int prioridade(PQ* p, int vertice);

#endif