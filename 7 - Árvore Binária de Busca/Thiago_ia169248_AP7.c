#include <stdio.h>
#include <stdlib.h>
typedef struct TipoNo{
  int num;
  struct TipoNo *esq,*dir,*pai;
}TipoNo;
typedef struct TipoArv{
  TipoNo *raiz;
}TipoArv;
void inicializaArv(TipoArv *arv){
  arv->raiz = NULL;
}
TipoNo *criafolha(int z){
  TipoNo *novo = malloc(sizeof(TipoNo));
  novo->num = z;
  novo->dir = NULL;
  novo->esq = NULL;
  return novo;
}
void insereArv(TipoArv *arv,int z, int *altura){
  TipoNo *novo = criafolha(z);
  TipoNo *y = NULL, *x = arv->raiz;
  int soma = 0;
  while(x!=NULL){
    y = x;
    if(z<x->num){
      x = x->esq;
    }else{
      x = x->dir;
    }
    soma++;
  }
  if(soma>*altura){
    *altura = soma;
  }
  novo->pai = y;
  if(y==NULL){
    arv->raiz = novo;
  }else if(z<y->num){
    y->esq = novo;
}else{
    y->dir = novo;
}
}
void preOrdem(TipoNo *no){
    if(no==NULL){
        return;
    }
    printf("%d ",no->num); 
    preOrdem(no->esq);    
    preOrdem(no->dir);
}
void emOrdem(TipoNo *no){
    if(no==NULL){
        return;
    }
    emOrdem(no->esq);    
    printf("%d ",no->num); 
    emOrdem(no->dir);
}
void posOrdem(TipoNo *no){
    if(no==NULL){
        return;
    }
    posOrdem(no->esq);    
    posOrdem(no->dir);
    printf("%d ",no->num); 
}
void busca(TipoArv *arv,int z){
  TipoNo *x = arv->raiz;
  while(x != NULL && z != x->num){
    if(z<x->num){
      printf("%d ",x->num);
      x = x->esq;
    }else{
      printf("%d ",x->num);
      x = x->dir;
    }
  }
  printf("%d", z);
}

int main(void) {
  TipoArv arv;
  inicializaArv(&arv);
  int quan,bus,nozinho,altura = 0,aux=-1;
  scanf("%d",&quan);
  scanf("%d",&bus);
  for(int i=0;i<quan;i++){
    scanf("%d",&nozinho);
    if(nozinho == bus){
      aux++;
    }
    insereArv(&arv,nozinho,&altura);
  }
  preOrdem(arv.raiz);
  printf("\n");
  emOrdem(arv.raiz);
  printf("\n");
  posOrdem(arv.raiz);
  printf("\n");
  if(aux!=-1){
  busca(&arv,bus);
  }
  else{
    printf("-1");
  }
  printf("\n%d",altura);
  return 0;
}