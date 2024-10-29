#include <stdio.h>
#include <stdlib.h>
typedef struct TipoItem{
	int num;
  char l;
 	struct TipoItem *ant,*prox;
}TipoItem;
typedef struct{
	TipoItem *inicio,*fim; 
}TipoLista;
void inicializarListaDE(TipoLista *lista){
    lista->inicio = NULL;
    lista->fim    = NULL;
}
void imprimirListaDE(TipoLista *lista){
    TipoItem *p=lista->inicio;
    while(p!=NULL){
        printf("%d",p->num);
        printf("%c",p->l);
        p=p->prox;
    }
  printf("\n");
}
int contadigitos(int numero){
  int digitos=0;
    while (numero > 0) {
        numero /= 10;
        digitos++;
    }

    return digitos;
}
int contalista(TipoLista *lista){
  int soma=0,n;
  TipoItem *vet=lista->inicio;
  while(vet!=NULL){
    n = contadigitos(vet->num);
    soma = soma + n + 1;
    vet=vet->prox;
  }
  return soma;
}
void limpavetor(int vet[]){
  for(int j=0;j<27;j++){
    vet[j] = 0;
  }
}
void inserenofim(TipoLista *lista, TipoItem novo){
	TipoItem *novoaux;
	novoaux = (TipoItem *) malloc(sizeof(TipoItem));
	*novoaux = novo;
  novoaux->prox = NULL;
	if(lista->inicio==NULL){ 
		lista->inicio = novoaux;
		lista->fim    = novoaux;
	}
  else{
    novoaux->ant = lista->fim;
    lista->fim->prox = novoaux;
    lista->fim = novoaux;
  }
}
void retiraruido(TipoLista *lista,TipoItem *point){
  if(lista->fim == lista->inicio){
return;
  }
  else if(point == lista->inicio && point->prox->num==1){
    return;
  }
  else if (point == lista->fim && point->ant->num==1){
    return;
  }
  else if((lista->inicio == point) && ((point->prox->num)>1)){
    TipoItem *aux = lista->inicio;
    lista->inicio = lista->inicio->prox;
    lista->inicio->ant = NULL;
    aux->prox->num = aux->prox->num + 1;
    free(aux);
  }
  else if(lista->fim == point && point->ant->num>1){
    TipoItem *aux = lista->fim;
    lista->fim = lista->fim->ant;
    lista->fim->prox = NULL;
    aux->ant->num = aux->ant->num + 1;
    free(aux); 
  }
  else if(point->ant->num==point->prox->num && point->ant->num>1){
    TipoItem *aux=point;
    point->ant->prox = point->prox;
    aux->prox->ant = aux->ant;
    aux->ant->num = aux->ant->num + 1;
    free(aux);
  }
  else if(point->ant->num>point->prox->num && point->prox->num>1){
    TipoItem *aux=point;
    point->ant->prox = point->prox;
    aux->prox->ant = aux->ant;
    aux->ant->num = aux->ant->num + 1;
    free(aux);
      }
  else if(point->ant->num<point->prox->num && point->ant->num>1){
    TipoItem *aux=point;
    point->ant->prox = point->prox;
    aux->prox->ant = aux->ant;
    aux->prox->num = aux->prox->num + 1;
    free(aux);
  }
else{
  return;
}
}

int main(void) {
TipoLista lista;
TipoItem aux;
char N[2000];
int i=0,count=0,auxx,tam1;
  inicializarListaDE(&lista);
  scanf("%s",N);
  while(N[i]!='\0'){
    if(N[i]==N[i+1]){
      count++;
    }
    else{
      count++;
      aux.num = count;
      aux.l = N[i];
      inserenofim(&lista, aux);
      count=0;
    }
    i++;
  }
  printf("\n%d\n",contalista(&lista));
  imprimirListaDE(&lista);
  TipoItem *point = lista.inicio;
  while(point!=NULL){
    if(point->num==1){
      retiraruido(&lista,point);
    }
   point = point->prox;
  }
  printf("%d\n",contalista(&lista));
  imprimirListaDE(&lista);
  return 0;
}
