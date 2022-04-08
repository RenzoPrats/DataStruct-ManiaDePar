//aluno: Renzo Prats Silva Souza   matricula: 11921ECP004
//arquivo com as funcoes da lista_peso
#include <stdio.h>
#include <stdlib.h>
#include "lista_peso.h"

No* criar_lista(){
  return NULL;
}

void destruir_lista(No* p) {
  if (p != NULL) {
    destruir_lista(p->prox);
    free(p);
  }
}

No* inserir_na_lista(No *p, int x, int w) {
  No *novo = malloc(sizeof(No));
  novo->v = x;
  novo->peso = w;
  novo->prox = p;
  return novo;
}

No* remover_da_lista(No* p, int x) {
  No *proximo;
  if (p == NULL)
    return NULL;
  else if (p->v == x) {
    proximo = p->prox;
    free(p);
    return proximo;
  } else {
    p->prox = remover_da_lista(p->prox, x);
    return p;
  }
}

int buscar_valor(No *p, int x) {
  while(p != NULL){
    if (p->v == x) return p->peso;
    p = p->prox;
  }
return 0;
}

int imprimir_lista(No *p) {
  while(p != NULL){
    printf("%d (%d) ", p->v, p->peso); //imprime como um char
    if(p->prox!=NULL) printf("-> ");
    p = p->prox;
  }
  printf("\n");
return 0;
}
