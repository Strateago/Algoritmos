#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Cliente{
  unsigned C_timestamp;                                    
  unsigned C_IP;
}Cliente;

typedef struct{
  Cliente *Vector;
  int num;
}Tabela;

int partition(Cliente *Vector, int L, int R){
  int C = ((rand()%(R-L))+L);
  int i = L, j = R-1;
  Cliente Aux;
  Aux = Vector[L];
  Vector[L] = Vector[C];
  Vector[C] = Aux;
  while(i <= j){
    while(i < R && Vector[i].C_timestamp <= Vector[L].C_timestamp){
      i++;
    }
    while(Vector[j].C_timestamp > Vector[L].C_timestamp){
      j--;
    }
    if(i < j){
      Aux = Vector[i];
      Vector[i] = Vector[j];
      Vector[j] = Aux;
    }
  }
  Aux = Vector[L];
  Vector[L] = Vector[j];
  Vector[j] = Aux;
  return j;
}

void ordena(Cliente *Vector, int L, int R){
  int P;
  if(R-L > 1){
    P = partition(Vector, L, R);
    ordena(Vector, L, P);
    ordena(Vector, P+1, R);
  }
}

int binary_search(Cliente *Vector, unsigned timestamp, int num){
  int L = 0, R = num - 1, Mid;
  while(L <= R){
    Mid = (L + R)/2;
    if(timestamp == Vector[Mid].C_timestamp){
      return Mid;
    }
    else if(timestamp > Vector[Mid].C_timestamp){
      L = Mid+1;
    }
    else{
      R = Mid-1;
    }
  }
  return -1;
}
   
int main(){
  int M, newM, insert, Position = -1;
  unsigned IP, timestamp;
  float LMax, f_carga;
  char comando[4];
  Tabela *Hashtable, *Rehash;
  srand(time(NULL));
  scanf("%d %f", &M, &LMax);
  Hashtable = (Tabela*)malloc(M*sizeof(Tabela));
  if(Hashtable == NULL){
    exit(1);
  }
  for(int a = 0; a < M; a++){
    Hashtable[a].Vector = NULL;
    Hashtable[a].num = 0;
  }
  while(scanf(" %3[^ ]", comando), strcmp(comando, "END") != 0){
    if(strcmp(comando, "NEW") == 0){
      if((f_carga/M) > LMax){
        newM = (2*M)+1;
        Rehash = (Tabela*)malloc(newM * sizeof(Tabela));
        for(int a = 0; a < newM; a++){
          Rehash[a].num = 0;
          Rehash[a].Vector = NULL;
        }
        for(int a = 0; a < M; a++){
          for(int b = 0; b < Hashtable[a].num; b++){
            insert = Hashtable[a].Vector[b].C_timestamp % newM;
            Rehash[insert].Vector = (Cliente*)realloc(Rehash[insert].Vector, (Rehash[insert].num + 1)*sizeof(Cliente));
            if(Rehash[insert].Vector == NULL){
              exit(1);
            }
            Rehash[insert].Vector[Rehash[insert].num].C_timestamp = Hashtable[a].Vector[b].C_timestamp;
            Rehash[insert].Vector[Rehash[insert].num].C_IP = Hashtable[a].Vector[b].C_IP;
            Rehash[insert].num++;
            ordena(Rehash[insert].Vector, 0, Rehash[insert].num);
          }
          free(Hashtable[a].Vector);
        }
        free(Hashtable);
        Hashtable = Rehash;
        Rehash = NULL;
        M = newM;
      }
      f_carga++;
      scanf("%u %u", &timestamp, &IP);
      insert = timestamp % M;
      Hashtable[insert].Vector = (Cliente*)realloc(Hashtable[insert].Vector, (Hashtable[insert].num + 1)*sizeof(Cliente));
      if(Hashtable[insert].Vector == NULL){
        exit(1);
      }
      Hashtable[insert].Vector[Hashtable[insert].num].C_IP = IP;
      Hashtable[insert].Vector[Hashtable[insert].num].C_timestamp = timestamp;
      Hashtable[insert].num++;
      printf("%d %d\n", insert, Hashtable[insert].num);
    }
    if(strcmp(comando, "QRY") == 0){
      scanf("%u", &timestamp);
      insert = timestamp % M;
      Position = binary_search(Hashtable[insert].Vector, timestamp, Hashtable[insert].num);
      if(Position != -1){
        printf("%u %d\n", Hashtable[insert].Vector[Position].C_IP, Position);
      }
      else{
        printf("-1 -1\n");
      }
    }
  }
  for(int a = 0; a < M; a++){
    free(Hashtable[a].Vector);
  }
  free(Hashtable);
}
