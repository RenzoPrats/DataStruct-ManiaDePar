//aluno: Renzo Prats Silva Souza   matricula: 11921ECP004
//arquivo que define o prototipo das funcoes da lista_peso 
#ifndef LISTA_PESO_H
#define LISTA_PESO_H

//Dados
typedef struct No {
  int v;
  int peso;
  struct No *prox;
} No;

//funcoes
No* criar_lista();
void destruir_lista(No* p);

No* inserir_na_lista(No *p, int x, int w);
No* remover_da_lista(No* p, int x);

int buscar_valor(No *p, int x);
int imprimir_lista(No *p);
  

#endif
