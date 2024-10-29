#include <stdio.h>
#include <stdlib.h>
typedef struct TipoItem{
	int num;
	struct TipoItem *prox;
}TipoItem;
typedef struct{
	TipoItem *topo;
}TipoPilha;
void inicializaPilha(TipoPilha *pilha){
    pilha->topo = NULL;
}
int pilhaVazia(TipoPilha *pilha){
    if(pilha->topo == NULL)
        return 1;
    return 0;
}
int temdois(TipoPilha* pilha) {
    int conta = 0;
    TipoItem* p = pilha->topo;
    
    while (p != NULL) {
        conta++;
        p = p->prox;
        if (conta >= 2) {
            return 1;
        }
    }
    return 0;
}
int ehdigito(char d){
  if(d=='0'||d=='1'||d=='2'||d=='3'||d=='4'||d=='5'||d=='6'||d=='7'||d=='8'||d=='9'){
    return 1;
  }
  return 0;
}
void push(TipoPilha *pilha,TipoItem novoitem){
  TipoItem *novo;
  novo = malloc(sizeof(TipoItem));
  novo->num = novoitem.num;
  novo->prox = pilha->topo;
  pilha->topo = novo;
}
int pop(TipoPilha* pilha) {
    if (pilhaVazia(pilha)) {
        printf("Invalid Expression\n");
        exit(1);
    }
    int y;
    TipoItem* aux = pilha->topo;
    y = aux->num;
    pilha->topo = pilha->topo->prox;
    free(aux);
    return y;
}
int main(void) {
  TipoPilha polish;
  TipoItem naux,oaux;
  int i=0,j,a,b,bo=0,ccount=0;
  char N[1026];
  inicializaPilha(&polish);
  scanf("%s",N);
    while (N[i] != '\0') {
        if (ehdigito(N[i])) {
            j = N[i] - '0';
            naux.num = j;
            push(&polish, naux);
            ccount++;
            i++;
        } else {
              if(temdois(&polish)){
                b = pop(&polish);
                ccount--;
                a = pop(&polish);
                if (N[i] == '*') {
                  oaux.num = a*b;
                } else if (N[i] == '/') {
                  oaux.num = a/b;
                } else if (N[i] == '+') {
                  oaux.num = a+b;
                } else if (N[i] == '-') {
                  oaux.num = a-b;
                }
                  push(&polish, oaux);
                  i++;
            }else {
            bo = 1;
            break;
          }}}
if(ccount == 1&&bo!=1){
  printf("%d",pop(&polish));
}else{
  printf("Invalid Expression");
}

    return 0;
}