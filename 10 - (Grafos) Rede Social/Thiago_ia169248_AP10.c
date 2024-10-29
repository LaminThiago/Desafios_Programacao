#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 50
#define TAM 50
typedef struct{
char nome[50];
int index; 
}TipoItem;
typedef struct{
TipoItem l[N];
int qtd;
}TipoLista;
typedef struct{
TipoLista lista; 
int adj[N][N]; 
}TipoGrafoMatrizAdj;
void zera(int jafoi[TAM]) {
    for (int i = 0; i < TAM; i++) {
        jafoi[i] = 0;
    }
}
void imprimirMatriz(int matriz[TAM][TAM], int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }
  printf("\n");
}
void inicializaGrafo(TipoGrafoMatrizAdj *grafo){
int i,j;
grafo->lista.qtd=0;
for(i=0; i<N; i++)
for(j=0; j<N; j++)
grafo->adj[i][j]=0;
}
int inserirNo(TipoLista *lista, char nome[TAM]){
if(lista->qtd==N) return -1;
strcpy(lista->l[lista->qtd].nome, nome);
lista->l[lista->qtd].index = lista->qtd;
lista->qtd++;
return lista->qtd - 1;
}
int buscaNo(TipoLista *lista, char nome[TAM]){
int i;
for(i=0; i<lista->qtd; i++){
if(strcmp(lista->l[i].nome, nome)==0){
return lista->l[i].index;
}
}
return -1;
}
int insere(TipoGrafoMatrizAdj *grafo, char no1[TAM], char no2[TAM]){
  int i1 = buscaNo(&grafo->lista, no1);
  int i2 = buscaNo(&grafo->lista, no2);
if(i1 == -1){
  i1 = inserirNo(&grafo->lista, no1);
}
if(i2 == -1){
  i2 = inserirNo(&grafo->lista, no2);
}
if(i1<0 || i2<0){ 
  return -1;
}
grafo->adj[i1][i2] = 1;
grafo->adj[i2][i1] = 1; 
  
return 1;
}
/*int buscaaux(TipoGrafoMatrizAdj *grafo, int i, int index1, int jafoi[1025]){
  int count = 0;
  for(int j = 0; j<grafo->lista.qtd; j++){
    if(grafo->adj[i][j] == 1 && index1 != j && !estaem(j, jafoi)){
        jafoi[j] = j;
        count++;
    }
  }
  return count;
}*/
int busca(TipoGrafoMatrizAdj *grafo, char pessoa[TAM]) {
    int index1 = buscaNo(&grafo->lista, pessoa), count = 0, jafoi[TAM];
    zera(jafoi);
    for (int i = 0; i < grafo->lista.qtd; i++) {
        if (grafo->adj[index1][i] == 1) {
            for (int j = 0; j < grafo->lista.qtd; j++) {
                if (grafo->adj[i][j] == 1 && index1 != j && !jafoi[j] && grafo->adj[j][index1]!=1) {
                    jafoi[j] = 1;
                    count++;
                }
            }
        }
    }
    return count;
}

int main(void) {
  TipoGrafoMatrizAdj grafo;
  inicializaGrafo(&grafo);
  int n,m;
  char pessoa[TAM], aux1[TAM], aux2[TAM];
  scanf("%s %d %d", pessoa, &n, &m);
  for(int k = 0; k<m; k++){
    scanf("%s %s", aux1, aux2);
    insere(&grafo, aux1, aux2);
  }
  printf("%d", busca(&grafo, pessoa));
  //imprimirMatriz(grafo.adj, 7, 7);
  return 0;
}