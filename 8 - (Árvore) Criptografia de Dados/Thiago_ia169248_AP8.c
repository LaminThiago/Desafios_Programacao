#include <stdio.h>
#include <stdlib.h>
typedef struct TipoNo{
  int num;
  char let;
  struct TipoNo *esq,*dir,*pai;
}TipoNo;
typedef struct TipoArv{
  TipoNo *raiz;
}TipoArv;
void inicializaArv(TipoArv *arv){
  arv->raiz = NULL;
}
TipoNo *criafolha(int z, char l){
  TipoNo *novo = malloc(sizeof(TipoNo));
  novo->num = z;
  novo->let = l;
  novo->dir = NULL;
  novo->esq = NULL;
  return novo;
}
void insereArv(TipoArv *arv,int z, char l){
  TipoNo *novo = criafolha(z,l);
  TipoNo *y = NULL, *x = arv->raiz;
  while(x!=NULL){
    y = x;
    if(z<x->num){
      x = x->esq;
    }else{
      x = x->dir;
    }
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
void emOrdem(TipoNo *no){
    if(no==NULL){
        return;
    }
    emOrdem(no->esq);    
    printf("%c",no->let); 
    emOrdem(no->dir);
}
TipoNo *remover(TipoNo *raiz, int num, char let){
  if(raiz == NULL){
    return NULL;
  }else{
    if(raiz->num == num && raiz->let == let){
      if(raiz->esq == NULL && raiz->dir == NULL){//folha
        free(raiz);
        return NULL;
      }
      else{
        if(raiz->esq != NULL && raiz->dir != NULL){//dois filhos
          TipoNo *aux = raiz->dir;
          int a;
          char b;
          while(aux->esq != NULL){
            aux = aux->esq;
          }
          a = raiz->num;
          b = raiz->let;
          raiz->num = aux->num;
          raiz->let = aux->let;
          aux->num = a;
          aux->let = b;
          raiz->dir = remover(raiz->dir, num, let);
          return raiz;
        }
        else{//um filho
          TipoNo *aux;
          if(raiz->esq != NULL){
            aux = raiz->esq;
          }else{
            aux = raiz->dir;
          }
          free(raiz);
          return aux;
        }
      }
    }else{
      if(num < raiz->num){
        raiz->esq = remover(raiz->esq, num, let);
      }else{
        raiz->dir = remover(raiz->dir, num, let);
      }
      return raiz;
    }
  }
}
int conta(char alone, char *Z){
  int count=0;
  for (int i = 0; Z[i]!='\0'; i++){
  if(Z[i]==alone){
    count++;
  }
  }
return count;
}
int main(void) {
  TipoArv arvore;
  TipoNo aux;
  int n=0, alf[28], flx1=0, flx2=0;
  char lx1, lx2, str[1025] ;
  inicializaArv(&arvore);
  scanf("%c %c %s", &lx1, &lx2, str);
  for(int j=65;j<91;j++){
    char aa = j;
    int contado = conta(aa,str);
    if(aa == lx1){
      flx1 = contado;
    }
    if(aa == lx2){
      flx2 = contado;
    }
    if(contado!=0){
    insereArv(&arvore, contado, aa);
    }
  }
  emOrdem(arvore.raiz);
  remover(arvore.raiz, flx1, lx1);
  remover(arvore.raiz, flx2, lx2);
  printf("\n");
  emOrdem(arvore.raiz);
  return 0;
}