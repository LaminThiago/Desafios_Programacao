#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct TipoNo{
    char nome[1025];
    struct TipoNo *filho;
    struct TipoNo *irmao;
    struct TipoNo *pai;
}TipoNo;
typedef struct TipoArvG{
    TipoNo *raiz;
}TipoArvG;
TipoNo *cria(char nome[1025]){
    TipoNo *novo = (TipoNo *) malloc(sizeof(TipoNo));
    strcpy(novo->nome, nome);
    novo->filho = NULL;
    novo->irmao = NULL;
    novo->pai = NULL;
    return novo;
}
void inicializa(TipoArvG *arv){
    char auxx[1025] = "\\root";
    arv->raiz = cria(auxx);
}
void insere(TipoNo *arv, TipoNo *subarv){
    subarv->irmao = arv->filho;
    arv->filho    = subarv;
    subarv->pai   = arv;
}
TipoNo *procura(TipoNo *raiz, char bus[1025]) {
    if (raiz == NULL) {
        return NULL;
    }

    if (strcmp(bus, raiz->nome) == 0) {
        return raiz;
    }

    TipoNo *p = raiz->filho;
    while (p != NULL) {
        TipoNo *resultado = procura(p, bus);
        if (resultado != NULL) {
            return resultado;
        }
        p = p->irmao;
    }

    return NULL;
}
void remover(TipoNo *root, char removido[1025]){
    TipoNo *x = procura(root, removido), *y = x->pai, *z;
    if(y!=NULL && x!=NULL){
      if(y->filho == x){//primeira posicao
        y->filho = x->irmao;
      }else{
        TipoNo *aux = y->filho;
        while(aux->irmao != x){
          aux = aux->irmao;
        }
        aux->irmao = x->irmao;
      }
      free(x);
    }
}
void print(TipoArvG *arv, char busc[1025]){
  if(arv->raiz == NULL){
    printf("Arquivo nao encontrado!");
    return;
  }
  TipoNo *p = procura(arv->raiz, busc);
  if(p == NULL){
    printf("Arquivo nao encontrado!");
    return;
  }
  while(p != NULL && p->nome != NULL){
    printf("%s ", p->nome);
    p = p->pai;
  }
}


int main(void) {
  TipoArvG arv;
  int N;
  char op[1025], son[1025], dad[1025], busc[1025];
  inicializa(&arv);
  scanf("%d", &N);
  scanf("%s", busc);
  for(int i=0; i<N; i++){
    scanf("%s", op);
    if(strcmp(op, "-a") == 0){
      scanf("%s %s", son, dad);
      TipoNo *novin = cria(son);
      TipoNo *father = procura(arv.raiz, dad);
      if(father!=NULL){
        insere(father, novin);
      }
    }
    else if(strcmp(op, "-r") == 0){
      scanf("%s", son);
      TipoNo *aj = procura(arv.raiz, son);
      if(aj!=NULL){
              remover(arv.raiz, son);
      }
    }else{
      scanf("%s %s", son, dad);
      remover(arv.raiz, son);
      TipoNo *novin = cria(son);
      TipoNo *father = procura(arv.raiz, dad);
      if(father!=NULL){
        insere(father, novin);
      }
    }
  }
  print(&arv, busc);
  return 0;
}