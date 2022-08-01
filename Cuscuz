#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Carta{
  int numero;
  char naipe;
  struct Carta *next;
}Carta;

typedef struct{
  int n_cartas;
  Carta *Head;
  Carta *Tail;
  int eliminado;
}Jogador;

typedef struct{
  int numero;
  char naipe;
  int comp;
}Compara;

Carta* adiciona(int numero, char naipe, Carta *Tail, int *N_cartas){
  Carta *New;
  New = (Carta*)malloc(sizeof(Carta));
  New->numero = numero;
  New->naipe = naipe;
  New->next = Tail->next;
  Tail->next = New;
  (*N_cartas)++;
  return Tail;
}

Carta *adiciona_fila(int numero, char naipe, Carta *Tail, int *N_cartas){
  Tail = adiciona(numero, naipe, Tail, N_cartas);
  return Tail->next;
}

Carta *remover(Carta *Head){
  Carta *Del;
  Del = Head->next;
  Head->next = Del->next;
  free(Del);
  return Head;
}

Carta *remover_fila(Carta *Head, Carta **Tail, int *N_cartas){
  Head = remover(Head);
  if(Head->next == NULL){
    *Tail = Head;
  }
  (*N_cartas)--;
  return Head;
}

void desalocar(Carta *Head, int N){
  Carta *Free;
  Free = Head;
  for(int a = 0; a < N; a++){
    Free = Free->next;
  }
  free(Free);
}

int compara(Compara *C, int N){
  int vencedor = -1;
  for(int a = 0; a < N; a++){
    for(int b = 0; b < N; b++){
      if(b != a){
        if(C[a].numero > C[b].numero){
          C[a].comp++;
        }
        else if(C[a].numero == C[b].numero){
          if(C[a].naipe == C[b].naipe){
          }
          else if(C[a].naipe == 'P'){
            C[a].comp++;
          }
          else if(C[a].naipe == 'O' && C[b].naipe != 'P'){
            C[a].comp++;
          }
          else if(C[a].naipe == 'E' && C[b].naipe == 'C'){
            C[a].comp++;
          }
        }
      }
    }
    if(C[a].comp == N-1){
      vencedor = a;
    }
  }
  return vencedor;
}

int main(){
  int n, num, vencedor_R, n_cuscuz = 0, round = 0, eliminados = 0, vencedor_C = -1;
  Jogador *V;
  Compara *C, *Comp;
  Carta *cuscuz;
  char END[] = "END", DEAL[] = "DEA", ROUND[] = "RND", palavra[4], naipe;
  scanf("%d", &n);
  V = (Jogador*)malloc(n*sizeof(Jogador));
  if(V == NULL){
    printf("Falha na alocacao");
    exit(1);
  }
  for(int a = 0; a < n; a++){
    V[a].Head = (Carta*)malloc(sizeof(Carta));
    if(V[a].Head == NULL){
      printf("Falha na alocacao");
      exit(1);
    }
    V[a].Tail = V[a].Head;
    V[a].Head->next = NULL;
    V[a].n_cartas = 0;
    V[a].eliminado = 0;
  }
  C = (Compara*)malloc(n*sizeof(Compara));
  if(C == NULL){
    printf("Falha na alocacao");
    exit(1);
  }
  Comp = (Compara*)malloc(n*sizeof(Compara));
  if(Comp == NULL){
    printf("Falha na alocacao");
    exit(1);
  }
  cuscuz = (Carta*)malloc(sizeof(Carta));
  if(cuscuz == NULL){
    printf("Falha na alocacao");
    exit(1);
  }
  scanf(" %3[^ ]", palavra);
  while(strcmp(palavra, END) != 0){
    //Deal
    if(strcmp(palavra, DEAL) == 0){
      for(int a = 0; a < n; a++){
        if(V[a].eliminado == 0){
          scanf("%d%c", &num, &naipe);
          V[a].Tail = adiciona_fila(num, naipe, V[a].Tail, &V[a].n_cartas);
        }
      }
    }
    //Round
    else if(strcmp(palavra, ROUND) == 0){
      vencedor_R = -1;
      while(vencedor_R == -1 && eliminados < n){
        for(int a = 0; a < n; a++){
          if(V[a].eliminado == 0){
            C[a].numero = V[a].Head->next->numero;
            C[a].naipe = V[a].Head->next->naipe;
            C[a].comp = 0;
            V[a].Head = remover_fila(V[a].Head, &V[a].Tail, &V[a].n_cartas);
            cuscuz = adiciona(C[a].numero, C[a].naipe, cuscuz, &n_cuscuz);
          }
        }
        vencedor_R = compara(C, n);
        for(int a = 0; a < n; a++){
          if(a!=vencedor_R && V[a].n_cartas == 0 && V[a].eliminado == 0){  
            V[a].eliminado = 1;
            eliminados++;
            C[a].numero = 0;
            C[a].naipe = 'C';
          }
        }
        if(eliminados == n){
          printf("-1 -1 -1\n");
        }
        else if(vencedor_R != -1){
          printf("%d %d %d\n", round, vencedor_R, n_cuscuz);
          for(int a = 0; a < n_cuscuz; a++){
            V[vencedor_R].Tail = adiciona_fila(cuscuz->next->numero, cuscuz->next->naipe, V[vencedor_R].Tail, &V[vencedor_R].n_cartas);
            cuscuz = remover(cuscuz);
          }
          n_cuscuz = 0;
        }
      }
      round++;
    }
    scanf(" %3[^ ]", palavra);
  }
  for(int a = 0; a < n; a++){
    Comp[a].comp = 0;
    for(int b = 0; b < n; b++){
      if(b!=a && V[a].n_cartas > V[b].n_cartas){
        Comp[a].comp++;
      }
    }
    if(Comp[a].comp == n-1){
      vencedor_C = a;
    }
  }
  printf("%d\n", vencedor_C);
  for(int a = 0; a < n; a++){
    for(int b = V[a].n_cartas; b > 0; b--){
      desalocar(V[a].Head, b);
    }
    free(V[a].Head);
  }
  free(V);
  free(C);
  free(Comp);
  for(int a = n_cuscuz; a > 0; a--){
    desalocar(cuscuz, a);
  }
  free(cuscuz);
  return 0;
}
