#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  int C_timestamp;
  int C_IP;
}Cliente;

typedef struct{
  Cliente *Vector;
  int num;
}Tabela;
   
int main(){
  int M, timestamp, IP, insert, *n;
  float LMax;
  char comando[4];
  Tabela *Hashtable;
  scanf("%d %f", &M, &LMax);
  Hashtable = (Tabela*)calloc(M, sizeof(Tabela));
  if(Hashtable == NULL){
    printf("Falha na alocação");
    exit(1);
  }
  for(int a = 0; a < M; a++){
    Hashtable[a].Vector = NULL;
    Hashtable[a].num = 0;
  }
  while(scanf(" %3[^ ]", comando), strcmp(comando, "END") != 0){
    if(strcmp(comando, "NEW") == 0){
      scanf("%d %d", &timestamp, &IP);
      insert = timestamp % M;
      Hashtable[insert].num++;
      Hashtable[insert].Vector = (Cliente*) realloc (Hashtable[insert].Vector, Hashtable[insert].num*sizeof(Cliente));
    }
  }
}
