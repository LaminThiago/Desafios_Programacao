#include <stdio.h>
#include <stdlib.h>

#define ALOCA_TAM 100

typedef struct{
	int coeficiente;
  int expoente;
}numero;
typedef struct{
	numero *N;
	int ultimo;
	int tamanho;
}lista;
int inicializalista(lista *lista){
    lista->ultimo  = 0;
    lista->tamanho = ALOCA_TAM;
    lista->N   = malloc(ALOCA_TAM*sizeof(numero));
    if(lista->N == NULL) return -1;
    return 0;
}
void imprimelista(lista *lista){
    int i=0;
    for(i=0; i<lista->ultimo; i++){
        printf("%d %d ", lista->N[i].coeficiente,
               lista->N[i].expoente);}
}
int inserenofinal(lista *lista, 
                      numero novonumero){
	int pos = lista->ultimo, i;

	if(pos==lista->tamanho){
          numero *aux = lista->N;
          numero *novalista = malloc((lista->tamanho+ALOCA_TAM)*sizeof(numero));
	   if(novalista == NULL) return -1;
          for(i=0; i<pos; i++)
             novalista[i] = lista->N[i];
          lista->N    = novalista;
          lista->tamanho += ALOCA_TAM;
          if(aux!=NULL)
            free(aux); 
	}
	lista->N[pos] = novonumero;
	lista->ultimo++;
	return 0;
}
void ordenaLista(lista *lista) {
    for (int i = 0; i < lista->ultimo - 1; i++) {
        for (int j = i + 1; j < lista->ultimo; j++) {
            if (lista->N[i].expoente < lista->N[j].expoente) {
                numero temp = lista->N[i];
                lista->N[i] = lista->N[j];
                lista->N[j] = temp;
            }
        }
    }
}
void removeElemento(lista* lista, int posicao) {
    if (posicao < 0 || posicao >= lista->ultimo) {
        printf("Erro: posição inválida para remoção.\n");
        return;
    }

    for (int i = posicao; i < lista->ultimo - 1; i++) {
        lista->N[i] = lista->N[i + 1];
    }

    lista->ultimo--;
}
void eliminazeros(lista *lista){
  for (int i = 0; i< lista->ultimo-1;i++){
    for (int j = i+ 1;j<lista->ultimo;j++){
        if ((lista->N[i].expoente == lista->N[j].expoente) && ((lista->N[i].coeficiente + lista->N[j].coeficiente) == 0)){
          removeElemento(lista, i);
          removeElemento(lista, j-1);
          i =-1;
          break;
      }
      else if((lista->N[i].expoente == lista->N[j].expoente) && ((lista->N[i].coeficiente +  lista->N[j].coeficiente) != 0)){
          lista->N[i].coeficiente += lista->N[j].coeficiente;
          removeElemento(lista, j);
          i = -1;
        break;
      }
    }
  }
}


int main(){
  int i, j, quan;
  lista lista;
  numero num;
  
  if(inicializalista(&lista) < 0){
    printf("ERRO! Nao foi possivel alocar memoria.\n");
    exit(1);
 }
  scanf("%d", &quan);
  for(i=0;i<quan;i++){
    scanf(" %d %d", &num.coeficiente,&num.expoente);
    if (num.coeficiente!=0){
      inserenofinal(&lista, num);
    }
  }
  eliminazeros(&lista);
  ordenaLista(&lista);
  if (lista.ultimo == 0){
    printf("\nnulo\n0");
  }
  else{  imprimelista(&lista);
  printf("\n%d",lista.ultimo);
  }
  free(lista.N);
  return 0;
}