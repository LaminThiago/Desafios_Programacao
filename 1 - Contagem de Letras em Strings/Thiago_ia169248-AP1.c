#include <stdio.h>
#include <stdlib.h>
void invertestr(char str[], int inicio, int fim) {
    if (inicio >= fim)
        return;

    char temp = str[inicio];
    str[inicio] = str[fim];
    str[fim] = temp;

    invertestr(str, inicio + 1, fim - 1);
}
int contastr(char str[]){
    int tamanho = 0;
    while(str[tamanho]!='\0'){
        tamanho++;
    }
    return tamanho;
}
void concatena(const char *xx, const char *yy, char *Z){
    int i, j;
    for (i = 0; xx[i] != '\0'; i++) {
        Z[i] = xx[i];
    }

    for (j = 0; yy[j] != '\0'; j++) {
        Z[i + j] = yy[j];
    }
    Z[i + j] = '\0';
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

int main(){
    int sizeX, sizeY, contado, trX, trY, trZ;
    char *X, *Y, alone, *Z;
    scanf("%d",&sizeX);
    scanf("%d",&sizeY);
    scanf(" %c",&alone);
    X = (char*) malloc(sizeX *1000* sizeof(char));
    Y = (char*) malloc(sizeY *1000* sizeof(char));
    scanf("   %s", X);
    scanf("      %s", Y);
    trX = contastr(X);
    trY = contastr(Y);
    invertestr(X,0,trX-1);
    invertestr(Y,0,trY-1);
    Z = (char*) malloc((trX+trY+1) *1000* sizeof(char));
    concatena(X,Y,Z);
    trZ = contastr(Z);
    contado = conta(alone, Z);
    printf("%s\n", Z);
    printf("%d\n",trZ);
    printf("%d", contado);
    return 0;
}