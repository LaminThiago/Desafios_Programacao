#include <stdio.h>
#include <stdlib.h>
typedef struct TipoCliente {
  int id;
  int tempo;
  struct TipoCliente *prox;
} TipoCliente;
typedef struct {
  TipoCliente *inicio, *fim;
} TipoFila;
void inicializafila(TipoFila *fila) {
  fila->inicio = NULL;
  fila->fim = NULL;
}
void inicializafilas(TipoFila caixas[], int c) {
  for (int i = 0; i < c; i++) {
    inicializafila(&caixas[i]);
  }
}
int filavazia(TipoFila *fila) {
  if (fila->inicio == NULL && fila->fim == NULL) {
    return 1;
  }
  return 0;
}
void insere(TipoFila *fila, int id, int tempo) {
  TipoCliente *novoitem = malloc(sizeof(TipoCliente));
  novoitem->id = id;
  novoitem->tempo = tempo;
  novoitem->prox = NULL;
  if (filavazia(fila)) {
    fila->inicio = novoitem;
    fila->fim = novoitem;
  } else {
    fila->fim->prox = novoitem;
    fila->fim = novoitem;
  }
}
TipoCliente retira(TipoFila *fila) {
  TipoCliente auxx = {0, 0, NULL};
  if (!filavazia(fila)) {
    TipoCliente *aux = fila->inicio;
    auxx.id = aux->id;
    auxx.tempo = aux->tempo;
    fila->inicio = fila->inicio->prox;
    free(aux);
    if (filavazia(fila)) {
      fila->fim = NULL;
    }
  }
  return auxx;
}
int somadostempos(TipoFila *fila) {
  TipoCliente *vet = fila->inicio;
  int retorno = 0;
    if (filavazia(fila)) {
    return -1;
  }
  while (vet != NULL) {
    retorno = retorno + vet->tempo;
    vet = vet->prox;
  }
  return retorno;
}
int menortempo(TipoFila caixas[], int c) {
  int tmin, retorno=0;
  tmin = somadostempos(&caixas[0]);
  for (int i = 1; i < c; i++) {
    int meio = somadostempos(&caixas[i]);
    if ((meio) < tmin) {
      tmin = meio;
      retorno = i;
    }
  }
  return retorno;
}
void imprimefila(TipoFila *fila) {
  if (filavazia(fila)) {
    return;
  }
  TipoCliente *vet = fila->inicio;
  while (vet != NULL) {
    printf("%d ", vet->id);
    vet = vet->prox;
  }
}
int main(void) {
  TipoFila bb, *caixas;
  TipoCliente aux, aux2;
  int cliente, atendente, t,tt;
  inicializafila(&bb);
  scanf("%d %d", &cliente, &atendente);
  caixas = malloc(atendente * sizeof(TipoFila));
  inicializafilas(caixas, atendente);
  for (int i = 1; i <= cliente; i++) {
    scanf("%d", &t);
    insere(&bb, i, t);
  }
  if(cliente-atendente>0){
  for (int jj = 0; jj < atendente; jj++) {
    aux = retira(&bb);
    insere(&caixas[jj], aux.id, aux.tempo);
  }
  for(int z=0;z<(cliente-atendente);z++){
    tt = menortempo(caixas, atendente);
    aux2 = retira(&bb);
    insere(&caixas[tt], aux2.id, aux2.tempo);}}
  else{
    for (int jk = 0; jk < cliente; jk++) {
    aux = retira(&bb);
    insere(&caixas[jk], aux.id, aux.tempo);
  }}
  printf("1: ");
  imprimefila(&caixas[0]);
  
  for (int k = 1; k < atendente; k++) {
    printf("\n%d: ", (k + 1));
    imprimefila(&caixas[k]);
  }
  return 0;
}